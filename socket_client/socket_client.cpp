#include "../headers/service/CameraSrvData.hpp"
#include "../headers/service/IMUSrvData.hpp"
#include "../headers/IMURawData.hpp"
#include "../headers/service/PowerMonitorSrvData.hpp"
#include "../headers/service/StateMachineSrvData.hpp"
#include "../headers/request/BoolRequest.hpp"
#include "socket_client.hpp"

using boost::asio::local::stream_protocol;

Client::Client(boost::asio::io_service& io_service)
    : io_service_(io_service), socket_(io_service_)
{
}

Client::~Client() {
    socket_.close();
}

void Client::connect()
{
    std::string socket_file = "/tmp/unix_socket";
    socket_.connect(stream_protocol::endpoint(socket_file));
}

void Client::send(char *command_str)
{
    char buff[256];
    snprintf(buff, sizeof(buff), "%s\n", command_str);
    spdlog::info("send(%s)", buff);
    boost::shared_ptr<std::string> data(new std::string(buff));

    command = atoi(command_str);
    // shared_ptr のデータをハンドラに bind してローカル変数扱いとする。
    boost::asio::async_write(socket_, boost::asio::buffer(*data),
        boost::bind(&Client::on_send, this, boost::asio::placeholders::error, data));
}

void Client::on_send(const boost::system::error_code& error, boost::shared_ptr<std::string> data)
{
    if (! error) {
        spdlog::info("send ok");
        boost::shared_ptr<boost::asio::streambuf> receive_data(new boost::asio::streambuf());

        // shared_ptr のデータをハンドラに bind してローカル変数扱いとする。
        boost::asio::async_read_until(socket_, *receive_data, '\n',
            boost::bind(&Client::on_receive, this, boost::asio::placeholders::error, receive_data));
    } else {
        spdlog::warn("send error: %s", error.message());
    }
}

void Client::on_receive(const boost::system::error_code& error, boost::shared_ptr<boost::asio::streambuf> data)
{
    if (! error) {
        std::string json_str = boost::asio::buffer_cast<const char*>(data->data());
        spdlog::info("receive ok :%s", json_str);

        std::stringstream ss(json_str);
        switch (command) {
        case 1:
            {
                CameraSrvData camInData;
                {// デシリアライズ(CameraSrvData)
                    cereal::JSONInputArchive archive(ss);
                    archive(camInData);
                }
//                std::cout << camInData.dx << std::endl;
//                std::cout << camInData.dy << std::endl;
//                std::cout << camInData.dtheta << std::endl;
            }
            break;
        case 2:
            {
                IMUSrvData imuInData;
                {// デシリアライズ(IMUSrvData)
                    cereal::JSONInputArchive archive(ss);
                    archive(imuInData);
                }
//                std::cout << imuInData.roll << std::endl;
//                std::cout << imuInData.pitch << std::endl;
            }
            break;
        case 3:
            {
                IMURawData imuRawInData;
                {// デシリアライズ(IMURawData)
                    cereal::JSONInputArchive archive(ss);
                    archive(imuRawInData);
                }
//                std::cout << imuRawInData.fx << std::endl;
//                std::cout << imuRawInData.fy << std::endl;
//                std::cout << imuRawInData.mz << std::endl;
            }
            break;
        case 4:
            {
                PowerMonitorSrvData powerMonitorInData;
                {// デシリアライズ(PowerMonitorSrvData)
                    cereal::JSONInputArchive archive(ss);
                    archive(powerMonitorInData);
                }
//                std::cout << powerMonitorInData.powerState << std::endl;
//                std::cout << powerMonitorInData.emsState << std::endl;
//                std::cout << powerMonitorInData.powerSaveMode << std::endl;
            }
            break;
        case 5:
            {
                StateMachineSrvData stateMachineSrvData;
                {// デシリアライズ(StateMachineSrvData)
                    cereal::JSONInputArchive archive(ss);
                    archive(stateMachineSrvData);
                }
//                std::cout << stateMachineSrvData.powerState << std::endl;
//                std::cout << stateMachineSrvData.emsState << std::endl;
//                std::cout << stateMachineSrvData.runningState << std::endl;
//                std::cout << stateMachineSrvData.imuState << std::endl;
//                std::cout << stateMachineSrvData.fx << std::endl;
//                std::cout << stateMachineSrvData.fy << std::endl;
//                std::cout << stateMachineSrvData.mz << std::endl;
            }
            break;
        case 6:
            {
                BoolRequest ems;
                {// デシリアライズ(EmsStopReq)
                    cereal::JSONInputArchive archive(ss);
                    archive(ems);
                }
//                std::cout << ems.name << std::endl;
//                std::cout << ems.flag << std::endl;
            }
            break;
        case 7:
            {
                BoolRequest ps;
                {// デシリアライズ(EmsStopReq)
                    cereal::JSONInputArchive archive(ss);
                    archive(ps);
                }
//                std::cout << ps.name << std::endl;
//                std::cout << ps.flag << std::endl;
            }
            break;
        case 8:
            {
                BoolRequest rm;
                {// デシリアライズ(EmsStopReq)
                    cereal::JSONInputArchive archive(ss);
                    archive(rm);
                }
//                std::cout << rm.name << std::endl;
//                std::cout << rm.flag << std::endl;
            }
            break;
        }
    } else {
        spdlog::warn("receive error: %s", error.message());
    }
}
