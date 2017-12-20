/**
 *  LibBoostAsio.cpp
 *  Compile with g++ libboostasio.cpp -o boost_test -lpthread -lboost_system -lamqpcpp
 */

/**
 *  Dependencies
 */
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>


#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>

/**
 *  Main program
 *  @return int
 */
int main()
{

    // access to the boost asio handler
    boost::asio::io_service service(4);

    // create a work object to process our events.
    boost::asio::io_service::work work(service);
    
    // handler for boostasio
    AMQP::LibBoostAsioHandler handler(service);
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://luffy:onepiece@localhost/"));
    AMQP::TcpChannel channel(&connection);


    auto callback = [](const std::string &name, int msgcount, int consumercount) {
        std::cout << "found box      = [" << name << "]" << std::endl;
    };

	// declare hello queue
    channel.declareQueue("hello").onSuccess(callback);

    // I look inside the box named "1111".
    auto startCb = [](const std::string &consumertag) {
        std::cout << "My ID watching = [" << consumertag << "]" << std::endl;
    };
    auto errorCb = [](const char *message) {
        std::cout << "My ID watching failed [" << message << "]" << std::endl;
    };
    auto messageCb = [&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {

        std::string myString(message.body(), message.bodySize());
        std::cout << "find message   = [" << myString << "]" << std::endl;

        channel.ack(deliveryTag);
    };
    channel.consume("hello")
        .onReceived(messageCb)
        .onSuccess(startCb)
        .onError(errorCb);    
    // run the handler
	//
	// <---SIGINT 
    return service.run();
}

