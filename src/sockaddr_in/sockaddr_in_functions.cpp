#include "sockaddr_in_functions.h"

#include <netinet/in.h>
#include <string>

size_t sockaddr_in_hash::operator()(const sockaddr_in& addr) const {
	return	std::hash<uint32_t>{}(addr.sin_addr.s_addr) ^
			std::hash<uint16_t>{}(addr.sin_port);
}

bool sockaddr_in_equal::operator()(const sockaddr_in& lhs, const sockaddr_in& rhs) const {
	return	lhs.sin_addr.s_addr == rhs.sin_addr.s_addr &&
			lhs.sin_port == rhs.sin_port;
}

bool compareSockAddrIn(const sockaddr_in& addr1, const sockaddr_in& addr2) {
	// Compare the individual fields
	return	addr1.sin_addr.s_addr == addr2.sin_addr.s_addr &&
			addr1.sin_port == addr2.sin_port;       
}

std::string formatSockAddrIn(const sockaddr_in& address) {
	char clientIP[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(address.sin_addr), clientIP, INET_ADDRSTRLEN);

	// Format the string as "IP:port"
	return std::string(clientIP) + ":" + std::to_string(ntohs(address.sin_port));
}