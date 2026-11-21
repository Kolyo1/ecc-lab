#include "CliApp.h"
#include "core/curves/CurveFactory.h"
#include "core/protocols/ECDSA.h"
#include "core/strategies/DoubleAndAdd.h"
#include "core/attacks/AttackFactory.h"
#include "core/attacks/AttackConfigBuilder.h"
#include "core/attacks/Attacker.h"
#include <iostream>
#include <string>
#include <memory>

namespace ecc {

int CliApp::run(const std::vector<std::string>& args) {
    CurveFactory::registerStandardCurves();
    if (args.size() < 2) {
        std::cout << "Usage: ecc_cli <command> [options]\n"
                  << "Commands: invalid-curve, pohlig-hellman, timing, nonce-reuse, benchmark\n";
        return 1;
    }

    const std::string& cmd = args[1];

    if (cmd == "invalid-curve")   return cmdInvalidCurve(args);
    if (cmd == "pohlig-hellman")  return cmdPohligHellman(args);
    if (cmd == "timing")          return cmdTiming(args);
    if (cmd == "nonce-reuse")     return cmdNonceReuse(args);
    if (cmd == "benchmark")       return cmdBenchmark(args);

    std::cerr << "Unknown command: " << cmd << "\n";
    return 1;
}

int CliApp::cmdInvalidCurve(const std::vector<std::string>& args) {
    auto curve = CurveFactory::create("secp256k1");
    std::shared_ptr<ICurve> sc(curve.release());
    auto protocol = std::make_shared<ECDSA>(sc, std::make_shared<DoubleAndAdd>());
    auto attack = AttackFactory::create("InvalidCurve", sc, protocol);

    AttackConfig cfg = AttackConfigBuilder().name("InvalidCurve").threads(1).samples(100).build();

    Attacker a;
    a.setAttack(std::shared_ptr<IAttack>(attack.release()));
    auto result = a.launch(cfg);

    std::cout << "Success: " << result.success << "\n";
    std::cout << "Recovered key: " << result.recoveredKey.toString(16) << "\n";
    std::cout << "Elapsed: " << result.elapsedMs << " ms\n";
    for (auto& s : result.steps) std::cout << "  - " << s << "\n";
    return result.success ? 0 : 1;
}

int CliApp::cmdPohligHellman(const std::vector<std::string>& args) {
    auto curve = CurveFactory::create("secp256k1");
    std::shared_ptr<ICurve> sc(curve.release());
    auto protocol = std::make_shared<ECDSA>(sc, std::make_shared<DoubleAndAdd>());
    auto attack = AttackFactory::create("PohligHellman", sc, protocol);

    AttackConfig cfg = AttackConfigBuilder().name("PohligHellman").threads(1).build();

    Attacker a;
    a.setAttack(std::shared_ptr<IAttack>(attack.release()));
    auto result = a.launch(cfg);

    std::cout << "Success: " << result.success << "\n";
    std::cout << "Recovered key: " << result.recoveredKey.toString(16) << "\n";
    std::cout << "Elapsed: " << result.elapsedMs << " ms\n";
    for (auto& s : result.steps) std::cout << "  - " << s << "\n";
    return result.success ? 0 : 1;
}

int CliApp::cmdTiming(const std::vector<std::string>& args) {
    auto curve = CurveFactory::create("secp256k1");
    std::shared_ptr<ICurve> sc(curve.release());
    auto protocol = std::make_shared<ECDSA>(sc, std::make_shared<DoubleAndAdd>());
    auto attack = AttackFactory::create("Timing", sc, protocol);

    AttackConfig cfg = AttackConfigBuilder().name("Timing").samples(200).build();

    Attacker a;
    a.setAttack(std::shared_ptr<IAttack>(attack.release()));
    auto result = a.launch(cfg);

    std::cout << "Elapsed: " << result.elapsedMs << " ms\n";
    for (auto& s : result.steps) std::cout << "  - " << s << "\n";
    return 0;
}

int CliApp::cmdNonceReuse(const std::vector<std::string>& args) {
    auto curve = CurveFactory::create("secp256k1");
    std::shared_ptr<ICurve> sc(curve.release());
    auto protocol = std::make_shared<ECDSA>(sc, std::make_shared<DoubleAndAdd>());
    protocol->generateKeys();
    auto attack = AttackFactory::create("NonceReuse", sc, protocol);

    AttackConfig cfg = AttackConfigBuilder()
        .name("NonceReuse").threads(1)
        .target(protocol->keyPair().privateKey)
        .targetPub(protocol->keyPair().publicKey)
        .build();

    Attacker a;
    a.setAttack(std::shared_ptr<IAttack>(attack.release()));
    auto result = a.launch(cfg);

    std::cout << "Success: " << result.success << "\n";
    std::cout << "Recovered key: " << result.recoveredKey.toString(16) << "\n";
    std::cout << "Elapsed: " << result.elapsedMs << " ms\n";
    for (auto& s : result.steps) std::cout << "  - " << s << "\n";
    return result.success ? 0 : 1;
}

int CliApp::cmdBenchmark(const std::vector<std::string>& args) {
    std::cout << "Benchmark: not yet implemented\n";
    return 0;
}

} // namespace ecc
