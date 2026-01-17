#include <thread>
#include <iostream>

#include "../SimplENetServer.hpp"


int main() {
try {
        SimplENetServer sns(55555);
        for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                auto received_data = sns.service();
                if (received_data.size() != 0) {
                        for (auto& p : received_data) {
                                std::cout << "Received packet from client " << std::to_string(p.first) << std::endl;
                                std::cout << "^ received packet's data: " << (char*)p.second.data() << std::endl;
                        }

                        sns.send(std::as_bytes(std::span{"Hello from server"}));
                }
        }

        return 0;
} catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        exit(1);
}
}