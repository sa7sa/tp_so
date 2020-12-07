
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define  SERVER_FIFO "ser_fifo"

#define  CLIENT_FIFO "cli_%d_fifo"

#define TAM_MAX 50

typedef struct{//cliente -> servidor
 pid_t pid_cliente;
 char palavra[TAM_MAX];
}pergunta_t;

typedef struct{//servidor -> cliente
 char palavra[TAM_MAX];
}resposta_t;

