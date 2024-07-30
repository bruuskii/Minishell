#include  "../minishell.h"


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
    
    //token->type == token.pipe
        
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
Achraf

*/
// }

t_exec *initexec(char **env)
{
    t_exec *exec; 

    exec =  (t_exec *)malloc (sizeof (t_exec ));
    if (!exec)
        return (NULL);
    //exec->env_export = (t_env *) malloc (sizeof(t_env));
    exec->env = init_env(env);
    exec->env_export = init_env(env);
    exec->Paths = get_paths();
    exec->cmd = NULL;
    exec->exit_status = 0;
    return (exec);
}

int    getinputfile(t_cmd *cmd)
{
    int fileinfd;
    int size;
    int     i;
    t_filedescriptiom *file;
    
    i = 0;
    size = countfiles(cmd->infile);
    file = cmd->infile;
    if (!size)
        return (0);
    while (i < size && file)
    {
        if (file->isherdoc)
            {
                fileinfd = heredoc(file->delimeter);
            }
        else
        {
            fileinfd = open(file->filename, O_RDONLY, 0777);
            if (fileinfd == -1)
            {
                perror("file not found");//check if i need to open them wakha error;
            }
                
            else
            {
                // close files;
                // if size > 2  // close file while  i=0<size-1;
            }
        }
        file = file->next;
        i++;
    }
    return (fileinfd);
}

int getoutputfile(t_cmd *cmd)
{
    int fileoutfd;
    int size;
    int     i;
    t_filedescriptiom *file;
    int *fd;
    
    i = 0;
    size = countfiles(cmd->outfile);
    file = cmd->outfile; 
    if (!size)
        return (STDOUT_FILENO);
    fd = malloc(size * sizeof(int));
    if (!fd)
        return (0);
    while (i < size && file)
    {
        if (file->iswithappend)
        {
            printf("yes file with append");
            fd[i] = open(file->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
        }
            
        else  
        {
            printf("yes file not append\n");
            fd[i] = open(file->filename, O_RDWR | O_CREAT, 0777);
        }
            
        if (fd[i] == -1)
        {
            perror("file (name) not found");//check if i need to open them wakha error;
        }
        if (file->next)
            close(fd[i]);
        i++;
        file = file->next;
    }
    fileoutfd = fd[i - 1];
    //int j = 0;
    free(fd);
    return (fileoutfd);
}


void ft_exec( t_exec *exec, t_cmd *cmd, char **env)
{
    char *commandpath;

    //= exec->cmd->cmd[0];
    // if (!commandpath)
    //     perror("command not found");
    if (!ft_strchr(cmd->cmd[0], '/'))
	{
		commandpath = get_path(exec, cmd->cmd[0]);
        if (!commandpath)
            {perror("command path not found");
            printf("this is cmd : %s\n", cmd->cmd[0]);}
        if (execve(commandpath, cmd->cmd, env) == -1)
            perror("execve error");
	}
	else
	{
        if (execve(cmd->cmd[0], cmd->cmd, env) == -1)//env to tab;
            perror("commande execve error");
	}
}

void ft_exec_builtin(t_exec **exec, t_cmd *cmd, char **env)
{
    (void)env;
    // if (!strcmp(cmd->cmd[0], "echo"))
    //     return (1);
    // else if (!strcmp(cmd->cmd[0], "cd"))
    //     return (1);
    if (!strcmp(cmd->cmd[0], "pwd"))
        pwd((*exec)->env);
    else if (!strcmp(cmd->cmd[0], "export"))
    {
        export(cmd->cmd);
    }
        
    // else if (!strcmp(cmd->cmd[0], "unset"))
    //     return (1);
    // else if (!strcmp(cmd->cmd[0], "env"))
    //     return (1);
    // else if (!strcmp(cmd->cmd[0], "exit"))
    //     return (1);
}







int itsbuiltin(t_cmd *cmd)
{
    if (!strcmp(cmd->cmd[0], "echo"))
        return (1);
    else if (!strcmp(cmd->cmd[0], "cd"))
        return (1);
    else if (!strcmp(cmd->cmd[0], "pwd"))
        return (1);
    else if (!strcmp(cmd->cmd[0], "export"))
        return (1);
    else if (!strcmp(cmd->cmd[0], "unset"))
        return (1);
    else if (!strcmp(cmd->cmd[0], "env"))
        return (1);
    else if (!strcmp(cmd->cmd[0], "exit"))
        return (1);
    else
        return (0);
}


// void execute(t_exec *exec, char **env)
// {
//     t_cmd *cmd = exec->cmd;
//     t_cmd *prev = NULL;
//     int countpipes = count_pipes(cmd);
//     int i = 0;

//     while (cmd && i <= countpipes)
//     {
//         if (cmd->next)
//         {
//             cmd->fd = malloc(2 * sizeof(int));
//             if (pipe(cmd->fd) == -1)
//             {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         }

//         int pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }

//         if (pid == 0) // Enfant
//         {
//             if (prev)
//             {
//                 dup2(prev->fd[0], STDIN_FILENO);
//                 close(prev->fd[0]);
//                 close(prev->fd[1]);
//             }

//             if (cmd->next)
//             {
//                 close(cmd->fd[0]);
//                 dup2(cmd->fd[1], STDOUT_FILENO);
//                 close(cmd->fd[1]);
//             }

//             if (itsbuiltin(cmd))
//                 ft_exec_builtin(exec, cmd, env);
//             else
//                 ft_exec(exec, cmd, env);
//             exit(EXIT_SUCCESS);
//         }
//         else // Parent
//         {
//             if (prev)
//             {
//                 close(prev->fd[0]);
//                 close(prev->fd[1]);
//                 //free(prev->fd);
//             }
//             prev = cmd;
//             cmd = cmd->next;
//             i++;
//         }
//     }

//     // Attendre tous les enfants
//     // for (int j = 0; j <= countpipes; j++)
//     // {
//     //     wait(NULL);
//     // }
//     int j = -1;
//     while (++j <= countpipes)
//     {
//         wait(NULL);
//             // j++;
//     }

//     // Libérer les descripteurs de fichiers alloués
//     // cmd = exec->cmd;
//     // while (cmd)
//     // {
//     //     if (cmd->fd)
//     //         free(cmd->fd);
//     //     cmd = cmd->next;
//     // }
// }


// test au dessus origine;


void execute(t_exec *exec, char **env)
{
    t_cmd *cmd = exec->cmd;
    t_cmd *prev = NULL;
    int countpipes = count_pipes(cmd);
    int i = 0;

    int fdin= -1;
    int fdout= -1;
    int its_builtin;

    while (cmd && i <= countpipes)
    {
        fdin = getinputfile(cmd);
        fdout = getoutputfile(cmd);

        // test herdoc;
        if (cmd->next)
        {
            cmd->fd = malloc (2 * sizeof(int));
            if (pipe(cmd->fd) == -1)
            {
                perror("pipe error\n");
                exit (EXIT_FAILURE);
            }
        }
        its_builtin = itsbuiltin(cmd);

        int pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        if (pid == 0)
        {
            if (fdin != STDIN_FILENO)
            {
                dup2(fdin, STDIN_FILENO);
                close (fdin);
            }
            else if (prev)
            {
                dup2(prev->fd[0], STDIN_FILENO);
                close (prev->fd[0]);
                close (prev->fd[1]);
            }
            if (fdout != STDOUT_FILENO)
            {
                dup2 (fdout, STDOUT_FILENO);
                close (fdout);
            }
            else if (cmd->next)
            {
                close (cmd->fd[0]);
                dup2(cmd->fd[1], STDOUT_FILENO);
                close (cmd->fd[1]);
            }

            if (!its_builtin)
            {
                ft_exec(exec, cmd, env);
                
            }
            exit (EXIT_SUCCESS);
        }
        else
        {
            if (its_builtin && !cmd->next && !prev)
            {
                ft_exec_builtin(&exec, cmd, env);
            }
            if (prev)
            {
                close (prev->fd[0]);
                close (prev->fd[1]);
                // free(prev->fd);
            }
            prev = cmd;
            cmd = cmd->next;
            i++;
        }
        
    }


        
    int j = -1;
    while (++j <= countpipes)
    {
        wait(NULL);
    }

    

    // Libérer les descripteurs de fichiers alloués
    // cmd = exec->cmd;
    // while (cmd)
    // {
    //     if (cmd->fd)
    //         free(cmd->fd);
    //     cmd = cmd->next;
    // }


}