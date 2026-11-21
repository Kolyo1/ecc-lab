#include <catch2/catch_test_macros.hpp>
#include <string>
#include "core/bigint/BigInt.h"
#include "core/curves/WeierstrassCurve.h"
#include "core/curves/CurveParams.h"
#include "core/strategies/DoubleAndAdd.h"
#include "core/strategies/MontgomeryLadder.h"
#include "core/protocols/ECDH.h"
#include "core/protocols/ECDSA.h"
#include "core/defenses/ConstantTimeDefense.h"
#include "core/defenses/DeterministicNonceDefense.h"
#include "core/defenses/PointValidationDefense.h"
#include "core/defenses/StrongCurveDefense.h"
#include "core/defenses/Defender.h"
#include "core/curves/CurveFactory.h"

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

TEST_CASE("ConstantTimeDefense toggles strategy") {
    auto curve = std::make_shared<WeierstrassCurve>(tinyParams());
    ConstantTimeDefense def(curve);
    REQUIRE_FALSE(def.isActive());
    def.apply();
    REQUIRE(def.isActive());
    def.remove();
    REQUIRE_FALSE(def.isActive());
}

TEST_CASE("DeterministicNonceDefense toggles flag") {
    auto curve = std::make_shared<WeierstrassCurve>(tinyParams());
    auto strat = std::make_shared<DoubleAndAdd>();
    auto ecdsa = std::make_shared<ECDSA>(curve, strat);
    DeterministicNonceDefense def(ecdsa);
    REQUIRE_FALSE(def.isActive());
    def.apply();
    REQUIRE(def.isActive());
    def.remove();
    REQUIRE_FALSE(def.isActive());
}

TEST_CASE("PointValidationDefense toggles flag") {
    auto curve = std::make_shared<WeierstrassCurve>(tinyParams());
    auto strat = std::make_shared<DoubleAndAdd>();
    auto proto = std::make_shared<ECDH>(curve, strat);
    PointValidationDefense def(proto);
    REQUIRE_FALSE(def.isActive());
    def.apply();
    REQUIRE(def.isActive());
    REQUIRE(proto->validatePoints() == true);
    def.remove();
    REQUIRE_FALSE(def.isActive());
    REQUIRE(proto->validatePoints() == false);
}

TEST_CASE("StrongCurveDefense toggles curve") {
    CurveFactory::registerStandardCurves();
    auto curve = std::make_shared<WeierstrassCurve>(tinyParams());
    auto strat = std::make_shared<DoubleAndAdd>();
    auto proto = std::make_shared<ECDH>(curve, strat);
    StrongCurveDefense def(proto, curve);
    REQUIRE_FALSE(def.isActive());
    def.apply();
    REQUIRE(def.isActive());
    REQUIRE(proto->curve()->params().name == "secp256k1");
    def.remove();
    REQUIRE_FALSE(def.isActive());
    REQUIRE(proto->curve()->params().name == "tiny");
}

TEST_CASE("Defender enable/disable by name") {
    auto curve = std::make_shared<WeierstrassCurve>(tinyParams());
    Defender defender;
    auto d1 = std::make_shared<ConstantTimeDefense>(curve);
    auto d2 = std::make_shared<PointValidationDefense>(
        std::make_shared<ECDH>(curve, std::make_shared<DoubleAndAdd>()));
    defender.addDefense(d1);
    defender.addDefense(d2);

    REQUIRE_FALSE(d1->isActive());
    defender.enable("ConstantTime");
    REQUIRE(d1->isActive());
    REQUIRE_FALSE(d2->isActive());

    defender.disable("ConstantTime");
    REQUIRE_FALSE(d1->isActive());
}

TEST_CASE("Defense names") {
    auto curve = std::make_shared<WeierstrassCurve>(tinyParams());
    REQUIRE(ConstantTimeDefense(curve).name() == std::string("ConstantTime"));
    REQUIRE(DeterministicNonceDefense(
        std::make_shared<ECDSA>(curve, std::make_shared<DoubleAndAdd>())).name()
        == std::string("DeterministicNonce"));
    REQUIRE(PointValidationDefense(
        std::make_shared<ECDH>(curve, std::make_shared<DoubleAndAdd>())).name()
        == std::string("PointValidation"));
}
