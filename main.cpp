#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
//htons() for port nums
//htonsl() for ip addresses and other ints
//make sure buffer before cal of send()

//ip checker function to v specific ip valid||not 
bool ipvalidcheck(const char* socky) {
  int socker = socket(AF_INET, SOCK_STREAM, 0);
    
  if (socker == -1){
        std::cerr << "failed socket creation" << std::endl;
        return false;
    }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);
//converts string ip to binary fo read
  if(inet_pton(AF_INET, socky, &addr.sin_addr) <= 0){
    std::cerr << "ip address invalid" << std::endl;
  close (socker);   //close socket before return
  return false;
  }
  //connect to ip
  int connection = connect(socker, (struct sockaddr*)&addr, sizeof addr);
  if (connection <= -1){ 
    std::cerr << "error connecting" << std::endl;
  }
  else {
    std::cout << "ip address is valid " << std::endl;
  }
  close(socker);
  return true;
}
// port checker for given port on ip is accessible 
bool portchecker(const char* socky, int port){
    int socker = socket(AF_INET, SOCK_STREAM, 0);
    if (socker == -1 ){
        std::cerr << "socket creation failed" << std::endl; 
        return false;
    }
//similar ip func just sock checkign
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(inet_pton(AF_INET, socky, &addr.sin_addr) <= 0){
    std::cerr << "ip address invalid" << std::endl;
    close (socker);   //close socket before return
    return false;
    }
    else {
        std::cout << "port is valid " << std::endl;
    }
    return true;
    }
int main(){
    char ip_address[100];   //needs buffer
    int port_number;            
    std::cout << "Enter ip address: ";
    std::cin >> ip_address;
    
    if(!ipvalidcheck(ip_address)){
    std::cerr << "invalid ip " << std::endl;
    return 1;
    }
    std::cout << "Enter port number: ";
    std::cin >> port_number;
    
    if(!portchecker(ip_address, port_number)){
    std::cerr << "invalid port number " << std::endl;
    return 1;
    }
    else {
        return 0;
    }
}
