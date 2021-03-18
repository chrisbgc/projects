#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <list>
#include <map>
#include <queue>
#include <functional>
#include <iterator>
#include <unordered_set>
#include <set>
#include "mingw.thread.h"
#include "mingw.mutex.h"
#include <chrono>
#include <vector>
#include <Ws2tcpip.h>


int main(){
WSADATA some_kind_of_data;
WSAStartup(MAKEWORD(2, 2), &some_kind_of_data);

//Connection socket

sockaddr_in connect_address;
connect_address.sin_family = AF_INET;
connect_address.sin_port = htons(666);
inet_pton(AF_INET, "127.0.0.1" , &connect_address.sin_addr);

SOCKET connection_socket = socket(AF_INET, SOCK_STREAM, 0);

connect(connection_socket, (sockaddr*)&connect_address, sizeof(connect_address));

std::string message = "wow, look at my code";

send(connection_socket, message.c_str(), message.size()+1,0);


closesocket(connection_socket);
WSACleanup();
}
