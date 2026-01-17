# Server usage

1) `SimplENetServer sns(PORT);`

2) `received_data = sns.service();`

3) `sns.send(DATA, CLIENT_ID, RELIABLE);`


# Client usage

1) `SimplENetClient snc(IP, PORT);`

2) `received_data = snc.service();`

3) `snc.send(DATA, RELIABLE);`


# Server example

```cpp
SimplENetServer sns(55555);
for (;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        auto received_data = sns.service();
        if (received_data.size() != 0) {
                for (auto& p : received_data) {
                        std::cout << "Received packet from client " << std::to_string(p.first) << std::endl;
                        std::cout << "^ received packet's data: " << (char*)p.second.data() << std::endl;
                }

                sns.send("Hello from server", sizeof("Hello from server"));
        }
}
```


# Client example

```cpp
SimplENetClient snc("::1", 55555);
snc.send("Hello from client", sizeof("Hello from client"));
for (;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        auto received_data = snc.service();
        if (received_data.size() != 0) {
                for (auto& p : received_data) {
                        std::cout << "Received data: " << (char*)p.data() << std::endl;
                }
        }
}
```