
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
    FILE *fp;
    fp=fopen("ProcessList.txt", "a");
    
    fprintf(fp,"Process Has Been Terminated.\n");
    
    fclose(fp);
    
}


int main(int argc, const char * argv[])
{
    
    int result_exit = 0 ;
    
    while (result_exit != 1 )
    {
        
        char x[250];
        int wait_flag=0;
        int i=0;
        int size = 0;
        char *words[250];
        printf("shell->");
        gets(x);
        char *token = strtok(x, " ");
        
        
        
        while (token != NULL )
        {
            
            if (strcmp(token, "exit")==0)
            {
                result_exit = 1;
                return 0;
            }
            
            if (strcmp(token,"&")==0)
            {
                wait_flag=1;
                token = strtok(NULL, " ");
            }
            else
            {
                
                // printf("%s\n",token);
                words[i] = token;
                i++;
                size+=1;
                token = strtok(NULL, " ");
            }
            
            
            
        }
        
        // printf("%d\n",size);
        // printf("%d \n",wait_flag);
        words[size]=NULL;
        if (strcasecmp(words[0],"cd")==0){
            chdir(words[1]);
        }
        else{
            pid_t pid = fork();
            
            
            
            if(pid == 0)
            {
                // printf("I am the child %d my parent %d \n",getpid(),getppid());
                if (execvp(words[0], words)==-1) {
                    printf("......Wrong Command.....\n");
                }
                execvp(words[0],words);
                
            }
            
            else if(pid >0)
            {
                signal(SIGCHLD, handler);
                if(wait_flag==0)
                {
                    wait(NULL);
                }
                // printf("I am the parent %d \n",getpid());
            }
        }
        
        
        
    }
    return 0;
    
}




