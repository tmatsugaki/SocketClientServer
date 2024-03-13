cmake_minimum_required(VERSION 3.0)
project(unix_domain_socket_client)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.74.0 REQUIRED
             COMPONENTS iostreams serialization date_time system)

add_executable(client socket_client.cpp main.cpp)
#target_include_directories(client PRIVATE /opt/homebrew/include)
# pthread: OpenCVでは必須、bullseye環境では Boost 使用時必須
# fmt: spdlogで必須（ライブラリの構成が変わった際に追加した部分、C++17で追加された機能）
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} pthread fmt)
