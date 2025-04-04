cmake_minimum_required(VERSION 3.10)
project(libdataexamples)

add_executable(udpserver udpserver.c)
target_link_libraries(udpserver data pthread)
target_include_directories(udpserver PRIVATE ${PROJECT_SOURCE_DIR}/libdata)

add_executable(tcpserver tcpserver.c)
target_link_libraries(tcpserver pthread)

add_executable(tcpclient tcpclient.c)

add_executable(ini ini.c)
target_link_libraries(ini data pthread)
target_include_directories(ini PRIVATE ${PROJECT_SOURCE_DIR}/libdata)

add_executable(argparser argparser.c)
target_link_libraries(argparser data)
target_include_directories(argparser PRIVATE ${PROJECT_SOURCE_DIR}/libdata)

add_executable(ansicolors ansicolors.c)
target_link_libraries(ansicolors data)
target_include_directories(ansicolors PRIVATE ${PROJECT_SOURCE_DIR}/libdata)

add_executable(ipv6-uint128 ipv6-uint128.c)
