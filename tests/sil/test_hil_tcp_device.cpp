#include "raps/hil/hil_tcp_device.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

int main() {
    const int listener = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) return 1;

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = 0;
    if (::bind(listener, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0 ||
        ::listen(listener, 1) != 0) {
        ::close(listener);
        return 1;
    }
    socklen_t address_len = sizeof(address);
    if (::getsockname(listener, reinterpret_cast<sockaddr*>(&address), &address_len) != 0) {
        ::close(listener);
        return 1;
    }

    std::thread rig([listener] {
        const int client = ::accept(listener, nullptr, nullptr);
        if (client >= 0) {
            char byte = 0;
            while (::recv(client, &byte, 1, 0) == 1 && byte != '\n') {}
            constexpr char response[] = "{\"ok\":true}\n";
            (void)::send(client, response, sizeof(response) - 1U, 0);
            ::close(client);
        }
        ::close(listener);
    });

    HilTcpDevice device("127.0.0.1", ntohs(address.sin_port));
    device.set_io_timeout_ms(500U);
    const char payload = 'x';
    const bool written = device.flash_write(0U, &payload, 1U);
    device.disconnect();
    rig.join();

    if (!written) {
        std::cerr << "HIL operation did not auto-connect and complete.\n";
        return 1;
    }
    std::cout << "HIL auto-connect test passed.\n";
    return 0;
}
