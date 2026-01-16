#include <thread>
#include <iostream>

#include "../SimpleNetServer.hpp"


int main() {
try {
        SimplENetServer sns(55555);
        for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                std::vector<SimplENetServer::Packet> received_data = sns.service();
                if (received_data.size() != 0) {
                        for (SimplENetServer::Packet& p : received_data) {
                                std::cout << "Received packet type: " << std::to_string(p.packet_type) << std::endl;
                                std::cout << "Received packet data: " << (char*)p.data.data() << std::endl;
                        }

                        const std::string reply = "Hello from server";
                        sns.send(
                                std::vector<uint8_t>(reply.begin(), reply.end()),
                                SimplENetServer::SEND_ALL,
                                true,
                                111
                        );
                }
        }

        return 0;
} catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        exit(1);
}
}