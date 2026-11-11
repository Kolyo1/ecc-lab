#include <catch2/catch_test_macros.hpp>
#include "core/bigint/BigInt.h"
#include "core/curves/WeierstrassCurve.h"
#include "core/curves/CurveParams.h"

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

TEST_CASE("isOnCurve tiny") {
    WeierstrassCurve c(tinyParams());
    REQUIRE(c.isOnCurve(Point{ BigInt("5"), BigInt("1"), false }));
    REQUIRE(c.isOnCurve(Point{ BigInt("6"), BigInt("3"), false }));
    REQUIRE_FALSE(c.isOnCurve(Point{ BigInt("0"), BigInt("0"), false }));
}

TEST_CASE("dbl tiny") {
    WeierstrassCurve c(tinyParams());
    Point P{ BigInt("5"), BigInt("1"), false };
    Point R = c.dbl(P);
    REQUIRE(R.x.toString() == "6");
    REQUIRE(R.y.toString() == "3");
}

TEST_CASE("add tiny") {
    WeierstrassCurve c(tinyParams());
    Point P{ BigInt("5"), BigInt("1"), false };
    Point Q{ BigInt("6"), BigInt("3"), false };
    Point R = c.add(P, Q);
    REQUIRE(R.x.toString() == "10");
    REQUIRE(R.y.toString() == "6");
}

TEST_CASE("scalarMul tiny") {
    WeierstrassCurve c(tinyParams());
    Point G{ BigInt("5"), BigInt("1"), false };
    Point R = c.scalarMul(BigInt("3"), G);
    REQUIRE(R.x.toString() == "10");
    REQUIRE(R.y.toString() == "6");
    Point O = c.scalarMul(BigInt("19"), G);
    REQUIRE(O.isInfinity);
}

TEST_CASE("negate tiny") {
    WeierstrassCurve c(tinyParams());
    Point P{ BigInt("5"), BigInt("1"), false };
    Point N = c.negate(P);
    REQUIRE(N.x.toString() == "5");
    REQUIRE(N.y.toString() == "16");   // -1 mod 17 = 16
    Point O = c.add(P, N);
    REQUIRE(O.isInfinity);
}
