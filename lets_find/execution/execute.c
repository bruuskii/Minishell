#include  "../minishell.h"


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
    exec->herdoc_sig = 0;
    return (exec);
}


int execute_herdoc(t_exec_utils *exec_utils, int fileinfd)
{
    int fd[2];

    if (pipe(fd) == -1)
        return (-1);
            int pid = fork();
    if (pid == -1)
        return (-1);
    else if (pid == 0)
    {
        close (fd[0]);
        heredoc(exec_utils->file->delimeter,fd[1]);
        close (fd[1]);
        exit(0);
    }
    else
    {
        int status;
        close (fd[1]);
        wait(&status);
        int exit_status = WEXITSTATUS(status); 
        if (exit_status == 1)
        {
            g_exec->exit_status = exit_status;
            return (-1);
        }
        else if (exit_status == 2)
        {
            g_exec->herdoc_sig = 1;
            return -1;
        }
            fileinfd = fd[0];
    }
    return(fileinfd);
}

int    getinputfile(t_cmd *cmd, t_exec_utils *exec_utils)
{
    int fileinfd=-1;
    int size;
    int     i;
    int tmpfderror;
    
    i = 0;
    size = countfiles(cmd->infile);
    exec_utils->file = cmd->infile;
    tmpfderror = 0;
    if (!size)
        return (0);
    while (i < size && exec_utils->file)
    {
        if (!*exec_utils->file->filename)
        {
            ft_putstr_fd("bash : ambiguous redirect\n", 2);
            exec_utils->file = exec_utils->file->next;
            i++;
            tmpfderror = -1;
            continue;
        }
        if (exec_utils->file->isherdoc)
        {
            
            int fd[2];

            if (pipe(fd) == -1)
                return (-1);
            int pid = fork();
            if (pid == -1)
                return (-1);
            else if (pid == 0)
            {
                close (fd[0]);
                heredoc(exec_utils->file->delimeter,fd[1]);
                close (fd[1]);
                exit(0);
            }
            else
            {
                int status;
                close (fd[1]);
                wait(&status);
                int exit_status = WEXITSTATUS(status);

                if (exit_status == 1)
                {
                    g_exec->exit_status = exit_status;
                    return (-1);
                }
                else if (exit_status == 2)
                {
                    g_exec->herdoc_sig = 1;
                    return -1;
                }
                fileinfd = fd[0];
            }
        }
        else
        {
            fileinfd = open(exec_utils->file->filename, O_RDONLY, 0777);
            if (fileinfd == -1)
            {
                printf("yes here the probleme :%d:\n", fileinfd);
                perror("no such file or directory\n");
                tmpfderror = fileinfd;
            }
        }
        exec_utils->file = exec_utils->file->next;
        i++;
    }
    if (tmpfderror == -1)
        return (tmpfderror);
    return (fileinfd);
}


int get_lastoutfile(t_filedescriptiom *file, int *fd, int size)
{
    int i;

    i = 0;
    while (i < size && file)
    {
        if (file->iswithappend)
            fd[i] = open(file->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
        else  
            fd[i] = open(file->filename, O_RDWR | O_CREAT, 0777);
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
    return (i);
}

int getoutputfile(t_cmd *cmd, t_exec_utils *exec_utils)
{
    int fileoutfd;
    int size;
    int     i;
    int *fd;
    
    i = 0;
    size = countfiles(cmd->outfile);
    exec_utils->file = cmd->outfile;
    if (!size)
        return (STDOUT_FILENO);
    fd = malloc(size * sizeof(int));
    if (!fd)
        return (0);
    i = get_lastoutfile(exec_utils->file, fd, size);
    if (i == -1)
    {
        free(fd);
        return (-1);
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
        exit_with_message(": command path not found\n", 127);
    }
    if (execve(commandpath, cmd->cmd, env) == -1)
    {
        free(commandpath);
        free_db_arr(env);
        exit_with_message("execve error\n", 127);
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
    if (!cmd->cmd[0])
        return;
    if (!ft_strcmp(cmd->cmd[0], "echo"))
        echo(cmd->cmd);
    else if (!ft_strcmp(cmd->cmd[0], "cd"))
        cd(cmd->cmd);
    if (!ft_strcmp(cmd->cmd[0], "pwd"))
        pwd();
    else if (!ft_strcmp(cmd->cmd[0], "export"))
        export(cmd->cmd);
    else if (!ft_strcmp(cmd->cmd[0], "unset"))
        unset(cmd->cmd);
    else if (!ft_strcmp(cmd->cmd[0], "env"))
        print_env(g_exec->env, 0);
    else if (!strcmp(cmd->cmd[0], "exit"))
        ft_exit(cmd->cmd);
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
    exec_utils.file = NULL;
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
        exec_utils.fdin = getinputfile(cmd, &exec_utils);// verfiy exit status  of cont + c;
        exec_utils.fdout = getoutputfile(cmd, &exec_utils);
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
<<<<<<< HEAD
=======
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



void free_filedescriptiom(t_filedescriptiom *file)
{
    t_filedescriptiom *current;
    t_filedescriptiom *next;

    fprintf(stderr, "Entering free_filedescriptiom\n");
    current = file;
    while (current)
    {
        fprintf(stderr, "Processing filedescriptiom: %p\n", (void*)current);
        next = current->next;
        if (current->filename)
        {
            fprintf(stderr, "Freeing filename: %p\n", (void*)current->filename);
            free(current->filename);
        }
        if (current->delimeter)
        {
            fprintf(stderr, "Freeing delimeter: %p\n", (void*)current->delimeter);
            free(current->delimeter);
        }
        if (!current->isherdoc)  // Only free non-heredoc descriptors
        {
            fprintf(stderr, "Freeing non-heredoc filedescriptiom: %p\n", (void*)current);
            free(current);
        }
        else
        {
            fprintf(stderr, "Skipping heredoc filedescriptiom: %p\n", (void*)current);
        }
        current = next;
    }
    fprintf(stderr, "Exiting free_filedescriptiom\n");
}

void free_cmd(t_cmd *cmd)
{
    if (!cmd || !cmd->cleanup_ready)
    {
        return; // Don't free if not ready for cleanup
    }
    int i;

    fprintf(stderr, "Entering free_cmd for cmd: %p\n", (void*)cmd);
    if (!cmd)
    {
        fprintf(stderr, "cmd is NULL, exiting free_cmd\n");
        return;
    }

    fprintf(stderr, "Freeing cmd->cmd\n");
    if (cmd->cmd)
    {
        for (i = 0; cmd->cmd[i]; i++)
        {
            fprintf(stderr, "Freeing cmd->cmd[%d]: %p\n", i, (void*)cmd->cmd[i]);
            free(cmd->cmd[i]);
        }
        fprintf(stderr, "Freeing cmd->cmd array itself\n");
        free(cmd->cmd);
        cmd->cmd = NULL;
    }
    else
    {
        fprintf(stderr, "cmd->cmd is NULL\n");
    }

    fprintf(stderr, "Checking cmd->infile: %p\n", (void*)cmd->infile);
    if (cmd->infile)
    {
        fprintf(stderr, "Freeing cmd->infile\n");
        free_filedescriptiom(cmd->infile);
        cmd->infile = NULL;
    }
    else
    {
        fprintf(stderr, "cmd->infile is NULL\n");
    }

    fprintf(stderr, "Checking cmd->outfile: %p\n", (void*)cmd->outfile);
    if (cmd->outfile)
    {
        fprintf(stderr, "Freeing cmd->outfile\n");
        free_filedescriptiom(cmd->outfile);
        cmd->outfile = NULL;
    }
    else
    {
        fprintf(stderr, "cmd->outfile is NULL\n");
    }

    fprintf(stderr, "Checking cmd->fd: %p\n", (void*)cmd->fd);
    if (cmd->fd && cmd->fd != (int *)0xbebebebebebebebe)
    {
        fprintf(stderr, "Freeing cmd->fd\n");
        if (cmd->fd[0] != -1)
        {
            fprintf(stderr, "Closing cmd->fd[0]: %d\n", cmd->fd[0]);
            close(cmd->fd[0]);
        }
        if (cmd->fd[1] != -1)
        {
            fprintf(stderr, "Closing cmd->fd[1]: %d\n", cmd->fd[1]);
            close(cmd->fd[1]);
        }
        free(cmd->fd);
    }
    else
    {
        fprintf(stderr, "cmd->fd is NULL or invalid\n");
    }
    cmd->fd = NULL;

    fprintf(stderr, "Freeing cmd itself\n");
    free(cmd);
    fprintf(stderr, "Exiting free_cmd\n");
}

void cleanup_commands(t_cmd *cmd_head)
{
    t_cmd *current;
    t_cmd *next;

    fprintf(stderr, "Entering cleanup_commands\n");
    current = cmd_head;
    while (current)
    {
        fprintf(stderr, "Processing cmd: %p\n", (void*)current);
        next = current->next;
        free_cmd(current);
        current = next;
    }
    fprintf(stderr, "Exiting cleanup_commands\n");
>>>>>>> refs/remotes/origin/main
}