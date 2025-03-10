
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024


int main() {
  int sockfd;
  char buffer[MAXLINE];
  char *hello = "Hello from client";
  struct sockaddr_in servaddr;

  
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int n, len;
  char *mess;

  printf("Enter message: \n");
  scanf("%s", mess);

  sendto(sockfd, mess, strlen(mess), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));

  n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
               (struct sockaddr *)&servaddr, &len);
  buffer[n] = '\0';
  printf("Server : %s\n", buffer);

  close(sockfd);
  return 0;
}
