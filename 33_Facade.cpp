#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

#include <stdio.h>
#include <string.h>

class Socket {
	int sock;
public:
	Socket(int s = -1) : sock(s) {}

	void write(const std::string& s) {
		::write(sock, s.c_str(), strlen(s.c_str()));
	}

	int c_socket() {
		return sock;
	}
};

class ServerSocket {
	int sock;
public:
	ServerSocket(int type) {
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

	Socket accept() {
		struct sockaddr_in caddr = {0, };
		socklen_t caddrlen = sizeof caddr;
		int csock = ::accept(sock, (struct sockaddr*)&caddr, &caddrlen);
		return Socket(csock);
	}

	int c_socket() {
		return sock;
	}

	void close() {
		::close(sock);
	}
};

class TCPServer {
	ServerSocket sock;
	Socket csock;
public:
	TCPServer() : sock(SOCK_STREAM) {}
	~TCPServer() {
		close(sock.c_socket());
		close(csock.c_socket());
	}

	void start(const char* ip, int port) {
		sock.bind("127.0.0.1", 5000);
		sock.listen();
		csock = sock.accept();

		process();
	}

	virtual void process() = 0;

	Socket getSocket() const {
		return csock;
	}
};

//-------------------
// Facade Pattern: 프로그램을 하는데 필요한 클래스와 절차를 단순화 시켜주는
//                 상위 개념의 클래스를 제공하자.
class MyServer : public TCPServer {
public:
	void process() override {
		Socket sock = getSocket();
		while (1) {
			sock.write("Hello, DP\n");
			getchar();
		}
	}
};

int main() {
	MyServer server;
	server.start("127.0.0.1", 5000);
}





#if 0
int main() {
	ServerSocket sock(SOCK_STREAM);

	sock.bind("127.0.0.1", 5000);

	sock.listen();

	Socket csock = sock.accept();
	while (1) {
		csock.write("Hello, DP\n");
		getchar();
	}

	sock.close();
}
#endif
