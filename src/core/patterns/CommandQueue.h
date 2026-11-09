#pragma once
#include "ICommand.h"
#include <memory>
#include <queue>
#include <mutex>

namespace ecc {

class CommandQueue {
public:
    void push(std::unique_ptr<ICommand> c);
    void runAll();
private:
    std::queue<std::unique_ptr<ICommand>> queue_;
    std::mutex mutex_;
};

} // namespace ecc
