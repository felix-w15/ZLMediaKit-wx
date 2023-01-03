#ifndef COMMON_SIMPLEAMPQCLIENT_H
#define COMMON_SIMPLEAMPQCLIENT_H

#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

namespace mediakit {

class SimpleAMPQClient
{
private:
    /* data */
    std::string _host;
    int _port;
    std::string _username;
    std::string _pwd;
    std::string _vhost;
    std::string _queueName;
    AmqpClient::Channel::ptr_t _channel;
public:
    SimpleAMPQClient(const std::string host, const int port, const std::string username, 
        const std::string password, const std::string vhost = "/");
    ~SimpleAMPQClient();
    void declareQueue(const std::string &queue_name, bool passive = false,
                           bool durable = true, bool exclusive = false,
                           bool auto_delete = false);
    void sendMsg(std::string msg);
    bool consumeMsg(AmqpClient::Envelope::ptr_t &envelope, std::string &msg, int timeout = -1);

    std::string recvMsg();
};

}


#endif //COMMON_SIMPLEAMPQCLIENT_H