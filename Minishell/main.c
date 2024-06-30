#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RESET "\033[0m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define WHITE "\033[0;37m"

// Manually copies the source string to the destination string
void manual_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// Manually concatenates the source string to the destination string
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
    prompt_str[0] = '\0';  // Initialize the string with null terminator

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

int main(int argc, char **argv, char **envp) {
    clear_screen(envp);
    char *line;
    char *pro;

    while (1) {
        pro = prompt();
        line = readline(pro);
        if (line == NULL) {
            break; // Exit on EOF
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
        free(line);
    }

    return 0;
}
