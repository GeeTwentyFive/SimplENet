#include <thread>
#include <iostream>

#include "../SimplENetClient.hpp"


int main() {
try {
        SimplENetClient snc("::1", 55555);
        snc.send(std::as_bytes(std::span{"Hello from client"}));
        for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                auto received_data = snc.service();
                if (received_data.size() != 0) {
                        for (auto& p : received_data) {
                                std::cout << "Received data: " << (char*)p.data() << std::endl;
                        }
                }
        }

        return 0;
} catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        exit(1);
}
}