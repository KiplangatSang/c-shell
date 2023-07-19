#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


#define MAX_COMMAND_LENGTH 110
#define MAX_ARGS 15

int main() {
    char mycommand[MAX_COMMAND_LENGTH];
    char* command_args[MAX_ARGS];
    char* token;
    int parentstatus;

    while (1) {
        printf("My shell> ");
        fgets(mycommand, sizeof(mycommand), stdin);

        // Remove linebreaks from the command
        if (mycommand[strlen(mycommand) - 1] == '\n')
            mycommand[strlen(mycommand) - 1] = '\0';

        // make tokens of the command 
        token = strtok(mycommand, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            command_args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        command_args[i] = NULL;

        // Fork a child  process into the parent process
        pid_t pid = fork();

        if (pid < 0) {
            printf("Failed to fork .\n");
            exit(1);
        } else if (pid == 0) {
            // Child process
            execvp(command_args[0], command_args);
            printf("The command could not found: %s\n", command_args[0]);
            exit(0);
        } else {
            // Let the parent process run with a status 0
            waitpid(pid, &parentstatus, 0);
        }
    }

    return 0;
}
