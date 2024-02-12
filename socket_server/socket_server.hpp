#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

/******************************************************************************
 ※ リスンソケットはアクセプト待ちで同期処理されるので、原則的には別のスレッドでの実行となる。
 ※ １次メッセージを処理しない場合は、start_receive(), on_receive() を使用せず、
   on_accept で直接２次メッセージを送信する。
 ******************************************************************************/
#define USE_IO_SERVICE_RUN      true    // true: boost::asio::io_service , false: boost::asio::io_context
#define PROCESS_COMMAND         true    // true: process command , false: fixed response

#if (USE_IO_SERVICE_RUN == true)
class Server {
public:
    Server(std::string socket_name, boost::asio::io_service& io_service);
    ~Server();
    void start();
    void process();

    boost::system::error_code error_code;

private:
    void start_accept();
    void on_accept(const boost::system::error_code& error);
#if (PROCESS_COMMAND == true)
    void start_receive();
    void on_receive(const boost::system::error_code& error, boost::shared_ptr<boost::asio::streambuf> received_data);
#endif
    // ２次メッセージ送信後のハンドラー
    void on_send(const boost::system::error_code& error, boost::shared_ptr<std::string> response_data);

    boost::asio::io_service& io_service_;
    boost::asio::local::stream_protocol::acceptor acceptor_;
    boost::asio::local::stream_protocol::socket socket_;
};
#else
#endif
