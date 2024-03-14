cmake_minimum_required(VERSION 3.0)
project(unix_domain_socket_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -I/usr/local/include -I/opt/homebrew/include -L/opt/homebrew/Cellar/fmt/10.2.1_1/lib -O3 -DNDEBUG -march=native")

find_package(Boost 1.74.0 REQUIRED
             COMPONENTS iostreams serialization date_time system)

add_executable(client socket_client.cpp main.cpp)
# target_include_directories(/opt/homebrew/include) # 20240313
# pthread: OpenCVでは必須、bullseye環境では Boost 使用時必須
# fmt: spdlogで必須（ライブラリの構成が変わった際に追加した部分）
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} pthread fmt)
