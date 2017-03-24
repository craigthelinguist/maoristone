#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include<vector>
#include "Address.h"

class GameManager {

public:
    GameManager(const std::vector<Address> players);


private:
    void InitGame();
    unsigned int address;
    unsigned short port;
};

#endif
