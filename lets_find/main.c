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

void    *_malloc(size_t size)
{
    void *ptr;
    ptr = malloc(size);
    if (!ptr)
        return NULL;
    return ptr;
}



<<<<<<< HEAD
    struct sigaction sa;
    sa.sa_handler = &handle_sigint;
    sa.sa_flags = SA_RESTART; // For Ctr C
    sigaction(SIGINT, &sa, NULL);
    clear_screen(envp);
    char *line;
    char *pro;
    t_env *env = init_env(envp);
    increment_shell_level(env);
    (void)argc;
    (void)argv;
    //int i = 0;
    t_token *token = NULL;
    while (1) 
    {

        pro = prompt();
        line = readline(pro);
        if(!line)
        {
            printf("exit\n");
            break;
        }
        if(strlen(line) > 0)
        {
            add_history(line);
            print_type(line, env, token);
        }
        //i = 0;
        if (strcmp(line, "clear") == 0)
            clear_screen(envp);
        if(strcmp(line, "ls") == 0)
            ls_screen(envp);
        if (strcmp(line, "env") == 0)
            print_env(env);
        if(strcmp(line, "pwd") == 0)
            pwd(env);
        if(strcmp(line, "exit") == 0)
        {
            //free(line);
            break;
        }
        //free(line);
    }
=======

int main(int argc, char **argv, char **envr)
{
    (void)argc;
    (void)argv;
    t_env *env = init_env(envr);
    t_env *export_list = init_env(envr);//printf("before seg\n");
    char **cmd = malloc (sizeof(char *));  cmd[0] = malloc(10); strcpy(cmd[0], "AchrafIn");cmd[1] = NULL;
    
    export(env, export_list, cmd);
    // strcpy(cmd[0], "hamada");
    // ft_export(env, export_list, cmd);
    // ft_export(env, export_list, cmd);
    print_env(export_list);
>>>>>>> 628ecaadbda264eac315d8008223f1feeaf7fec3

    //print_env(env);
}


//

// int main(int argc, char **argv, char **envp) {

//     struct sigaction sa;
//     sa.sa_handler = &handle_sigint;
//     sa.sa_flags = SA_RESTART; // For Ctr C
//     sigaction(SIGINT, &sa, NULL);
//     clear_screen(envp);
//     char *line;
//     char *pro;
//     t_env *env = init_env(envp);
//     increment_shell_level(env);
//     argc = 0;
//     argv = NULL;
//     int i = 0;
//     t_token *token = NULL;
//     while (1) 
//     {

//         pro = prompt();
//         line = readline(pro);
//         if(!line)
//         {
//             printf("exit\n");
//             break;
//         }
//         if(strlen(line) > 0)
//         {
//             add_history(line);
//             print_type(line, env, token);
//         }
//         i = 0;
//         if (strcmp(line, "clear") == 0)
//             clear_screen(envp);
//         if(strcmp(line, "ls") == 0)
//             ls_screen(envp);
//         if (strcmp(line, "env") == 0)
//             print_env(env);
//         if(strcmp(line, "pwd") == 0)
//             pwd(env);
//         if(strcmp(line, "exit") == 0)
//         {
//             //free(line);
//             break;
//         }
//         //free(line);
//     }

//     return 0;
// }
