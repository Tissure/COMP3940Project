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

string ServerPacketBuilder::buildGameStatePacket() {
    string output;
    for (pair<const int, Player> x : GameInstanceSingleton::getGameInstance().getPlayerList()){
        output.append(addPlayerBodyPart(x.second));
    }
    // Delimit End Of Packet
    output.append(BOUNDARY).append(CRLF).append(CRLF);
    output.append("\4");
    return output;
}

string ServerPacketBuilder::buildDisconnectPacket(const int &playerId) {
    string output;
    output.append(BOUNDARY).append(CRLF);
    // Header
    output.append("Content-Type:Disconnect").append(CRLF).append(CRLF);
    // Payload (Nothing on this line)
    output.append("id:").append(to_string(playerId)).append(CRLF);
    output.append(BOUNDARY).append(CRLF).append(CRLF);
    output.append("\4");
    return output;
}
