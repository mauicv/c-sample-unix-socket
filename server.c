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

int main(int argc, char *argv[]) {
  int sockfd, newsockfd, clilen, n;
  struct sockaddr_un addr, cli_addr;
  char buffer[256];
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  bzero((char *) &addr, sizeof(addr));

  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);

  if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    quit_on_error("ERROR on binding");

  listen(sockfd, 5);

  for (;;) {
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) quit_on_error("ERROR on accept");

    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) quit_on_error("ERROR reading from socket");

    printf("%s\n", buffer);

    close(newsockfd);
    if (strcmp(buffer, "quit") == 0) break;

  }


  unlink(addr.sun_path);

  return 0;
}
