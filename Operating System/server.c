#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>


// in your browser type: http://localhost:8090
// IF error: address in use then change the PORT number
#define PORT 8090
pthread_mutex_t mutex_lock;

void* action() {
    pthread_mutex_lock(&mutex_lock);
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char* hello = "HTTP/1.1 200 OK\nContent-Type: text/plain" \
        "Content-Length: 20\n\nMy first web server!";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //소켓을 생성하고
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET; // 소켓 주소를 설정한 다음
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero); //메모리를 확보하고


    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) // 소켓을 서버 소켓으로 등록하고
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0) // 서버 소켓을 통해 클라이언트의 접속 요청을 확인하도록 설정하고
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    //while(1){
    printf("\n+++++++ Waiting for new connection ++++++++\n\n");

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    { // 클라이언트 접속 요청 대기 및 허락, 새 소켓 생성(client socket)
        perror("In accept");
        exit(EXIT_FAILURE);
    }

    char buffer[30000] = { 0 };
    valread = read(new_socket, buffer, 30000); // 데이터 송수신(client socket)
    printf("%s\n", buffer);

    write(new_socket, hello, strlen(hello)); // 데이터 송수신(client socket)
    printf("-------------Hello message sent---------------");
    close(new_socket); //소켓 소멸 (client socket)
    //}
    sleep(60); // 얘 잔다!
    pthread_mutex_unlock(&mutex_lock);
}

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    pthread_mutex_init(&mutex_lock, NULL);
    
    pthread_create(&t1, NULL, action, NULL);
    pthread_create(&t2, NULL, action, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
