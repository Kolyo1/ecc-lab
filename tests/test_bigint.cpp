#include <catch2/catch_test_macros.hpp>

TEST_CASE("add/sub/mul") {
    BigInt a("123"), b("456");
    REQUIRE((a+b).toString() == "579");
    REQUIRE((b-a).toString() == "333");
    REQUIRE((a*b).toString() == "56088");
}

TEST_CASE("division and mod") {
    BigInt a("100"), b("7");
    REQUIRE((a / b).toString() == "14");
    REQUIRE((a % b).toString() == "2");
}

TEST_CASE("modPow") {
    REQUIRE(BigInt("2").modPow(BigInt("10"), BigInt("1000")).toString() == "24");  // 2^10=1024
}

TEST_CASE("modInverse") {
    BigInt a("3"), m("11");
    REQUIRE((a * a.modInverse(m) % m).toString() == "1");
}

TEST_CASE("negative modInverse normalization") {
    BigInt a("7"), m("11");   // inverse of 7 mod 11 is 8 (7*8=56≡1)
    REQUIRE(a.modInverse(m).toString() == "8");
}

TEST_CASE("large values (256-bit)") {
    BigInt a("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", 16);
    REQUIRE(a.toString(16) == "fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
}
// TODO: tests for bigint