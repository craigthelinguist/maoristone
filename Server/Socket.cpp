#include "Socket.h"
#include <iostream>

Socket::Socket() {

}

Socket::~Socket() {

}

bool Socket::Open(unsigned short port) {
    this->handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

    if (this->handle <= 0) {
        printf( "failed creating socket\n" );
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (unsigned short) port );

    if (bind( this->handle, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0) {
        printf( "failed to bind socket\n" );
        return false;
    }

    printf("Listening on port %d\n", port);

    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    int nonBlocking = 1;
    if (fcntl( this->handle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1) {
        printf( "failed to set non-blocking\n" );
        return false;
    }

    #elif PLATFORM == PLATFORM_WINDOWS

    DWORD nonBlocking = 0; // set this to 1 if we want blocking disabled - at the moment, 0 means it will block
    // 29th march:: Temporarily set to blocking
    if (ioctlsocket( handle, FIONBIO, &nonBlocking ) != 0) {
        printf( "failed to set non-blocking\n" );
        return false;
    }

    #endif

    return true;
}

void Socket::Close() {
    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    close(this->handle);
    #elif PLATFORM == PLATFORM_WINDOWS
    closesocket(this->handle);
    #endif
}

bool Socket::IsOpen() const {
    return this->handle > 0;
}

bool Socket::Send(const Address & destination, const void * data, int size) {
  sockaddr_in address;
  address.sin_family = AF_INET; // IPv4 Socket
  address.sin_addr.s_addr = htonl(destination.GetAddress()); // local address
  address.sin_port = htons(destination.GetPort());

  int sent_bytes = sendto(handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

  std::cout << "sending to address: " << destination.GetAddress() << " port: " << destination.GetPort() << std::endl;
  std::cout << "sent bytes: " << sent_bytes << std::endl;

  if (sent_bytes != size) {
    printf("failed to send packet\n");
    return false;
  }
  return true;
}

int Socket::Receive(Address & sender, void * data, int size) {
  #if PLATFORM == PLATFORM_WINDOWS
  typedef int socklen_t;
  #endif

  sockaddr_in from;
  socklen_t fromLength = sizeof(from);

  int bytes = recvfrom(this->handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);
  printf("skipped\n");
  unsigned int from_address = ntohl(from.sin_addr.s_addr);
  unsigned int from_port = ntohs(from.sin_port);

  sender = Address(from_address, from_port);

  return bytes;
}
