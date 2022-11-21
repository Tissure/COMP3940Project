//
// Created by Admin on 2022-11-14.
//

#include "ClientPacketReader.hpp"
#include "../../game/GameInstanceSingleton.hpp"
#include <sstream>
#include <iostream>

void ClientPacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    while (getline(stream, current)) {
//        cout << "Line: " << current << endl;
        istringstream breaker{current};
        string first;
        getline(breaker, first, ':');
        string second;
        getline(breaker, second, '\r');
        //TODO add ball and score as well, once those are being sent
        if (current == "Content-Type:Player\r") {
            readPlayer(stream, current);
        }
    }
//    cout << "END READER" << endl;
}

void ClientPacketReader::readPlayer(std::istringstream &stream , std::string &current) {
    auto *p = new Player();
    while (getline(stream, current) && current != "BOUNDARY!!!!!!!\r") {
        istringstream playerBreaker{current};
        string first;
        getline(playerBreaker, first, ':');
        string second;
        getline(playerBreaker, second, '\r');
        if (first == "id") {
            p->setID(stoi(second));
        }
        if (first == "xCoord") {
            p->setX(stoi(second));
        }
        if (first == "yCoord") {
            p->setY(stoi(second));
        }
    }
//            if (p != nullptr) {
    //players.push_back(p);
//            cout << "PLAYER RECV" << endl;
//            cout << *p << endl;
    GameInstanceSingleton::getGameInstance().setPlayer(p);
    if (GameInstanceSingleton::getGameInstance().getLocalPlayer()->getID() == p->getID()) {
        GameInstanceSingleton::getGameInstance().setLocalPlayer(p);
//                }
    }
}
