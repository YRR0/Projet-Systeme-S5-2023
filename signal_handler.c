#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "signal_handler.h"
#include "job_manager.h"
#include "prompt.h"
#include "command_executor.h"

//kill()
/*
int killProjet(int sig, Job job ){
    return 1;
}
int killProjet( Job job ){
    return 1;
}
*/


//JE crois que c'est celui là:
int killProjet(int sig, int pid ){
    return 1;
}

/*
int killProjet(int pid){
    return 1;
}*/



//Je commence par une fonction limitée qui exécute deux commandes à la fois (ne fonction donc qu'avec un seul pipe)
int pipeLimitedTwo( char * c1, char * c2){

    int fd [2];
    int taille1,taille2;
    char** command1=separerParEspaces(c1,&taille1);
    char** command2=separerParEspaces(c2,&taille2);


    if(pipe(fd)<0){
        return 1;
    }

    pid_t pid1=fork();

    if (pid1<0){
        return 2;
    }

    if (pid1==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);

        execute_command(command1[0],command1);
        perror("execute_commande");
        exit(EXIT_FAILURE);
    }else{
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);

        wait(NULL);

        execute_command(command2[0],command2);
        perror("execute_commande");
        return 0;

    }



    return 0;
}
