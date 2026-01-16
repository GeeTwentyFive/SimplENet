#include <thread>
#include <iostream>

#include "../SimpleNetClient.hpp"


int main() {
try {
        SimplENetClient snc("::1", 55555);
        const std::string message = "Hello from client";
        snc.send(
                std::vector<uint8_t>(message.begin(), message.end()),
                true,
                222
        );
        for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                std::vector<SimplENetClient::Packet> received_data = snc.service();
                if (received_data.size() != 0) {
                        for (SimplENetClient::Packet& p : received_data) {
                                std::cout << "Received packet type: " << std::to_string(p.packet_type) << std::endl;
                                std::cout << "Received packet data: " << (char*)p.data.data() << std::endl;
                        }
                }
        }

        return 0;
} catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        exit(1);
}
}