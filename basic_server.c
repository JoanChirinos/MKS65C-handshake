#include "pipe_networking.h"

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("Sesame");
    printf("\n");
    exit(EXIT_SUCCESS);
  }
}

int main() {

  signal(SIGINT, sighandler);

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  while (1) {
    // get client request
    char* input = calloc(sizeof(char), 200);
    int got_response = read(from_client, input, 200);
    printf("got_response: %d\n", got_response);
    if (got_response == 0) {
      from_client = server_handshake( &to_client );
      continue;
    }
    printf("got: %s\n", input);

    // make response: response = input + " beans!"
    char* response = calloc(sizeof(char), 207);
    strcpy(response, input);
    strcat(response, " beans!");

    printf("gonna send back: %s\n", response);

    // send back to client
    write(to_client, response, 207);
  }
}
