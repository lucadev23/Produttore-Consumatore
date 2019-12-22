#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/sem.h>
#include"definitions.h"
#include<string.h>

int main(void){
    char buffer[MAX_LEN];
    int fd;
    int semR,semW;
    int flag=1;

    //semafori
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
    if(SEM_SET(semR,0)==-1){
        fprintf(stderr,"Erorre inizializzazione semaforo Read\n");
        exit(EXIT_FAILURE);
    }
    if(SEM_SET(semW,1)==-1){
        fprintf(stderr,"Erorre inizializzazione semaforo Write\n");
        exit(EXIT_FAILURE);
    }

    while(flag){
        if(SEM_P(semR)==-1){
            fprintf(stderr,"Errore P() Read\n");
            exit(EXIT_FAILURE);
        }
        fd=open(OUTPUT,O_RDONLY);
        if(fd==-1){
            fprintf(stderr,"Errore apertura file\n");
            exit(EXIT_FAILURE);
        }
        memset(buffer,'\0',MAX_LEN);
        read(fd,buffer,MAX_LEN);
        if(!strncmp(buffer,"end",3)){
            flag=0;
            printf("Hai deciso di uscire\n");
        }
        else{
            printf("Hai digitato: %s\n",buffer);
        }
        if(SEM_V(semW)==-1){
            fprintf(stderr,"Errore V() write\n");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
    //deallocazione semafori
    if(SEM_DEL(semW)==-1){
        fprintf(stderr,"Impossibile deallocare semaforo Write\n");
        exit(EXIT_FAILURE);
    }
    if(SEM_DEL(semR)==-1){
        fprintf(stderr,"Impossibile deallocare semaforo Read\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}