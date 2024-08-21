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
    exec->env = init_env(env);
    exec->paths = NULL;
    exec->cmd = NULL;
    exec->exit_status = 0;
    exec->herdoc_sig = -1;
    return (exec);
}

int    getinputfile(t_cmd *cmd)
{
    int fileinfd;
    int size;
    int     i;
    t_filedescriptiom *file;
    int tmpfderror;
    
    i = 0;
    size = countfiles(cmd->infile);
    file = cmd->infile;
    tmpfderror = 0;
    if (!size)
        return (0);
    while (i < size && file)
    {
        if (!*file->filename)
        {
            ft_putstr_fd("bash : ambiguous redirect\n", 2);
            file = file->next;
            i++;
            tmpfderror = -1;
            continue;
        }

        if (file->isherdoc)
        {
            fileinfd = heredoc(file->delimeter);
        }
        else
        {
            fileinfd = open(file->filename, O_RDONLY, 0777);
            if (fileinfd == -1)
            {
                printf(":%d:\n", fileinfd);
                perror("no such file or directory\n");
                tmpfderror = fileinfd;
            }
        }
        file = file->next;
        i++;
    }
    if (tmpfderror == -1)
        return (tmpfderror);
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
            fd[i] = open(file->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
        }
        else  
        {
            fd[i] = open(file->filename, O_RDWR | O_CREAT, 0777);
        }
            
        if (fd[i] == -1)
        {
            perror("file cannot opend");
            return (-1);
        }
        if (file->next)
            close(fd[i]);
        i++;
        file = file->next;
    }
    fileoutfd = fd[i - 1];
    free(fd);
    return (fileoutfd);
}


void    exit_with_message(char *s, int exit_value)
{
    ft_putstr_fd(s, 2);
    exit(exit_value);
}


void    ft_exec_no_path(t_cmd *cmd, char **env, char *commandpath)
{
    commandpath = get_path(cmd->cmd[0]);
    if (!commandpath)
    {
        ft_putstr_fd(cmd->cmd[0], 2);
        exit_with_message(" : command path not found\n", 127);
    }
    if (execve(commandpath, cmd->cmd, env) == -1)
    {
        free(commandpath);
        exit_with_message("execve error\n", 127);
        free_db_arr(env);
    }
}


void ft_exec(t_cmd *cmd)
{
    char *commandpath;
    char    **envtemp;

    if (!cmd->cmd[0])
        return;
    commandpath = NULL;
    envtemp = init_env_arr();
    if (!ft_strchr(cmd->cmd[0], '/'))
	{
		ft_exec_no_path(cmd, envtemp, commandpath);
	}
	else
	{
        if (execve(cmd->cmd[0], cmd->cmd, envtemp) == -1)
        {
            exit_with_message("execve error\n", 127);
            free_db_arr(envtemp);
        } 
	}
}

void ft_exec_builtin(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->cmd[0], "echo"))
    {
        echo(cmd->cmd);
    }
        
    else if (!ft_strcmp(cmd->cmd[0], "cd"))
    {
        cd(cmd->cmd);
    }
    if (!ft_strcmp(cmd->cmd[0], "pwd"))
    {
        pwd();
    }
        
    else if (!ft_strcmp(cmd->cmd[0], "export"))
    {
        export(cmd->cmd);
    }
    else if (!ft_strcmp(cmd->cmd[0], "unset"))
    {
        unset(cmd->cmd);
    }
    else if (!ft_strcmp(cmd->cmd[0], "env"))
    {
        print_env(g_exec->env, 0);
    }
        
    else if (!strcmp(cmd->cmd[0], "exit"))
    {
        ft_exit(cmd->cmd);
    }
}


int itsbuiltin(t_cmd *cmd)
{
    if (!cmd->cmd[0])
        return (0);
    if (!ft_strcmp(cmd->cmd[0], "echo"))
        return (1);
    else if (!ft_strcmp(cmd->cmd[0], "cd"))
        return (1);
    else if (!ft_strcmp(cmd->cmd[0], "pwd"))
        return (1);
    else if (!ft_strcmp(cmd->cmd[0], "export"))
        return (1);
    else if (!ft_strcmp(cmd->cmd[0], "unset"))
        return (1);
    else if (!ft_strcmp(cmd->cmd[0], "env"))
        return (1);
    else if (!ft_strcmp(cmd->cmd[0], "exit"))
        return (1);
    else
        return (0);
}

void set_upfdfiles(int fdin, int fdout, t_cmd *cmd, t_cmd *prev)
{
    if (fdin == -1)
        exit(EXIT_FAILURE);
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
}




void    execute_parent(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
{
    if (exec_utils->its_builtin && !cmd->next && !prev)
    {
        if (exec_utils->fdout != STDOUT_FILENO)
        {
            dup2(exec_utils->fdout, STDOUT_FILENO);
            close (exec_utils->fdout);
            ft_exec_builtin(cmd);
            dup2(exec_utils->savedout, STDOUT_FILENO);
            close (exec_utils->savedout);
        }
        else
            ft_exec_builtin(cmd);
    }
    if (exec_utils->fdin != STDIN_FILENO)
        close (exec_utils->fdin);
    if (prev)
    {
        close (prev->fd[0]);
        close (prev->fd[1]);
    }
}

void    execute_child(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
{
    set_upfdfiles(exec_utils->fdin, exec_utils->fdout, cmd, prev);
    if (!exec_utils->its_builtin)
        ft_exec(cmd);
    else if (!ft_strcmp(cmd->cmd[0], "pwd")  && !cmd->next)
        exit(EXIT_SUCCESS);
    else if (exec_utils->its_builtin && !cmd->cmd[1])
        ft_exec_builtin(cmd);
    exit (EXIT_SUCCESS);
}


void    ft_execute(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
{
    if (cmd->next)
    {
        cmd->fd = malloc (2 * sizeof(int));
        if (pipe(cmd->fd) == -1)
        {
            perror("pipe error\n");
            exit (EXIT_FAILURE);
        }
    }
    exec_utils->its_builtin = itsbuiltin(cmd);
    exec_utils->pid = fork();
    if (exec_utils->pid == -1)
        exit(EXIT_FAILURE);
    if (exec_utils->pid == 0)
        execute_child(exec_utils, cmd, prev);
    else
        execute_parent(exec_utils, cmd, prev);
}


// void    execute_parent(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
// {
//     if (exec_utils->its_builtin && !cmd->next && !prev && (cmd->cmd[1]
//          || !ft_strcmp(cmd->cmd[0], "cd")))
//     {
//         if (exec_utils->fdout != STDOUT_FILENO)
//         {
//             dup2(exec_utils->fdout, STDOUT_FILENO);
//             close (exec_utils->fdout);
//             ft_exec_builtin(cmd);
//             dup2(exec_utils->savedout, STDOUT_FILENO);
//             close (exec_utils->savedout);
//         }
//         else
//             ft_exec_builtin(cmd);
//     }
//     if (exec_utils->fdin != STDIN_FILENO)
//         close (exec_utils->fdin);
//     if (prev)
//     {
//         close (prev->fd[0]);
//         close (prev->fd[1]);
//     }
// }

// void    execute_child(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
// {
//     set_upfdfiles(exec_utils->fdin, exec_utils->fdout, cmd, prev);
//     if (!exec_utils->its_builtin)
//         ft_exec(cmd);
//     else if (exec_utils->its_builtin && !cmd->cmd[1])
//         ft_exec_builtin(cmd);
//     exit (EXIT_SUCCESS);
// }


// void    ft_execute(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
// {
//     if (cmd->next)
//     {
//         cmd->fd = malloc (2 * sizeof(int));
//         if (pipe(cmd->fd) == -1)
//         {
//             perror("pipe error\n");
//             exit (EXIT_FAILURE);
//         }
//     }
//     exec_utils->its_builtin = itsbuiltin(cmd);
//     exec_utils->pid = fork();
//     if (exec_utils->pid == -1)
//         exit(EXIT_FAILURE);
//     if (exec_utils->pid == 0)
//         execute_child(exec_utils, cmd, prev);
//     else
//         execute_parent(exec_utils, cmd, prev);
// }

void    get_exitstatus(t_exec_utils exec_utils)
{
    int j = -1;
    int status;

    while (++j <= exec_utils.countpipes)
    {
        wait(&status);
        if (WIFEXITED(status)) {
            if (!exec_utils.its_builtin)
            {
                g_exec->exit_status = WEXITSTATUS(status);
            }
                
    } else {
        printf("Child process did not terminate normally\n");
    }
    }
}


t_exec_utils init_exec_utils(t_cmd *cmd)
{
    t_exec_utils    exec_utils;

    exec_utils.countpipes = count_pipes(cmd);
    exec_utils.i = 0;
    exec_utils.fdin= -1;
    exec_utils.savedout = dup(STDOUT_FILENO);
    exec_utils.fdout= -1;
    return (exec_utils);
}

void execute(t_exec *exec)
{
    t_cmd *cmd;
    t_cmd *prev;
    t_exec_utils    exec_utils;

    cmd = exec->cmd;
    prev = NULL;
    exec_utils = init_exec_utils(cmd);
    while (cmd && exec_utils.i <= exec_utils.countpipes)
    {
        exec_utils.fdin = getinputfile(cmd);
        exec_utils.fdout = getoutputfile(cmd);
        if (exec_utils.fdin == -1 || exec_utils.fdout == -1)
        {
            cmd = cmd->next;
            exec_utils.i++;
            g_exec->exit_status = 1;
            continue;
        }
        ft_execute(&exec_utils, cmd, prev);
        prev = cmd;
        cmd = cmd->next;
        exec_utils.i++;
    }
    get_exitstatus(exec_utils);
    free_exec(0);
}




// void execute(t_exec *exec, char **env)
// {
//     t_cmd *cmd = exec->cmd;
//     t_cmd *prev = NULL;
//     int countpipes = count_pipes(cmd);
//     int i = 0;
//     int pid;

//     int fdin= -1;
//     int savedout = dup(STDOUT_FILENO);
//     int fdout= -1;
//     int its_builtin;

//     while (cmd && i <= countpipes)
//     {
//         fdin = getinputfile(cmd);
//         fdout = getoutputfile(cmd);

//         if (fdin == -1 || fdout == -1)
//         {
//             cmd = cmd->next;
//             i++;
//             g_exec->exit_status = 1;
//             continue;
//         }
//         if (cmd->next)
//         {
//             cmd->fd = malloc (2 * sizeof(int));
//             if (pipe(cmd->fd) == -1)
//             {
//                 perror("pipe error\n");
//                 exit (EXIT_FAILURE);
//             }
//         }
        
//         its_builtin = itsbuiltin(cmd);
//         pid = fork();
//         if (pid == -1)
//             exit(EXIT_FAILURE);
//         if (pid == 0)
//         {
//             //execute child process;
//             set_upfdfiles(fdin, fdout, cmd, prev);
//             if (!its_builtin)
//             {
//                 ft_exec(cmd, env);
//             }
//             else if (its_builtin && !cmd->cmd[1])
//                 ft_exec_builtin(cmd);
//             exit (EXIT_SUCCESS);
//         }
//         else
//         {
//             // execute parent process;
//             if (its_builtin && !cmd->next && !prev && cmd->cmd[1])
//             {
//                 if (fdout != STDOUT_FILENO)
//                 {
//                     dup2(fdout, STDOUT_FILENO);
//                     close (fdout);
//                     ft_exec_builtin(cmd);
//                     dup2(savedout, STDOUT_FILENO);
//                     close (savedout);
//                 }
//                 else
//                     ft_exec_builtin(cmd);
//             }
//             if (fdin != STDIN_FILENO)
//                 close (fdin);
//             if (prev)
//             {
//                 close (prev->fd[0]);
//                 close (prev->fd[1]);
//             }
//             prev = cmd;
//             cmd = cmd->next;
//             i++;
//         }
        
//     }

//         // get exit status;
//         int j = -1;
//         int status;

//         while (++j <= countpipes)
//         {
//             wait(&status);
//             if (WIFEXITED(status)) {
//                 if (!its_builtin)
//                     g_exec->exit_status = WEXITSTATUS(status);
//         } else {
//             printf("Child process did not terminate normally\n");
//         }
//     }
//     free_exec(0);
// }