#include "CurveFactory.h"
#include "CurveRegistry.h"
#include "WeierstrassCurve.h"
#include "MontgomeryCurve.h"
#include "EdwardsCurve.h"
#include "core/bigint/BigInt.h"

namespace ecc {
    std::unique_ptr<ICurve> CurveFactory::create(const std::string& name){
        return CurveRegistry::instance().get(name);
    }

    std::unique_ptr<ICurve>  CurveFactory::create(const CurveParams& params, const std::string& form){
        if(form == "Weierstrass") return std::make_unique<WeierstrassCurve>(params);
        if(form == "Montgomery") return std::make_unique<MontgomeryCurve>(params);
        if(form == "Edwards") return std::make_unique<EdwardsCurve>(params);
            return nullptr;
    }

    CurveParams CurveFactory::secp256k1Params() {
    CurveParams p;
    p.name = "secp256k1";
    p.p = BigInt("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", 16);
    p.a = BigInt("0");
    p.b = BigInt("7");
    p.G = Point{
        BigInt("0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798", 16),
        BigInt("0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8", 16),
        false
    };
    p.n = BigInt("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141", 16);
    p.h = BigInt("1");
    return p;
    }

    CurveParams CurveFactory::p256Params() {
        CurveParams p;
        p.name = "P-256";
        p.p = BigInt("0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", 16);
        p.a = p.p - BigInt("3");   // a = -3 mod p
        p.b = BigInt("0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B", 16);
        p.G = Point{
            BigInt("0x6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296", 16),
            BigInt("0x4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5", 16),
            false
        };
        p.n = BigInt("0xFFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551", 16);
        p.h = BigInt("1");
        return p;
    }

    void CurveFactory::registerStandardCurves() {
        CurveRegistry::instance().registerCurve("secp256k1",
            []() { return std::make_unique<WeierstrassCurve>(secp256k1Params()); });
        CurveRegistry::instance().registerCurve("P-256",
            []() { return std::make_unique<WeierstrassCurve>(p256Params()); });
    }


} // namespace ecc
