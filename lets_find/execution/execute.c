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

    exec = malloc (sizeof (t_exec ));
    if (!exec)
        return (NULL);
    exec->env = init_env(env);
    exec->Paths = get_paths();
    exec->cmd = NULL;
    exec->exit_status = 0;
    return (exec);
}

// void setuptestexecute(t_exec *exec)
// {
//     t_cmd *tmp1 = malloc(sizeof(t_exec *));
//     tmp1->infile  = malloc(sizeof(t_filedescription));
//     tmp1->outfile = malloc(sizeof(t_filedescription));
//     tmp1->cmd = ft_split("ls -al", ' ');

//     t_cmd *tmp2 = malloc(sizeof(t_exec *));
//     tmp2->infile  = malloc(sizeof(t_filedescription));
//     tmp2->outfile = malloc(sizeof(t_filedescription));
//     tmp2->cmd = ft_split("Achraf", ' ');

//     // tmp1->nextcmd = NULL;
//     exec->cmd = tmp1;
//     tmp2->next = NULL;
//     exec->cmd->next = tmp2;
// }

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
    // int fdout = 0; // find output;
    // int fdin = 0; // find input
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

void ft_exec_builtin( t_exec *exec, t_cmd *cmd, char **env)
{
    (void)env;
    // if (!strcmp(cmd->cmd[0], "echo"))
    //     return (1);
    // else if (!strcmp(cmd->cmd[0], "cd"))
    //     return (1);
    if (!strcmp(cmd->cmd[0], "pwd"))
        pwd(exec->env);
    else if (!strcmp(cmd->cmd[0], "export"))
        export(exec->env, exec->env_export, cmd->cmd);
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



// void execute( t_exec *exec, char **env)
// {   
//     t_cmd  *cmd = NULL;
//     int countpipes = count_pipes(exec->cmd);
//     int i=0;

//     t_cmd *prev = NULL;
//     cmd = exec->cmd;
//     cmd->isfd0used = 0;
//     cmd->isfrompipe = 0;
//     while (i <= countpipes && cmd)
//     {
//         cmd->isfd0used = 0;
//         cmd->fd = malloc (2 * sizeof (int));
//         if (pipe(cmd->fd) == -1)
//             exit (-1);
//         int pid = fork();
//         if (pid == -1)
//             exit (-2);

//         if (pid == 0)
//         {
//             if (!prev)
//                 close (cmd->fd[0]);
//             if (prev)
//             {
//                 dup2(prev->fd[0], STDIN_FILENO);
//                 close (prev->fd[0]);
//                 prev->isfd0used = 1;
//             }

//             if (cmd->next)
//             {
//                 dup2(cmd->fd[1], STDOUT_FILENO);
//                 close (cmd->fd[1]);
//             }

//             if (itsbuiltin(cmd))
//                 ft_exec_builtin(exec, cmd, env);
//             else
//                 ft_exec(exec, cmd, env);
//             exit (0);
//         }
//         else
//         {
//             if (prev && prev->isfd0used)
//                 close (prev->fd[0]);
//             if (!prev)
//                 close (cmd->fd[0]);
//             if (cmd->next)
//                 close (cmd->fd[1]);
//         }
//         i++;
//         prev = cmd;
//         cmd = cmd->next;
//     }
    

//     cmd = exec->cmd;
//     while (cmd)
//     {
//         wait (NULL);
//         cmd = cmd->next;
//     }
    
//     if (prev)
//     {
//         close (prev->fd[1]);
//         close (prev->fd[0]);
//     }
//     // close all commands;
//     //execute Last cmd;
// }

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

    while (cmd && i <= countpipes)
    {
        fdin = getinputfile(cmd);
        fdout = getoutputfile(cmd);

        // if (cmd->outfile)
        // {   
        //     cmd->outfile->iswithappend = 1;
        //     if (cmd->outfile->iswithappend)
        //         printf("yes with append\n");
        //     else 
        //         printf("not with append\n");
            
        // }
        // else
        //     printf("no output file\n");

        // test herdoc;

        if (cmd->infile)
        {
            if (cmd->infile->isherdoc)
            {
                printf("yes it's a herdoc\n");
            }
        }
        else
        {
            printf("no it's not  a herdoc\n");
        }
        
            

        if (cmd->next)
        {
            cmd->fd = malloc (2 * sizeof(int));
            if (pipe(cmd->fd) == -1)
            {
                perror("pipe error\n");
                exit (EXIT_FAILURE);
            }
        }

        int pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        if (pid == 0)
        {
            (void)fdout;
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

            if (itsbuiltin(cmd))
                ft_exec_builtin(exec, cmd, env);
            else
                ft_exec(exec, cmd, env);
            exit (EXIT_SUCCESS);
        }
        else
        {
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

// test

// void execute( t_exec *exec, char **env)
// {   
//     t_cmd  *cmd = NULL;
//     int countpipes = count_pipes(exec->cmd);
//     int i=0;

//     t_cmd *prev = NULL;
//     cmd = exec->cmd;
//     cmd->isfd0used = 0;
//     cmd->isfrompipe = 0;

//     int fdin;
//     int fdout;

//     while (i <= countpipes && cmd)
//     {
//         fdin = getinputfile(cmd);
//         fdout = getoutputfile(cmd);

        
//         cmd->isfd0used = 0;
//         cmd->fd = malloc (2 * sizeof (int));
//         if (cmd->next)
//         {
//             if (pipe(cmd->fd) == -1)
//             exit (-1);
//         }
        
//         int pid = fork();
//         if (pid == -1)
//             exit (-2);

//         printf("fdin = %d\n", fdin);
//         printf("fdout = %d\n", fdout);


//         if (pid == 0)
//         {
//             // if (!prev && fdin == STDIN_FILENO)
//             //     close (cmd->fd[0]);

//             if (fdin != STDIN_FILENO)
//             {
//                 // close (cmd->fd[0]);
//                 dup2(fdin, STDIN_FILENO); // fd[0] not closed;
//                 close (fdin);
//             }
//             else if (prev)
//             {
//                 dup2(prev->fd[0], STDIN_FILENO); // cmd fd[0]fd[1] not closed;
//                 close (prev->fd[0]);
//                 prev->isfd0used = 1;
//             }
//             else
//             {
//                 close (cmd->fd[0]); // cmd[0] closed;
//             }

//             if (fdout != STDOUT_FILENO)
//             {
//                 // close (cmd->fd[1]);
//                 dup2 (fdout, STDOUT_FILENO);//fd[1] not closed;
//                 close (fdout);
//             }

//             else if (cmd->next)
//             {
//                 dup2(cmd->fd[1], STDOUT_FILENO); // cmd0 not closed;
//                 close (cmd->fd[1]);
//             }

//             else 
//             {
//                 close (cmd->fd[1]);// cmd 1 closd;
//                 // hello //
//             }

//             if (itsbuiltin(cmd))
//                 ft_exec_builtin(exec, cmd, env);
//             else
//                 ft_exec(exec, cmd, env);
//             exit (0);
//         }
//         else
//         {
            
//             if (cmd->next)
//                 close (cmd->fd[1]);

//             if (!prev && fdin == STDIN_FILENO)
//                 close (cmd->fd[0]);

//             if (prev && prev->isfd0used)
//                 close (prev->fd[0]);
            
            
//         }
//         i++;
//         prev = cmd;
//         cmd = cmd->next;
//     }
    

//     cmd = exec->cmd;
//     while (cmd)
//     {
//         wait (NULL);
//         cmd = cmd->next;
//     }
//     if (prev)
//     {
//         close (prev->fd[1]);
//         close (prev->fd[0]);
//     }
    
//     // close all commands;
//     //execute Last cmd;
// }

// void execute( t_exec *exec, char **env)
// {   
//     t_cmd  *command = NULL;
//     int countpipes = count_pipes(exec->cmd);
//     int i=0;

//     t_cmd *prev = NULL;
//     command = exec->cmd;
//     while (i <= countpipes && command)
//     {
//         command->isfrompipe = 0;
//         command->isfd0used = 0;
//         command->fd = malloc(2 * sizeof(int));
//         if (itsbuiltin(command))
//             ft_execute(exec, command, env, 1, prev);
//         else    
//             ft_execute(exec, command, env, 0, prev);
//         prev = command;
//         command = command->next;
//         i++;
//     }
//     if (command)
//     {
//         close (command->fd[1]);
//         close (command->fd[0]);
//     }
//     // close all commands;
//     //execute Last cmd;
// }