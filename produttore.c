#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/sem.h>
#include"definitions.h"
#include<string.h>


int main(void){
    int fd;
    char buffer[MAX_LEN];
    int semR,semW,flag=1;

    semR=semget(SEM_KEY_READ,1,IPC_CREAT | 0666);
    if(semR==-1){
        fprintf(stderr,"Errore creazione semaforo Read\n");
        exit(EXIT_FAILURE);
    }
    semW=semget(SEM_KEY_WRITE,1,IPC_CREAT | 0666);
    if(semW==-1){
        fprintf(stderr,"Errore creazione semaforo Write\n");
        exit(EXIT_FAILURE);
    }

    while(flag){
        if(SEM_P(semW)==-1){
            fprintf(stderr,"Errore P() Write\n");
            exit(EXIT_FAILURE);
        }
        fd=open(OUTPUT,O_CREAT | O_TRUNC | O_WRONLY,0666);
        if(fd==-1){
            fprintf(stderr,"Errore apertura file\n");
            exit(EXIT_FAILURE);
        }
        memset(buffer,'\0',MAX_LEN); //pulisco il buffer
        printf("Digita qualcosa da scrivere su file o esci scrivendo 'end'\n");
        fgets(buffer,MAX_LEN,stdin);
        if(!strncmp(buffer,"end",3)){
            flag=0;
            printf("Hai deciso di uscire\n");
        }
        else{
            printf("Hai scritto: %s\n",buffer);
        }
        write(fd,buffer,(size_t)sizeof(buffer));
        close(fd);
        if(SEM_V(semR)==-1){
            fprintf(stderr,"Errore V() Read\n");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}