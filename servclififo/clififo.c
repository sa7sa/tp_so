
#include "dict.h"
#include <signal.h>

 
int main(){

int s_fifo_fd;
int c_fifo_fd;
pergunta_t perg;
resposta_t resp;
char c_fifo_fname[25];
int read_res;

//Cria o FIFO do cliente
perg.pid_cliente = getpid();
sprintf(c_fifo_fname, CLIENT_FIFO, perg.pid_cliente);
if( mkfifo(c_fifo_fname, 0777) == -1){
perror("\nmkfifo do FIFO cliente deu erro");
exit(EXIT_FAILURE);
}

fprintf(stderr,"\nFIFO do cliente criado");

s_fifo_fd = open(SERVER_FIFO, O_WRONLY);
if(s_fifo_fd == -1){
 fprintf(stderr, "\nO servidor não esta a correr\n");
 unlink(c_fifo_fname);
 exit(EXIT_FAILURE);
}
 fprintf(stderr,"\nFIFO do servidor aberto WRITE / BLOCKING");
 //
 //
 //
 //
 c_fifo_fd = open(c_fifo_fname, O_RDWR);
 if(c_fifo_fd == -1){
 perror("\nErro ao abrir o FIFO do cliente");
 close(c_fifo_fname);
 exit(EXIT_FAILURE);
 }
 fprintf(stderr, "\nFIFO do cliente aberto para READ(+Write) Block");
 
 memset(perg.palavra, '\0', TAM_MAX);
 
 while(1){

printf("\nPalavra a traduzir > ");
scanf("%s",perg.palavra);
if(!strcasecmp(perg.palavra,"fim"))
break;
// B) Envia a pergunta
write(s_fifo_fd, &perg, sizeof(perg));

// c) Obtem a resposta

read_res = read(c_fifo_fd, &resp, sizeof(resp));
if(read_res == sizeof(resp))
  printf("\nTraducao -> %s" , resp.palavra);
else
  printf("\nSem resposta ou resposta incompreensivel" "[bytes lidos: %d]", read_res);  
}

close(c_fifo_fd);
close(s_fifo_fd);
unlink(c_fifo_fname);
return 0;

}
