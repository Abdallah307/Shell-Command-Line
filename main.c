#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>


int main(int argc, char **argv) {
    int *arr[100];
    int sira = 0;
    while(1) {
        printf("$abdallah307: ");
        char str[100];
        char *programCommand;
        char *tkn;
        char * parameters[30];
        char command[100];
        int counter = -1;
        char commandsPath[] = "/bin/";
        scanf("%[^\n]%*c", str);
        tkn = strtok(str, " ");
        programCommand = tkn;
        bool checkRedirectInput = false;
        bool checkRedirectOutput = false;




        while (tkn != NULL) {
            if(counter == -1) {
                counter++;
                continue;
            }
            else {
                parameters[counter] = tkn;
                tkn = strtok(NULL, " ");
                counter++;
            }

        }

        parameters[counter] = NULL;

        if(strcmp(programCommand,"exit")==0){

            _exit(0);
        }



        printf("Parameter of one is : %s\n",parameters[1]);
        char s[100];
        printf("%s\n", getcwd(s, 100));
        if(strcmp(programCommand,"cd")==0){
            chdir(parameters[1]);
            printf("%s\n", getcwd(s, 100));
            continue;
        }
        int outCounter = 0;
        int inCounter = 0;
        while(parameters[outCounter] != NULL){
            if(strcmp(parameters[outCounter],">")==0){
                checkRedirectOutput = true;
                break;
            } else{
                checkRedirectOutput = false;
            }
            outCounter++;
        }

        while(parameters[inCounter] != NULL){
            if(strcmp(parameters[inCounter],"<")==0){
                checkRedirectInput = true;
                break;
            } else{
                checkRedirectInput = false;
            }
            inCounter++;
        }





        int myFork = fork();

        if(myFork != 0) {
            wait(NULL);
        }

        else {
            if(checkRedirectOutput){
                parameters[outCounter] = NULL;
                int file_desc = open(parameters[counter-1],O_WRONLY | O_APPEND);
                dup2(file_desc, 1) ;
                strcpy(command, commandsPath);
                strcat(command, programCommand);
                execvp(command, parameters);
            }
            else if(checkRedirectInput){
                char * tmp = parameters[inCounter+1];
                parameters[inCounter] = tmp;
                parameters[inCounter+1] = NULL;
                strcpy(command, commandsPath);
                strcat(command, programCommand);
                execvp(command, parameters);

            }
            else{
                strcpy(command, commandsPath);
                strcat(command, programCommand);
                execvp(command, parameters);
            }


        }
    }

    return 0;
}
