#include  "minishell.h"



// int CountNumberPipes(t_token *token)
// {
//     t_token *temp = token;
//     int countPipe = 0;
//     //printf("J'ai entree\n");
//     while (token)
//     {  
//         if (!strcmp(token->type , "pipe"))
//             countPipe++;
//         //printf("token type : %s\n", token->type);
//         token = token->next;
//     }
//     //printf("Number of pipes = %d", countPipe);
//     return (countPipe);
// }


// void execute(t_token *token)
// {
//     // how can i execute ?;

//     /*
//         split command into nodes pipe if number of pipes > 0; 1;
//             else (execute last) command;

//         in every small execute;

//             *** check if the command is a buitl in;
//             *** i need to have the input and out file;
//                 *** check if there is herdoc;
//             *** list of command;
//             *** save exit status;
//             *** create files in redirection;
            
        
//     */

   /*
        small execute;

        1 - get cmd as double pointer; 
                if cmd is builtin execute built in;
        2 - get input and output file;
            if (heredoc)
                in = herdoc file;
            else if (< )  input =  file after < 
            else in = entree standart;
        3 - dup entree sortie;
        4 - execute;  save exit status;

        //
        whats list i need;

        tokens;
        Path;
        env;
        env_export;
        inputfile;
        output;
        exit status;


*/
// }


char	**get_paths()
{
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
    if (!paths)
        return (NULL);
    return (paths);
}



t_exec *initexec(char **env)
{
    t_exec *exec;

    exec = malloc (sizeof (t_exec ));
    if (!exec)
        return (NULL);
    exec->env = init_env(env);
    exec->Paths = get_paths();
    exec->tokens = NULL;
    exec->cmd = NULL;
    exec->exit_status = 0;
    return (exec);
}



void execute(t_exec *exec)
{
    int i = 0;

    while (exec->Paths[i])
    {
        printf("%s\n", exec->Paths[i]);
        i++;
    }
    
}