#include <catch2/catch_test_macros.hpp>
#include "core/bigint/BigInt.h"
#include "core/curves/WeierstrassCurve.h"
#include "core/curves/MontgomeryCurve.h"
#include "core/curves/EdwardsCurve.h"
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

static CurveParams montParams() {
    CurveParams p;
    p.name = "mont-tiny";
    p.p = BigInt("17");
    p.a = BigInt("3");   // A
    p.b = BigInt("1");   // B
    p.G = Point{ BigInt("5"), BigInt("1"), false };
    p.n = BigInt("1");
    p.h = BigInt("1");
    return p;
}

TEST_CASE("Montgomery isOnCurve") {
    MontgomeryCurve c(montParams());
    REQUIRE(c.isOnCurve(Point{ BigInt("5"), BigInt("1"), false }));
    REQUIRE(c.isOnCurve(Point{ BigInt("8"), BigInt("10"), false }));
    REQUIRE_FALSE(c.isOnCurve(Point{ BigInt("0"), BigInt("1"), false }));
}

TEST_CASE("Montgomery dbl") {
    MontgomeryCurve c(montParams());
    Point P{ BigInt("5"), BigInt("1"), false };
    Point R = c.dbl(P);
    REQUIRE(R.x.toString() == "8");
    REQUIRE(R.y.toString() == "10");
}

TEST_CASE("Montgomery add") {
    MontgomeryCurve c(montParams());
    Point P{ BigInt("5"), BigInt("1"), false };
    Point Q{ BigInt("8"), BigInt("10"), false };
    Point R = c.add(P, Q);
    REQUIRE(R.x.toString() == "10");
    REQUIRE(R.y.toString() == "1");
}

TEST_CASE("Montgomery negate") {
    MontgomeryCurve c(montParams());
    Point P{ BigInt("5"), BigInt("1"), false };
    Point N = c.negate(P);
    REQUIRE(N.x.toString() == "5");
    REQUIRE(N.y.toString() == "16");
    Point O = c.add(P, N);
    REQUIRE(O.isInfinity);
}

static CurveParams edParams() {
    CurveParams p;
    p.name = "ed-tiny";
    p.p = BigInt("17");
    p.a = BigInt("1");   // a_quad
    p.b = BigInt("3");   // d
    p.G = Point{ BigInt("1"), BigInt("0"), false };
    p.n = BigInt("1");
    p.h = BigInt("1");
    return p;
}

TEST_CASE("Edwards isOnCurve") {
    EdwardsCurve c(edParams());
    REQUIRE(c.isOnCurve(Point{ BigInt("1"), BigInt("0"), false }));
    REQUIRE(c.isOnCurve(Point{ BigInt("0"), BigInt("1"), false }));
    REQUIRE_FALSE(c.isOnCurve(Point{ BigInt("0"), BigInt("0"), false }));
}

TEST_CASE("Edwards dbl") {
    EdwardsCurve c(edParams());
    Point P{ BigInt("1"), BigInt("0"), false };
    Point R = c.dbl(P);
    REQUIRE(R.x.toString() == "0");
    REQUIRE(R.y.toString() == "16");
}

TEST_CASE("Edwards add") {
    EdwardsCurve c(edParams());
    Point P{ BigInt("1"), BigInt("0"), false };
    Point Q{ BigInt("0"), BigInt("16"), false };
    Point R = c.add(P, Q);
    REQUIRE(R.x.toString() == "16");
    REQUIRE(R.y.toString() == "0");
}

TEST_CASE("Edwards negate") {
    EdwardsCurve c(edParams());
    Point P{ BigInt("1"), BigInt("0"), false };
    Point N = c.negate(P);
    REQUIRE(N.x.toString() == "16");
    REQUIRE(N.y.toString() == "0");
    Point I = c.add(P, N);
    REQUIRE(I.x.toString() == "0");
    REQUIRE(I.y.toString() == "1");
}
