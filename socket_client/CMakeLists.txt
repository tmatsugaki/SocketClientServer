cmake_minimum_required(VERSION 3.0)
project(unix_domain_socket_client)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.74.0 REQUIRED
             COMPONENTS iostreams serialization date_time system)

add_executable(client socket_client.cpp main.cpp)
# pthread: OpenCVでは必須、bullseye環境では Boost 使用時必須
# fmt: spdlogで必須（ライブラリの構成が変わった際に追加した部分）
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} pthread fmt)
