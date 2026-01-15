#include <iostream>

#include "../SimpleNetServer.hpp"


int main() {
try {
        SimplENetServer sns(55555);
        for (;;) {
                std::vector<SimplENetServer::Packet> received_data = sns.service();
                if (received_data.size() != 0) {
                        std::cout
                        << (char*)received_data[0].data.data()
                        << std::endl;

                        std::string reply = "Hello";
                        sns.send(std::vector<uint8_t>(reply.begin(), reply.end()));
                }
        }

        return 0;
} catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        exit(1);
}
}