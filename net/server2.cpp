

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

// 아래 코드를 클래스로 설계해서, 사용자들이 내부적인 사용 방법을
// 모르더라도 사용할 수 있도록 해보자.

// 동일한 이름을 가지는 C 함수를 멤버 함수안에서 호출할 경우,
// 이름을 찾을 수 없다는 오류가 발생한다.
// => 명시적으로 전역 함수라는 것을 지정해야 한다.

class Socket {
	int sock;
public:
	Socket(int type) {
		sock = socket(PF_INET, type, 0);
	}

	void bind(const char* ip, int port) {
		struct sockaddr_in addr = {0, };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);

		::bind(sock, (struct sockaddr*)&addr, sizeof addr);
	}

	void listen() {
		::listen(sock, 5);
	}

	void accept() {
		struct sockaddr_in caddr = {0, };
		socklen_t caddrlen = sizeof caddr;
		int csock = ::accept(sock, (struct sockaddr*)&caddr, &caddrlen);
	}

	void close() {
		::close(sock);
	}
};

int main() {
	Socket sock(SOCK_STREAM);

	sock.bind("127.0.0.1", 5000);

	sock.listen();

	sock.accept();

	sock.close();
}




#if 0
int main() {
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	// SOCK_STREAM: TCP
	// SOCK_DGRAM: UDP

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
#endif





