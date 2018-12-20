#include "pipe_networking.h"

static void sighandler(int signo) {
  if (signo == SIGINT) {
    system("clear");
    printf("\nThanks for beaning!\n\n");
    exit(EXIT_SUCCESS);
  }
}

int main() {

  signal(SIGINT, sighandler);

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1) {

    // writing message to server
    printf("Give me beans: ");
    char* input = calloc(sizeof(char), 200);
    fgets(input, 200, stdin);
    char* new_line = strchr(input, '\n');
    if (new_line) *new_line = 0;
    write(to_server, input, 200);

    // getting response back from server
    char* response = calloc(sizeof(char), 207);
    read(from_server, response, 207);
    printf("Have some beans: %s\n", response);
  }
}
