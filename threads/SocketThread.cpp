//
// Created by Admin on 2022-11-14.
//

#include "SocketThread.hpp"
#include <unistd.h>
#include <string>
#include <iostream>
#include "../server/packets/ServerPacketBuilder.hpp"
#include "../server/packets/ServerPacketReader.hpp"

#include "../game/GameInstanceSingleton.hpp"

SocketThread::SocketThread(Socket *sock) : Thread(this) {
    // All input from socket is read at this point.
    this->sock = sock;
}

void SocketThread::run() {
    string str;
    string pattern;
    Player *p = nullptr;
    int playerId;
    char *buf = new char[1];
    do {
        memset(buf, 0, 1);
        delete p;
        p = nullptr;
        str = "";
        pattern = "";
        while (buf[0] != '\4' && *(buf = sock->getNext()) > 0) {
            if (buf[0] != '\r' && buf[0] != '\n') {
                str += pattern;
                pattern = "";
                str += buf[0];
            } else {
                pattern += buf[0];
            }
        }
//        cout << "END OF WHILE: " << *buf << endl;
        str += pattern;
        p = ServerPacketReader::readPacket(str);
        if (p == nullptr) {
//            cout << "NO PLAYER" << endl;
        } else {
//            cout << "RECIEVED/ PLAYER" << endl;
//            cout << *p << endl;
            playerId = p->getID();
            if (GameInstanceSingleton::getGameInstance().getThreadList().count(playerId) == 0) {
                pair<int, Thread *> pair = make_pair(playerId, this);
                GameInstanceSingleton::getGameInstance().insertThread(pair);
            }
            GameInstanceSingleton::getGameInstance().updatePlayerList(p);
//        //TODO Move to notifyPlayers()
        string packet = ServerPacketBuilder::buildPacket();
        GameInstanceSingleton::getGameInstance().notifyPlayers(packet);
        }

    } while (*buf > 0);
    GameInstanceSingleton::getGameInstance().removePlayer(playerId);
    GameInstanceSingleton::getGameInstance().removeThread(playerId);
    delete p;
    delete[] buf;
    delete this; //Kill thread
}


SocketThread::~SocketThread() {
    cout << "DESTRUCT SOCKET THREAD" << endl;
    delete sock;
}

void SocketThread::send(string packet) {
    sock->sendResponse(packet);
}
