#include <stdio.h>
#include <winsock.h>

int main(int argc, char *argv[])
{

WSADATA wsaData;
WSAStartup(MAKEWORD(1, 1), &wsaData);

if(argc < 3) {
    printf("Usage: %s <ip/host> <startport> <endport> \n", argv[0]);
    exit(1);
}

struct hostent *he;
struct sockaddr_in host;
int sock;
int start = atoi(argv[2]);
int end = atoi(argv[3]);

if((he=gethostbyname(argv[1])) == NULL) {
    printf("Could not resolve host or ip \n");
    exit(1);
}
printf("Found Host             [ OK ]\n");
printf("Initializing socket    [ OK ]\n");
printf("Connecting to Host     [ OK ]\n");
printf("Scanning %s\n\n", argv[1]);


for(start; start < end; start++) {
if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
}


host.sin_family = AF_INET;
host.sin_port = htons(start);
host.sin_addr = *((struct in_addr *)he->h_addr);

if(connect(sock, (struct sockaddr *)&host, sizeof(struct sockaddr)) == -1) {
    closesocket(sock);
}
else {
    printf("Port %d open \n", start);
    closesocket(sock);
}
}
return 0;
}


