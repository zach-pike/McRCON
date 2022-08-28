#include <bits/stdc++.h>

#include "rcon/rcon.hpp"

int main(void) {
    using namespace RCON;

    RCONConnection connection("127.0.0.1", 25575);

    std::cout << (connection.connect() ? "Connected!" : "Failed to connect!") << std::endl;

    std::cout << (connection.authenticate("2773") ? "Authenticated!" : "Failed to authenticate") << std::endl;

    while (true) {
        std::cout << "> " << std::flush;

        std::string command;
        std::getline(std::cin, command);

        std::string response = connection.execute(command);

        std::cout << response << std::endl;
    }
}