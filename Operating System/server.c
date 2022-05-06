#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


// in your browser type: http://localhost:8090
// IF error: address in use then change the PORT number
#define PORT 8090

char* hello = "HTTP/1.1 200 OK\nContent-Type: text/plain" \
"Content-Length: 20\n\nMy first web server!";

typedef struct NODE { // 기본 NODE 구조체는 연결리스트와 동일합니다.
	struct NODE* next; // 각 노드는 다음 노드의 주소와
	int data; // 해당 노드의 데이터를 담고 있다.
} Node;


typedef struct QUEUE { // QUEUE 구조체는 head, tail의 주소를 가진다.
	Node* head;
	Node* tail;
	int size; // 사이즈도 가지고 있다.
} Queue;


Queue* initQueue(void) { // QUEUE 구조체 포인터를 초기화 합니다.
	Queue* queue = (Queue*)malloc(sizeof(Queue)); // 큐만큼 크기 할당하고
	queue->head = queue->tail = NULL; // head와 tail 모두 NULL로 초기화 합니다.
	queue->size = 0; // 아직 뭐 없으니까 크기는 0
	return queue; // 변환한 queue를 반환합니다.
}



void resetQueue(Queue* queue) { // 큐의 저장된 모든 노드를 해제하고, 큐를 초기화 합니다.
	Node* tmp;
	Node* cur;
	cur = queue->head; // cur은 큐에 저장된 연결리스트 노드 중 가장 처음 저장된 노드와 동일합니다.

	while (cur != NULL) {
		tmp = cur->next; // tmp에 현재 cur에 저장된 노드의 다음 노드를 저장합니다.
		free(cur);       // 현재 cur에 저장된 노드에 동적할당된 메모리를 해제합니다.
		cur = tmp;       // cur은 다음 노드와 동일해집니다.
	}

	queue->head = queue->tail = cur;
	queue->size = 0;
}


void enQueue(Queue* queue, int data) { // 큐에 원하는 데이터를 저장합니다.
	Node* tmp = (Node*)malloc(sizeof(Node)); // 새 노드 생성 이후
	tmp->data = data; // 임시 구조체 포인터 tmp에 데이터를 저장합니다.
	tmp->next = NULL; // 끝에 삽입하니까 next는 NULL

	if (queue->size == 0) { // 첫 노드이다?
		queue->head = tmp; // 바로 헤드로 설정
	}
	else { // 첫 노드가 아니라면
		queue->tail->next = tmp; // 현재 꼬리노드의 다음이 지금의 노드이다. 
	}                              
	queue->tail = tmp;  // 그리고 이제는 내가 꼬리지
	++queue->size; // Queue 사이즈 늘었어용.

}


void delete(Queue* queue, int num) { // 삭제할겁니다.
	Node* tmp;
	tmp = queue->head; // cur은 가장 먼저 들어온 head를 의미한다.
	queue->head = tmp->next; // 일단 머리를 다음으로 옮기고
	free(tmp); // 기존의 머리는 메모리 해제 해주자.
	--queue->size; // 크기도 줄여줬다.
}

//==================================================//

void* myFunc(void* arg)
{
	int new_socket;
	int tid;
	char buffer[30000] = { 0 };

	new_socket = *((int*)arg);
	read(new_socket, buffer, 30000);
	printf("%s\n", buffer);
	write(new_socket, hello, strlen(hello));
}

int main(int argc, char const* argv[])
{
	Queue* queue = initQueue();

	pthread_t t1;
	int server_fd, new_socket;
	long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

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
	while (1)
	{
		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
		{ // 클라이언트 접속 요청 대기 및 허락, 새 소켓 생성(client socket)
			perror("In accept");
			exit(EXIT_FAILURE);
		}
		pthread_create(&t1, NULL, myFunc, (void*)&new_socket);
		pthread_join(t1, NULL);
		printf("-------------Hello message sent---------------");
		close(new_socket); //소켓 소멸 (client socket)
	}
	return 0;
}
