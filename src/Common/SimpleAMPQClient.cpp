#include "SimpleAMPQClient.h"
#include <SimpleAmqpClient/SimpleAmqpClient.h>

namespace mediakit{

SimpleAMPQClient::SimpleAMPQClient(const std::string host, const int port, const std::string username, 
    const std::string password, const std::string vhost)
    : _host(host), _port(port), _username(username), _pwd(password), _vhost(vhost){
    _channel = AmqpClient::Channel::Create(_host, _port, _username, _pwd);
}

SimpleAMPQClient::~SimpleAMPQClient(){
}

void SimpleAMPQClient::declareQueue(const std::string &queue_name, bool passive,
    bool durable, bool exclusive, bool auto_delete){
    _queueName = queue_name;
    _channel->DeclareQueue(queue_name, passive, durable, exclusive, auto_delete);
}

void SimpleAMPQClient::sendMsg(std::string msg){
    _channel->BasicPublish("", _queueName, AmqpClient::BasicMessage::Create(msg));
}

bool SimpleAMPQClient::consumeMsg(AmqpClient::Envelope::ptr_t &envelope, std::string &msg, int timeout){
    bool success = _channel->BasicConsumeMessage(envelope, -1);
    if (success) {
        msg = envelope->Message()->Body();
    }
    return success;
}
} // mediakit

