#include <catch2/catch_test_macros.hpp>
#include <string>
#include "core/bigint/BigInt.h"
#include "core/curves/WeierstrassCurve.h"
#include "core/curves/CurveParams.h"
#include "core/strategies/DoubleAndAdd.h"
#include "core/strategies/MontgomeryLadder.h"
#include "core/strategies/NaiveReduction.h"
#include "core/strategies/BarrettReduction.h"

using namespace ecc;

static CurveParams tinyParams() {
    CurveParams p;
    p.name = "tiny";
    p.p = BigInt("17");
    p.a = BigInt("2");
    p.b = BigInt("2");
    p.G = Point{ BigInt("5"), BigInt("1"), false };
    p.n = BigInt("19");
    p.h = BigInt("1");
    return p;
}

TEST_CASE("DoubleAndAdd matches naive scalarMul") {
    WeierstrassCurve c(tinyParams());
    Point G{ BigInt("5"), BigInt("1"), false };
    DoubleAndAdd s;
    for (int k = 0; k < 19; ++k) {
        Point expected = c.scalarMul(BigInt(std::to_string(k)), G);
        Point got = s.multiply(c, BigInt(std::to_string(k)), G);
        REQUIRE(got.x == expected.x);
        REQUIRE(got.y == expected.y);
    }
}

TEST_CASE("MontgomeryLadder matches naive scalarMul") {
    WeierstrassCurve c(tinyParams());
    Point G{ BigInt("5"), BigInt("1"), false };
    MontgomeryLadder s;
    for (int k = 0; k < 19; ++k) {
        Point expected = c.scalarMul(BigInt(std::to_string(k)), G);
        Point got = s.multiply(c, BigInt(std::to_string(k)), G);
        REQUIRE(got.x == expected.x);
        REQUIRE(got.y == expected.y);
    }
}

TEST_CASE("DoubleAndAdd and MontgomeryLadder agree") {
    WeierstrassCurve c(tinyParams());
    Point G{ BigInt("5"), BigInt("1"), false };
    DoubleAndAdd da;
    MontgomeryLadder ml;
    for (int k = 0; k < 19; ++k) {
        Point a = da.multiply(c, BigInt(std::to_string(k)), G);
        Point b = ml.multiply(c, BigInt(std::to_string(k)), G);
        REQUIRE(a.x == b.x);
        REQUIRE(a.y == b.y);
    }
}

TEST_CASE("NaiveReduction basic") {
    NaiveReduction r;
    REQUIRE(r.reduce(BigInt("10"), BigInt("3")).toString() == "1");
    REQUIRE(r.reduce(BigInt("100"), BigInt("7")).toString() == "2");
    REQUIRE(r.reduce(BigInt("5"), BigInt("5")).toString() == "0");
    REQUIRE(r.reduce(BigInt("0"), BigInt("17")).toString() == "0");
}

TEST_CASE("NaiveReduction negative") {
    NaiveReduction r;
    REQUIRE(r.reduce(BigInt("-1"), BigInt("17")).toString() == "16");
    REQUIRE(r.reduce(BigInt("-17"), BigInt("17")).toString() == "0");
}

TEST_CASE("BarrettReduction matches naive (small)") {
    NaiveReduction n;
    BarrettReduction b;
    for (int x = -50; x <= 200; ++x) {
        for (int m : {3, 7, 17, 31}) {
            BigInt bx(std::to_string(x));
            BigInt bm(std::to_string(m));
            REQUIRE(b.reduce(bx, bm).toString() == n.reduce(bx, bm).toString());
        }
    }
}

TEST_CASE("BarrettReduction large values") {
    NaiveReduction n;
    BarrettReduction b;
    BigInt x("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    BigInt m("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    // x mod m == 0
    REQUIRE(b.reduce(x, m).toString() == "0");
    // x-1 mod m == m-1
    BigInt xm1 = x - BigInt("1");
    REQUIRE(b.reduce(xm1, m).toString() == n.reduce(xm1, m).toString());
}

TEST_CASE("strategy names") {
    REQUIRE(std::string(DoubleAndAdd().name()) == "DoubleAndAdd");
    REQUIRE(std::string(MontgomeryLadder().name()) == "MontgomeryLadder");
    REQUIRE(std::string(NaiveReduction().name()) == "Naive");
    REQUIRE(std::string(BarrettReduction().name()) == "Barrett");
}
