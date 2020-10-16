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
	Socket(int s) : sock(s) {}

	void write(const std::string& s) {
		::write(sock, s.c_str(), strlen(s.c_str()));
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

	void close() {
		::close(sock);
	}
};

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
