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
#include <Ws2tcpip.h>




int main(){
WSADATA some_kind_of_data;
WSAStartup(MAKEWORD(2, 2), &some_kind_of_data);


sockaddr_in listen_address;
listen_address.sin_family = AF_INET;
listen_address.sin_port = htons(666);
listen_address.sin_addr.S_un.S_addr = INADDR_ANY;

SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);

bind(listen_socket, (sockaddr*)&listen_address, sizeof(listen_address));

listen(listen_socket, SOMAXCONN);

listen_socket = accept(listen_socket, NULL, NULL);

char buffer[1024]{0};

recv(listen_socket, buffer, sizeof(buffer), 0);

std::cout << buffer << std::endl;

system("pause");
closesocket(listen_socket);
WSACleanup();




}


