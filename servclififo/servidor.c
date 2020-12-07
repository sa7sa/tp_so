
#include "dict.h"
#include <signal.h>

#define NPALAVRAS 7

char* dicionario[NPALAVRAS][2]={
{"memory",  "memoria"},
{"computer", "computador"},
{"close",  "fechar"},
{"open",  "abrir"},
{"read",  "ler"},
{"write",  "escrever"},
{"file",  "ficheiro"},
};

int s_fifo_fd,c_fifo_fd;

void trataSig(int i){
fprintf(stderr,"\nServidor de dicionario a terminar"
        "(interrompido via teclado)\n\n");
    close(s_fifo_fd);
    unlink(SERVER_FIFO);
    exit(EXIT_SUCCESS);
}

int main(){

pergunta_t perg;
resposta_t resp;

int i,res;
char c_fifo_fname[50];
char * aux;
printf("/nServidor de dicionario/n");
if(signal(SIGINT,trataSig)== SIG_ERR){
perror("\nNao foi possivel configurar o sinal SIGINT\n");
exit(EXIT_FAILURE);
}
fprintf(stderr, "\nSignal SIGINT configurado");

res = mkfifo(SERVER_FIFO, 0777);
if (res == -1){
perror("\nmkfifo do FIFO servidor deu erro");
exit(EXIT_FAILURE);
}
fprintf(stderr, "\nfIFO servidor criado");


s_fifo_fd = open(SERVER_FIFO, O_RDWR);
if (s_fifo_fd == -1){
perror("\nmkErro ao abrir FIFO servidor(RDWR/blocking)");
exit(EXIT_FAILURE);
}
 fprintf(stderr, "\nFIFO aberto para READ (+WRITE) bloqueante");
 
 while (1){
 
 res = read(s_fifo_fd, &perg, sizeof(perg));
 if(res < sizeof(perg)){
   fprintf(stderr,"\nRecebida pergunta incompleta " "[bytes lidos: %d]", res);
   continue;
 }
 fprintf("\nRecebido [%s]", perg.palavra);
 
strcpy(resp.palavra, "DESCONHECIDO");

 for(i=0;i<NPALAVRAS;i++)
   if(!strcasecmp(perg.palavra,dicionario[i][0])){
      strcpy(resp.palavra,dicionario[i][1]);
      break;
   }
     
   fprintf(stderr, "\nResposta [%s]", resp.palavra);

  sprintf(c_fifo_fname, CLIENT_FIFO, perg.pid_cliente);
  
  c_fifo_fd = open(c_fifo_fname, O_WRONLY);
  
  if(c_fifo_fd == -1)
    perror("\Erro no open - Minguem qis a resposta");
    else{
      fprintf(stderr, "\nFIFO cliente berto para WRITE");
      
      close(c_fifo_fd);
      fprintf(stderr,"\nFIFO Cliente fechado");
    
    }

 }

   close(s_fifo_fd);
   unlink(SERVER_FIFO);
   return 0;
   
   
   }


