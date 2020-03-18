#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void)
{
    
    int should_run = 1; /*flag to determine when to exit program*/
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
        char *arg[MAX_LINE/2+1]={NULL};/*command line arguments*/
        char inputBuffer[MAX_LINE]={0};
        read(STDIN_FILENO, inputBuffer, MAX_LINE);
        int p = 0, wait = 1;
        char *cmd;
        int pid;
        cmd = strtok(inputBuffer, " \t\r\n\a");
        while(cmd != NULL)
        {
            arg[p] = cmd;
            p++;
            cmd = strtok(NULL, " \t\r\n\a");
        }
        if(strcmp(arg[0], "exit") == 0)
        {
            should_run = 0;
        }
        //printf("%d",should_run);
        if(arg[p-1][0] == '&')
        {
            arg[p-1] = NULL;
            wait = 0;
        }
        pid = fork();
        if(pid == 0)
        {
            execvp(arg[0], arg);
        }
        else
        {
            int status;
            if(wait)
                waitpid(pid, &status, 0);
        }
        
        //printf("%d",wait);
        
    }
    
    return 0;
}

