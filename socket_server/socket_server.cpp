#include "../headers/service/CameraSrvData.hpp"
#include "../headers/service/IMUSrvData.hpp"
#include "../headers/IMURawData.hpp"
#include "../headers/service/PowerMonitorSrvData.hpp"
#include "../headers/service/StateMachineSrvData.hpp"
#include "../headers/request/BoolRequest.hpp"
#include "socket_server.hpp"

using boost::asio::local::stream_protocol;

#if (USE_IO_SERVICE_RUN == true)
static std::string generate_json_sample(int which_data);

Server::~Server() {
    socket_.close();
}

Server::Server(std::string socket_name, boost::asio::io_service& io_service)
    : io_service_(io_service),
      acceptor_(io_service, stream_protocol::endpoint(socket_name)),
      socket_(io_service) {
}

void Server::start()
{
    std::cout << "start " << std::endl;
    start_accept();
}

// 接続待機
// ※非同期でもアクセプト待ちで同期処理されるので、ソケットは必ず別のスレッドで実行すること。
void Server::start_accept()
{
    std::cout << "start_accept" << std::endl;
    acceptor_.async_accept(
        socket_,
        boost::bind(&Server::on_accept, this, boost::asio::placeholders::error));
}

// 接続待機完了
void Server::on_accept(const boost::system::error_code& error)
{
    std::cout << "on_accept" << std::endl;
    if (! error) {
#if (PROCESS_COMMAND == true)
        start_receive();
#else
    // 固定(ダミー)の２次メッセージ作成
    std::string result = generate_json_sample(1);
    // インスタンス変数としてバッファを使用しない様に、ここでシェアードポインタの文字列を作成する。
    boost::shared_ptr<std::string> response_data(new std::string(result + "\n"));
    async_write(socket_,
                boost::asio::buffer(*response_data),
                boost::bind(&Server::on_send, this, boost::asio::placeholders::error, response_data));
#endif
    } else {
        error_code = error;
        // ログを残す
        std::cerr << "accept failed: " << error.message() << std::endl;
        socket_.close();
        start();
    }
}

#if (PROCESS_COMMAND == true)
// メッセージ受信
void Server::start_receive()
{
    std::cout << "start_receive" << std::endl;
    // インスタンス変数としてバッファを使用しない様に、ここでシェアードポインタのストリームバッファ作成する。
    boost::shared_ptr<boost::asio::streambuf> receive_data(new boost::asio::streambuf());
    async_read_until(socket_,
                        *receive_data,
                        "\n",
                        boost::bind(&Server::on_receive, this,
                                    boost::asio::placeholders::error, receive_data));
}

// １次メッセージ受信完了 & ２次メッセージ送信
// error : エラー情報
// received_data : 受信したデータ
void Server::on_receive(const boost::system::error_code& error, boost::shared_ptr<boost::asio::streambuf> received_data)
{
    std::cout << "on_receive" << std::endl;
    if (! error) {
        // 今は１次メッセージを使用しない。
        std::string command = boost::asio::buffer_cast<const char*>(received_data->data());

        // ２次メッセージ作成
        std::string result = generate_json_sample(stoi(command));
        // インスタンス変数としてバッファを使用しない様に、ここでシェアードポインタの文字列を作成する。
        boost::shared_ptr<std::string> response_data(new std::string(result + "\n"));
        async_write(socket_,
                    boost::asio::buffer(*response_data),
                    boost::bind(&Server::on_send, this, boost::asio::placeholders::error, response_data));
    } else {
        error_code = error;
        // ログを残す
        std::cerr << "on_receive() Error" << error.value() << std::endl;
//        delete this;
    }
}
#endif

void Server::on_send(const boost::system::error_code& error, boost::shared_ptr<std::string> response_data) {
    std::cerr << "on_send" << std::endl;
    // Continue with the next read
    socket_.close();
    start();
}

void Server::process() {
    io_service_.run();
}

static std::string generate_json_sample(int which_data) {
    std::string result;

    switch (which_data) {
    case 1:
        {// シリアライズ(CameraSrvData)
            CameraSrvData camSrvData;

            camSrvData.dx = 0.1;
            camSrvData.dy = 0.2;
            camSrvData.dtheta = 0.3;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("CameraSrvData", camSrvData));
            }
            result = ss.str();
        }
        break;
    case 2:
        {// シリアライズ(IMUSrvData)
            IMUSrvData imuSrvData;

            imuSrvData.roll = 0.4;
            imuSrvData.pitch = 0.5;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("IMUSrvData", imuSrvData));
            }
            result = ss.str();
        }
        break;
    case 3:
        {// シリアライズ(IMURawData)
            IMURawData imuRawSrvData;

            imuRawSrvData.fx = 0.1;
            imuRawSrvData.fy = 0.2;
            imuRawSrvData.mz = 0.3;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("IMURawData", imuRawSrvData));
            }
            result = ss.str();
        }
        break;
    case 4:
        {// シリアライズ(PowerMonitorSrvData)
            PowerMonitorSrvData powerMonitorSrvData;

            powerMonitorSrvData.powerState = false;
            powerMonitorSrvData.emsState = false;
            powerMonitorSrvData.powerSaveMode = false;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("PowerMonitorSrvData", powerMonitorSrvData));
            }
            result = ss.str();
        }
        break;
    case 5:
        {// シリアライズ(StateMachineSrvData)
            StateMachineSrvData stateMachineSrvData;

            stateMachineSrvData.powerState = false;
            stateMachineSrvData.emsState = 0;
            stateMachineSrvData.runningState = 0;
            stateMachineSrvData.imuState = 0;
            stateMachineSrvData.fx = 0.0;
            stateMachineSrvData.fy = 0.0;
            stateMachineSrvData.mz = 0.0;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("StateMachineSrvData", stateMachineSrvData));
            }
            result = ss.str();
        }
        break;
    case 6:
        {// シリアライズ(EmergencyStop)
            BoolRequest ems;

            ems.name = "EmsStop";
            ems.flag = false;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("BoolRequest", ems));
            }
            result = ss.str();
        }
        break;
    case 7:
        {// シリアライズ(PowerSaveReq)
            BoolRequest ps;

            ps.name = "PowerSave";
            ps.flag = false;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("BoolRequest", ps));
            }
            result = ss.str();
        }
        break;
    case 8:
        {// シリアライズ(ResetMotorReq)
            BoolRequest rm;

            rm.name = "ResetMotor";
            rm.flag = false;

            std::stringstream ss;
            {
                cereal::JSONOutputArchive o_archive(ss);
                o_archive(cereal::make_nvp("BoolRequest", rm));
            }
            result = ss.str();
        }
        break;
    }
    return result;
}
#else
#endif