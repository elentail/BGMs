#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

struct Session {
	std::shared_ptr<asio::ip::tcp::socket> sock;
	std::unique_ptr<char[]> buf;
	unsigned int buf_size;
};

void callback(const boost::system::error_code& ec,
	std::size_t bytes_transferred,
	std::shared_ptr<Session> s)
{
	if (ec != 0) {
		std::cout << "Error occured! Error code = "
			<< ec.value()
			<< ". Message: " << ec.message();

		return;
	}
	else{
		std::cout <<"contents : " << s->buf.get() << std::endl;
	}
}

void readFromSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
	std::shared_ptr<Session> s(new Session);

	const unsigned int MESSAGE_SIZE = 30;

	s->buf.reset(new char[MESSAGE_SIZE]);

	s->sock = sock;
	s->buf_size = MESSAGE_SIZE;
	s->sock->async_read_some(
		asio::buffer(s->buf.get(), s->buf_size),
		std::bind(callback,
		std::placeholders::_1,
		std::placeholders::_2,
		s));
}

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 21;

	try {
		asio::ip::tcp::endpoint
			ep(asio::ip::address::from_string(raw_ip_address),
			port_num);

		asio::io_service ios;

		std::shared_ptr<asio::ip::tcp::socket> sock(
			new asio::ip::tcp::socket(ios, ep.protocol()));

		sock->connect(ep);

		readFromSocket(sock);

		ios.run();
	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();

		return e.code().value();
	}

	return 0;
}
