#include "cli/CliApp.h"
#include <vector>
#include <string>

int main(int argc, char** argv) {
    std::vector<std::string> args(argv, argv + argc);
    return ecc::CliApp().run(args);
}
