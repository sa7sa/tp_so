
#include "dict.h"
#include <signal.h>

 
int main(){

int s_fd;
int c_fd;
pergunta_t perg;
resposta_t resp;
char c_fifo_fname[50];
char pname[50];
int read_res;

//Cria o FIFO do cliente
printf("\nDigite  o nome de jogadoe: \n");
scanf("%s",pname);
strcpy(perg.nomec,pname);
perg.pid_cliente = getpid();
sprintf(c_fifo_fname, CLIENT_FIFO, perg.nomec);
if(mkfifo(c_fifo_fname, 0777) == -1){
perror("\nmkfifo do FIFO cliente deu erro");
exit(EXIT_FAILURE);
}

fprintf(stderr,"\nFIFO do cliente criado");

s_fd = open(SERVER_FIFO, O_WRONLY);
if(s_fd == -1){
 fprintf(stderr, "\nO servidor não esta a correr\n");
 unlink(c_fifo_fname);
 exit(EXIT_FAILURE);
}
 fprintf(stderr,"\nFIFO do servidor aberto WRITE / BLOCKING");
 
 c_fd = open(c_fifo_fname, O_RDWR);
 if(c_fd == -1){
 perror("\nErro ao abrir o FIFO do cliente");
 close(c_fd);
 unlink(c_fifo_fname);
 exit(EXIT_FAILURE);
 }
 
 
 fprintf(stderr, "\nFIFO do cliente aberto para READ(+Write) Block");
 
 memset(perg.palavra, '\0', TAM_MAX);
 
 

 
 while(1){

printf("\nPalavra a traduzir > ");
scanf("%s",perg.palavra);
if(!strcasecmp(perg.palavra,"fim")){
write(s_fd, &perg, sizeof(perg));
break;
}
// B) Envia a pergunta
write(s_fd, &perg, sizeof(perg));


// c) Obtem a resposta

read_res = read(c_fd, &resp, sizeof(resp));
if(read_res == sizeof(resp))
  printf("\nTraducao -> %s" , resp.palavra);
else
  printf("\nSem resposta ou resposta incompreensivel" "[bytes lidos: %d]", read_res);  
}

close(c_fd);
close(s_fd);
unlink(c_fifo_fname);
return 0;

}
