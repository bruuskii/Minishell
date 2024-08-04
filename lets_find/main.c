#include "minishell.h"

t_exec *g_exec = NULL;

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
        execvp("exit", envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}


void handle_sigint() {
    printf("\n");
    char *str = prompt();
    printf("%s", str);
    fflush(stdout);
}

// void    *_malloc(size_t size)
// {
//     void *ptr;
//     ptr = malloc(size);
//     if (!ptr)
//         return NULL;
//     return ptr;
// }

int main(int argc, char **argv, char **envp) {

    struct sigaction sa;
    // t_exec *exec = NULL;
    sa.sa_handler = &handle_sigint;
    sa.sa_flags = SA_RESTART; // For Ctr C
    sigaction(SIGINT, &sa, NULL);
    clear_screen(envp);
    char *line;
    char *pro;
    // exec = initexec(envp);
    g_exec = initexec(envp);
    increment_shell_level(g_exec->env);
    (void)argc;
    (void)argv;
    //int i = 0;
    while (1) 
    {
        
        pro = prompt();
        //print_env(g_exec->env);
        line = readline(pro);
        if(!line)
        {
            printf("exit\n");
            break;
        }
        if(strlen(line) > 0)
        {
            add_history(line);
            print_type(line, g_exec->env, &g_exec->tokens, &g_exec->cmd);
            printf("I'm in execute :\n");
            if (!g_exec->cmd)
                printf("No command to execute\n");
            else
            {
                execute(g_exec, envp);
            }
                
        }
        //i = 0;
         if (strcmp(line, "clear") == 0)
             clear_screen(envp);
        // // if(strcmp(line, "ls") == 0)
        // //     ls_screen(envp);
         if (strcmp(line, "env") == 0)
            print_env(g_exec->env, 0);
        // if(strcmp(line, "pwd") == 0)
        //     pwd(exec->env);
        if(strcmp(line, "exit") == 0)
        {
            //free(line);
            break;
        }
        // printf("exit status :%d:\n", g_exec->exit_status);
    }

    return 0;
}
