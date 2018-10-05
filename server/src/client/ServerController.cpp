//
// Created by romain on 04/10/18.
//

#include "ServerController.h"
#include "../../../protocol/HelloConnectMessage.h"

void ServerController::defineMessageHandlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::OPCODE] = handler(this, &ServerController::onHello);
}

void ServerController::onConnect(NetworkClient *client) {

}

void ServerController::onDisconnect(NetworkClient *client, error_code const &error) {

}

void ServerController::onHello(NetworkClient *client, HelloConnectMessage *msg) {
    std::string str("1029384765TEYRUFIDJFLSKAMZL");
    sizet i = 27;
    client->getSession()->send(str.c_str(), i);
}
