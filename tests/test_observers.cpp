#include <catch2/catch_test_macros.hpp>
#include <string>
#include "core/observers/ObservableSubject.h"
#include "core/observers/IObserver.h"
#include "core/observers/TimingObserver.h"
#include "core/observers/GuiObserver.h"

using namespace ecc;

// Simple counting observer for testing ObservableSubject
class CountingObserver : public IObserver {
public:
    int valueCount = 0;
    int timingCount = 0;
    void onValue(const std::string&, const std::string&) override { ++valueCount; }
    void onTiming(const std::string&, double) override { ++timingCount; }
};

TEST_CASE("ObservableSubject attach and notifyValue") {
    ObservableSubject subj;
    auto obs = std::make_shared<CountingObserver>();
    subj.attach(obs);
    subj.notifyValue("x", "5");
    REQUIRE(obs->valueCount == 1);
    REQUIRE(obs->timingCount == 0);
}

TEST_CASE("ObservableSubject notifyTiming") {
    ObservableSubject subj;
    auto obs = std::make_shared<CountingObserver>();
    subj.attach(obs);
    subj.notifyTiming("dbl", 12.5);
    REQUIRE(obs->timingCount == 1);
}

TEST_CASE("ObservableSubject detach stops notifications") {
    ObservableSubject subj;
    auto obs = std::make_shared<CountingObserver>();
    subj.attach(obs);
    subj.detach(obs);
    subj.notifyValue("x", "5");
    REQUIRE(obs->valueCount == 0);
}

TEST_CASE("ObservableSubject multiple observers") {
    ObservableSubject subj;
    auto a = std::make_shared<CountingObserver>();
    auto b = std::make_shared<CountingObserver>();
    subj.attach(a);
    subj.attach(b);
    subj.notifyValue("x", "5");
    REQUIRE(a->valueCount == 1);
    REQUIRE(b->valueCount == 1);
}

TEST_CASE("TimingObserver stores samples") {
    TimingObserver to;
    to.onTiming("dbl", 5.0);
    to.onTiming("dbl", 7.0);
    to.onTiming("add", 3.0);
    auto samples = to.samples("dbl");
    REQUIRE(samples.size() == 2);
    REQUIRE(samples[0] == 5.0);
    REQUIRE(samples[1] == 7.0);
    REQUIRE(to.samples("add").size() == 1);
}

TEST_CASE("TimingObserver clear") {
    TimingObserver to;
    to.onTiming("dbl", 5.0);
    to.clear();
    REQUIRE(to.samples("dbl").size() == 0);
}

TEST_CASE("GuiObserver callback forwarding") {
    std::string receivedLabel, receivedValue;
    double receivedTime = -1.0;
    GuiObserver gui(
        [&receivedLabel, &receivedValue](const std::string& l, const std::string& v) {
            receivedLabel = l; receivedValue = v;
        },
        [&receivedLabel, &receivedTime](const std::string& l, double us) {
            receivedLabel = l; receivedTime = us;
        }
    );
    gui.onValue("x", "42");
    REQUIRE(receivedLabel == "x");
    REQUIRE(receivedValue == "42");

    gui.onTiming("dbl", 9.5);
    REQUIRE(receivedLabel == "dbl");
    REQUIRE(receivedTime == 9.5);
}
