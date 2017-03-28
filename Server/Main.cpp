
/** Imports. **/
#include "../Modules.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include "Socket.h"
#include "Address.h"
#include "GameManager.h"



bool InitializeSockets();
void ShutdownSockets();
void CreateSocket();
void SendPacket(const char data[], const int len);
void ReceivePacket();
void FindPlayers();

int port = 30000;
int sendToPort = 30001;
bool sending = false;
const char data[] = "ITSUPGOGOGOO!!";

Socket sock;

GameManager* gameManager;

bool gameCanStart = false; // boolean to indicate when game can start (when 2 people are connected)
std::vector<Address> players; // address of players connected

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

void CreateSocket() {
  if (!sock.Open(port)) {
    printf("Opening socket failed\n");
  }
}

void SendPacket(const char data[], const int len) {
  sock.Send(Address(127,0,0,1, sendToPort), data, len);
}

void ReceivePacket() {
  while(true) {
    Address sender;
    unsigned char buffer[256];
    int bytes_read = sock.Receive(sender, buffer, sizeof(buffer));

    if (bytes_read <= 0) { // if nothing received
      continue;
    }

    // process the packet
    const char* packet_data = (const char*) buffer;
    // printf("%u: %u\n", sender.GetAddress(), sender.GetPort());
    printf("%d: %s\n", bytes_read, packet_data);
  }
}

/**
* This function waits until 2 players have connected. Once 2 players have connected,
* it exits and starts the game.
*/
void FindPlayers() {
  while (!gameCanStart) {
    Address sender;
    // unsigned char buffer[256];
    int bufferLength;

    int read_buffer_Length = sock.Receive(sender, (char*)&bufferLength, sizeof(int)); // get buffer length and store it in bufferLength
    char * buffer = new char[bufferLength];
    int bytes_read = sock.Receive(sender, buffer, bufferLength);

    if (bytes_read <= 0) { // if nothing received
      continue;
    }

    // process the packet
    const char* packet_data = (const char*) buffer;

    if (strcmp(packet_data, "connect") == 0) { // if the packet received is to connect, then store the client's address
      players.push_back(sender); // store the address of the client connecting
      printf("%i Connected\n", players.size());
    }

    if (players.size() == 2) { // if we have two players connected, set gameCanStart to true so the game can begin
      gameManager = new GameManager(players);
      gameCanStart = true;
      printf("2 Players have Connected\n");

      std::string startGame = "start";
      int bufferLength2 = startGame.size();

      // tell the players that game can begin
      for(auto const& a: players) {
        //sock.Send(a, (char*)&bufferLength2, sizeof(int));
      //  sock.Send(a, startGame.c_str(), bufferLength2);
        SendPacket((char*)&bufferLength2, sizeof(int));
        SendPacket(startGame.c_str(), bufferLength2);
      }
    }

    delete[] buffer; // deallocate the memory
  }
}


int main(int argc, char* argv[]) {

    //sending = true;

    //Socket socket();
    InitializeSockets();
    CreateSocket();

    if (sending) {
      //SendPacket(data, sizeof(data));

    }

    if (!gameCanStart) {
      printf("Waiting for players to connect...\n");
      FindPlayers();
    }

    ReceivePacket();


    ShutdownSockets();
    std::cin.get();

    return 0;

}
