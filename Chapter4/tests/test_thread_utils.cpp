#include "../thread_utils.h"
#include <cassert>

void test_setThreadCore() {
    // Test setting affinity for current thread
    assert(Common::setThreadCore(0) == true);

    // Test setting affinity for invalid core
    assert(Common::setThreadCore(100) == false);
}

void test_createAndStartThread() {
    // Test creating and starting a thread
    auto t = Common::createAndStartThread(0, "test_thread", []() {
        std::cout << "Hello from test thread!" << std::endl;
    });
    t->join();
    delete t;

    // Test creating and starting a thread with arguments
    int x = 5;
    t = Common::createAndStartThread(0, "test_thread_args", [](int a) {
        std::cout << "Hello from test thread with argument " << a << "!" << std::endl;
    }, x);
    t->join();
    delete t;
}

int main() {
    test_setThreadCore();
    test_createAndStartThread();
    return 0;
}