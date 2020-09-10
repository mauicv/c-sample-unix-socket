#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCK_PATH "socket"

void quit_on_error(char msg[]) {
  printf("%s\n", msg);
  exit(1);
}

int main(int argc, char* argv[]){
  if (argc<2) quit_on_error("require message to send");

  int sockfd, n, len;
  struct sockaddr_un remote;
  // char buffer[];

  if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    quit_on_error("Failed to create socket!");

  remote.sun_family = AF_UNIX;
  strcpy(remote.sun_path, SOCK_PATH);
  len = strlen(remote.sun_path) + sizeof(remote.sun_family);

  if (connect(sockfd, (struct sockaddr *)&remote, len) == -1)
    quit_on_error("Failure to connect socket!");

  n = write(sockfd, argv[1], strlen(argv[1]));
  if (n = 0) quit_on_error("Message failed to send!");

}
