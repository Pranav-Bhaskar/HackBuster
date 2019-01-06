#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<ctime>
#include<cstring>
#include<fstream>
#define file_name "/report.xml"

using namespace std;

void file_maker();

class Conn{
	int sock;
	int port;
	int client_socket;
	unsigned char *ip;
	struct sockaddr_in sin;
	struct sockaddr_in *hack;
	struct sockaddr_storage their_addr;
	socklen_t their_size;
	public:
	Conn(int);
	void sten();
	void report();
};

Conn::Conn(int p = 79){
	this->port = p;
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(this->sock < 0){
		perror("\nERROR : Couldnot create socket.\n");
		return ;
	}
	
	this->sin.sin_family = AF_INET;
	this->sin.sin_port = htons(this->port);
	this->sin.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sock, (struct sockaddr *) &sin, sizeof(sin)) == -1){
		perror("\nERROR : Couldnot get to bind on port.\n");
		return ;
	}
	
	listen(sock, 10);
	
	this->sten();
}

void Conn::sten(){
	while(true){
		this->their_size = sizeof(their_addr);
		this->client_socket = accept(this->sock, (struct sockaddr *)&their_addr, &their_size);
		if(this->client_socket < 0){
			perror("\nERROR : Couldnot connect to the client.\n");
			close(this->sock);
			return ;
		}
		this->report();
		shutdown(this->client_socket, SHUT_RDWR);
	}
	close(this->sock);
}

void Conn::report(){
	time_t now = time(0);
	char* dt = ctime(&now);
	
	if (dt[strlen(dt)-1] == '\n') dt[strlen(dt)-1] = '\0';
	
	char IP[NI_MAXHOST];
	char PORT[NI_MAXSERV];
	
	int rc = getnameinfo((struct sockaddr *)&their_addr, their_size, IP, sizeof(IP), PORT, sizeof(PORT), NI_NUMERICHOST | NI_NUMERICSERV);
	
	file_maker();
	
	if(rc == 0){
		ofstream f;
		f.open(file_name, ios::app);
		f << "<Attack time=\"" << dt << "\">\n\t<Victim PORT=\"" << this->port << "\"/>\n\t<Attacker IP=\"" << IP << "\" PORT=\"" << PORT << "\"/>\n</Attack>\n";
	}
	system("zenity --width=300 --alert --title \"Alert\" --text \"There has been a potential-attack on you.\nFor details check\nDirectory: /\nFILE: report.xml\n\" &");
}

void file_maker(){
	ifstream f(file_name);
	if(f.good())
		return ;
	f.close();
	ofstream file;
	file.open(file_name);
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE ipunlocker>\n<?xml-stylesheet type=\"text/xsl\"?>\n";
	file.close();
}

int main(int argc, char const* argv[]){
	int port = 0;
	if(argc == 2){
		int i = -1;
		while(argv[1][++i] != '\0'){
			if((argv[1][i] >= '0') && (argv[1][i] <= '9'))
				port = (port * 10) + argv[1][i] - '0';
			else
				break;
		}
	}
	if((port > 0) && (port < 9000))
		Conn c(port);
	else
		Conn c;		
	return 0;
}
