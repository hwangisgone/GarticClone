#ifndef SOCKADDR_IN_FUNCTIONS_H
#define SOCKADDR_IN_FUNCTIONS_H

#include <cstddef>
#include <string>
#include <arpa/inet.h>

// Define a custom hash function for sockaddr_in
struct sockaddr_in_hash {
    size_t operator()(const sockaddr_in& addr) const;
};

// Define a custom equality function for sockaddr_in
struct sockaddr_in_equal {
    bool operator()(const sockaddr_in& lhs, const sockaddr_in& rhs) const;
};

bool compareSockAddrIn(const sockaddr_in& addr1, const sockaddr_in& addr2);
std::string formatSockAddrIn(const sockaddr_in& address);


#endif // SOCKADDR_IN_FUNCTIONS_H