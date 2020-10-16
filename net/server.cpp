// Server.cpp

// IP Address: 컴퓨터의 주소
// Port Address: 프로세스의 주소

// Linux/Windows: Socket
//                TCP/IP IPC를 구현한다.
//                C API

// 1. socket 생성(TCP/UDP)
// 2. 소켓에 주소를 지정(bind)
// 3. 연결(listen / aceept)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

int main() {
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	// SOCK_STREAM: TCP
	// SOCK_DGRAM: UDP
	if (sock == -1) {
		printf("sock() failed\n");
		return 1;
	}

	struct sockaddr_in addr = {0, };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int ret = bind(sock, (struct sockaddr*)&addr, sizeof addr);
	if (ret == -1) {
		printf("bind() failed\n");
		return 1;
	}

	listen(sock, 5);

	struct sockaddr_in caddr = {0, };
	socklen_t caddrlen = sizeof caddr;
	int csock = accept(sock, (struct sockaddr*)&caddr, &caddrlen);

	while (1) {
		char buf[] = "Hello, Design Pattern\n";
		write(csock, buf, strlen(buf));
		getchar();
	}

	close(csock); // disconnect
}





