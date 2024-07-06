#include "minishell.h"


void manual_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

void manual_strcat(char *dest, const char *src) {
    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

char *prompt(void) {
    static char prompt_str[100];
    prompt_str[0] = '\0';

    manual_strcat(prompt_str, RED);
    manual_strcat(prompt_str, "ilyas");
    manual_strcat(prompt_str, RESET);
    manual_strcat(prompt_str, "@");
    manual_strcat(prompt_str, BLUE);
    manual_strcat(prompt_str, "bruski");
    manual_strcat(prompt_str, RESET);
    manual_strcat(prompt_str, ":~$ ");

    return prompt_str;
}

void clear_screen(char **envp) {
    pid_t pid = fork();
    if (pid == 0) {
        char *clear[] = {"/usr/bin/clear", NULL};
        execve("/usr/bin/clear", clear, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void ls_screen(char **envp) {
    pid_t pid = fork();
    if (pid == 0) {
        char *clear[] = {"/usr/bin/ls", NULL};
        execve("/usr/bin/ls", clear, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void exit_screen(char **envp) {
    pid_t pid = fork();
    if (pid == 0) {
        char *clear[] = {"/usr/bin/ls", NULL};
        execve("/usr/bin/exit", clear, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

// void execute_command(char *command, char **envp) {
//     pid_t pid = fork();
//     if (pid == 0) {
//         char *argv[] = {/usr/bin/env, NULL};
//         execve(command, argv, envp);
//         perror("execve");
//         exit(EXIT_FAILURE);
//     } else if (pid > 0) {
//         wait(NULL);
//     } else {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
// }

void handle_sigint() {
    printf("\n");
    char *str = prompt();
    printf("%s", str);
    fflush(stdout);
}

int main(int argc, char **argv, char **envp) {

    struct sigaction sa;
    sa.sa_handler = &handle_sigint;
    sa.sa_flags = SA_RESTART; // Restart interrupted system calls
    sigaction(SIGINT, &sa, NULL);
    clear_screen(envp);
    char *line;
    char *pro;
    argc = 0;
    argv = NULL;
    //char **str;
    int i = 0;
    while (1) {

        pro = prompt();
        line = readline(pro);
        if(line == NULL)
            return 0;
        print_type(line);
        i = 0;
        if (line == NULL) {
            break;
        }
        if (strcmp(line, "clear") == 0) {
            clear_screen(envp);
        }
        if(strcmp(line, "ls") == 0)
        {
            ls_screen(envp);
        }
        if(strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
        // else if(strcmp(line, "env") == 0)
        //     execute_command(line, envp);
        free(line);
    }

    return 0;
}
