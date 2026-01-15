#include <iostream>

#include "../SimpleNetClient.hpp"


int main() {
try {
        SimplENetClient snc("::1", 55555);
        snc.send({7, 2, 7});
        for (;;) {
                std::vector<SimplENetClient::Packet> received_data = snc.service();
                if (received_data.size() != 0) {
                        std::cout
                        << (char*)received_data[0].data.data()
                        << std::endl;
                }
        }

        return 0;
} catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        exit(1);
}
}