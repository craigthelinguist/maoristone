#include "MainGame.h"
#include LIBRARY(SDL.h)






#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

int nonBlocking = 1;
if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) ==-1) {
  printf("failed to set non blocking\n");
  return false;
}

#elif PLATFORM == PLATFORM_WINDOWS

DWORD nonblocking = 1;
if (ioctlsocket(handle, FIONBIO, &nonblocking) != 0) {
  printf("failed to set non blockign\n");
  return false;
}

#endif


#if PLATFORM == PALTFORM_MAC || PLATFORM == PLATFORM_UNIX
close(socket);
#elif PLATFORM == PLATFORM_WINDOWS
closesocket(socket);
#endif

bool InitializeSockets() {
  #if PLATFORM == PLATFORM_WINDOWS
  WSADATA WsaData;
  return WSAStartup (MAKEWORD(2,2), &WsaData) == NO_ERROR;
  #else
  return true;
  #endif
}

void ShutdownSockets() {
  #if PLATFORM == PLATFORM_WINDOWS
  WSACleanup();
  #endif
}

bool send() {
  int sent_bytes = sendto(handle, (const char*)packet_data, packet_size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

  if (sent_bytes != packet_size) {
    printf("failed to send packet\n");
    return false;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(127.0.0.1); // local address
  addr.sin_port = htons(port);
}

bool start() {
  int handle = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (handle <= 0) {
    printf("failed to create socket\n");
    return false;
  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons((unsigned shot) 0);

  if (bind(handle, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0) {
    printf("failed to bind socket\n");
    return false;
  }
}


void receive() {
  while (true) {
    unsigned char packet_data[256];

    unsigned int max_packet_size = sizeof(packet_data);

    #if PLATFORM == PLATFORM_WINDOWS
    typedef int socket_t;
    #endif

    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int bytes = recvfrom(socket, (char*)packet_data, 0, (sockaddr*)&from, &fromLength);

    if (bytes <= 0) {
      break
    }

    unsigned int from_address = ntohl(from.sin_addr.s_addr);

    unsigned int from_port = ntohs(from.sin_port);

    // process received packet
  }
}

int main(int argc, char* argv[]) {
  start();
  send();
  receive();
  return 0;
}
