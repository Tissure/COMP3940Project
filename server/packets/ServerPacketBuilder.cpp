//
// Created by Admin on 2022-11-14.
//

#include "ServerPacketBuilder.hpp"
#include "../../game/GameInstanceSingleton.hpp"

string ServerPacketBuilder::addPlayerBodyPart(const Player &player){
    string playerBody;
    playerBody.append(BOUNDARY).append(CRLF);
    // Header
    playerBody.append("Content-Type:Player").append(CRLF).append(CRLF);
    // Payload (Nothing on this line)
    playerBody.append("id:").append(to_string(player.getID())).append(CRLF);
    playerBody.append("xCoord:").append(to_string(player.getX())).append(CRLF);
    playerBody.append("yCoord:").append(to_string(player.getY())).append(CRLF);
    return playerBody;
}

//TODO change to gameState object for variable types
string ServerPacketBuilder::buildPacket(vector<Player *> &playerList) {
    string packet;
    packet.append(BOUNDARY).append(CRLF);
    // append contentType
    for(Player *p : playerList){
        packet.append(addPlayerBodyPart(*p));
    }
    // Delimit End Of Packet
    packet.append(BOUNDARY).append(CRLF).append(CRLF);

    return packet;
}

string ServerPacketBuilder::addPlayerBodyPart(const int id, const int xCoord, const int yCoord) {
    string playerBody;
    playerBody.append(BOUNDARY).append(CRLF);
    // Header
    playerBody.append("Content-Type:Player").append(CRLF).append(CRLF);
    // Payload (Nothing on this line)
    playerBody.append("id:").append(to_string(id)).append(CRLF);
    playerBody.append("xCoord:").append(to_string(xCoord)).append(CRLF);
    playerBody.append("yCoord:").append(to_string(yCoord)).append(CRLF).append(CRLF);

    return playerBody;
}

string ServerPacketBuilder::buildPacket() {
    string output;
    for (pair<const int, Player> x : GameInstanceSingleton::getGameInstance().getPlayerList()){
        output.append(addPlayerBodyPart(x.second));
    }
    // Delimit End Of Packet
    output.append(BOUNDARY).append(CRLF).append(CRLF);
    output.append("\4");
    return output;
}

string ServerPacketBuilder::addBallBodyPart(Ball ball) {
    string output;
    output.append(BOUNDARY).append(CRLF);
    // Header
    output.append("Content-Type:Ball").append(CRLF).append(CRLF);
    // Payload (Nothing on this line)
    output.append("xCoord:").append(to_string(ball.getXCoord())).append(CRLF);
    output.append("yCoord:").append(to_string(ball.getYCoord())).append(CRLF);
    return output;
}

string ServerPacketBuilder::addPointsBodyPart(Points points) {
    string output;
    output.append(BOUNDARY).append(CRLF);
    // Header
    output.append("Content-Type:Points").append(CRLF).append(CRLF);
    // Payload (Nothing on this line)
    output.append("TeamOnePoints:").append(to_string(points.getTeamOnePoints())).append(CRLF);
    output.append("TeamTwoPoints:").append(to_string(points.getTeamTwoPoints())).append(CRLF);
    return output;
}
