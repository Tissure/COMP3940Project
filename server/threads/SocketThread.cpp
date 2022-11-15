//
// Created by Admin on 2022-11-14.
//

#include "SocketThread.hpp"
#include <unistd.h>
#include <string>
#include <iostream>
#include "../packets/ServerPacketBuilder.hpp"
#include "../packets/ServerPacketReader.hpp"

#include "../../game/GameInstanceSingleton.hpp"

SocketThread::SocketThread(Socket *sock) : Thread(this) {
//    request.setSocket(sock);
//    request.parse();

    // All input from socket is read at this point.
    this->sock = sock;
}

void SocketThread::run() {
    // TODO route thread
//    UploadServlet endPoint;
//
//    switch (request.getMethod())
//    {
//        case 0:
//            endPoint.doGet(request, response);
//            break;
//        case 1:
//            endPoint.doPost(request, response);
//            break;
//        default:;
//    }
//
    // Create Container to hold message
    vector<char> result;
    // Dump every char from Payload into vector. Vector now holds entire Payload.
//    sock->dump(result);
//    string buildMessage = "";
    string str;
    char *buf;
    while (*(buf = sock->getNext()) > 0) {
        str += buf[0];
    }
    ServerPacketReader read;
    cout << "READING PACKET" << endl;
    cout << str << endl;
    read.readPacket(str);
    Player p = read.getPlayer();
    cout << "RECIEVED PLAYER" << endl;
    cout << "Player id: " << p.getID() << endl;
    cout << "Player x: " << p.getX() << endl;
    cout << "Player y: " << p.getY() << endl;

//    for (char x: result) {
//        buildMessage.append(reinterpret_cast<const char *>(x));

//    }


    //TODO Replace with buiildPacket
    string packet;
    packet.append(BOUNDARY).append(CRLF);
    // append contentType

    packet.append(ServerPacketBuilder::addPlayerBodyPart(1, 2, 3));

    // Delimit End Of Packet
    packet.append(BOUNDARY).append(CRLF).append(CRLF);
    string res = packet;
    char responseCharArray[res.length()];
    strncpy(responseCharArray, res.c_str(), res.length());
    sock->sendResponse(responseCharArray);
}

SocketThread::~SocketThread() {
    delete sock;
}
