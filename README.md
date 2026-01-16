# Server usage

1) `SimplENetServer sns(PORT);`

2) `received_data = sns.service();`

3) `sns.send(DATA, CLIENT_ID, RELIABLE, PACKET_TYPE);`

(`PACKET_TYPE` is an arbitrary number up to 255 of your choosing, to help you differentiate different packet types when receiving on client)


# Client usage

1) `SimplENetClient snc(IP, PORT);`

2) `received_data = snc.service();`

3) `snc.send(DATA, RELIABLE, PACKET_TYPE);`

(`PACKET_TYPE` is an arbitrary number up to 255 of your choosing, to help you differentiate different packet types when receiving on server)


# Server example

```cpp
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
```


# Client example

```cpp
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
```