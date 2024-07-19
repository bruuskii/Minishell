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
    exec->cmd = NULL;
    exec->exit_status = 0;
    return (exec);
}

void setuptestexecute(t_exec *exec)
{
    t_cmd *tmp1 = malloc(sizeof(t_exec *));
    tmp1->infile  = malloc(sizeof(t_filedescription));
    tmp1->outfile = malloc(sizeof(t_filedescription));
    tmp1->cmd = ft_split("ls -al", ' ');

    t_cmd *tmp2 = malloc(sizeof(t_exec *));
    tmp2->infile  = malloc(sizeof(t_filedescription));
    tmp2->outfile = malloc(sizeof(t_filedescription));
    tmp2->cmd = ft_split("Achraf", ' ');

    // tmp1->nextcmd = NULL;
    exec->cmd = tmp1;
    tmp2->nextcmd = NULL;
    exec->cmd->nextcmd = tmp2;
}





int    getinputfile(t_cmd *cmd)
{
    int fileinfd;
    int size;
    int     i;
    t_filedescription *file;
    
    i = 0;
    size = countfiles(cmd->infile);
    file = cmd->infile;
    if (!size)
        return (0);
    while (i < size && file)
    {
        if (file->isherdoc)
            {
                // open herdoc;
                // set up herdoc;
                // in case of herdoc what's to check
                /*
                    if the case of cat pass herdocs to parameter;test to check;
                */
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
    t_filedescription *file;
    int *fd;
    
    i = 0;
    size = countfiles(cmd->outfile);
    file = cmd->outfile;
    if (!size)
        return (1);
    fd = malloc(size * sizeof(int));
    if (!fd)
        return (0);
    while (i < size && file)
    {
        if (file->iswithappend)
            fd[i] = open(file->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
        else   
            fd[i] = open(file->filename, O_RDWR | O_CREAT, 0777);
        if (fd[i] == -1)
        {
            perror("file (name) not found");//check if i need to open them wakha error;
        }
        // else
        // {
        //     // close files;
        //     // if size > 2  // close file while  i=0<size-1;// save filesdescriptor;tab[size]
        // }
        // check later;
        if (file->next)
            close(fd[i]);
        i++;
        file = file->next;
    }
    fileoutfd = fd[i];
    int j = 0;
    while (j <= i)
    {
        if (fd[j])
            free(fd[j]);
        j++;
    }
    return (fileoutfd);
}


void ft_execute(t_exec *exec, t_cmd *cmd, char **env , int flagbuiltin)
{
    int fd[2];
    int pid;
    int fdout;
    int fdin;

    if (pipe(fd) == -1)
        exit(10);
    pid = fork();
    if (pid == -1)
        exit (10);
    if (pid == 0)
    {
        close(fd[0]);
        fdin = getinputfile(cmd);
        fdout = getoutputfile(cmd);
        dup2(fdin, STDIN_FILENO);
        dup2(fdout, STDOUT_FILENO);
        if (flagbuiltin)
            ft_exec_builtin(exec, cmd, env);
        else
            ft_exec(exec, cmd, env);

    }
    else
    {
        close(fd[1]);
        while (wait(NULL) == -1)
            ;
    }
    close(fd[0]);
    close(fd[1]);
}

void ft_exec_builtin( t_exec *exec, t_cmd *cmd, char **env)
{
    if (!ft_strcmp(cmd->cmd[0], "echo"))
        return (1);
    // else if (!ft_strcmp(cmd->cmd[0], "cd"))
    //     return (1);
    else if (!ft_strcmp(cmd->cmd[0], "pwd"))
        pwd(exec->env);
    else if (!ft_strcmp(cmd->cmd[0], "export"))
        export(exec->env, exec->env_export, cmd);
    // else if (!ft_strcmp(cmd->cmd[0], "unset"))
    //     return (1);
    // else if (!ft_strcmp(cmd->cmd[0], "env"))
    //     return (1);
    // else if (!ft_strcmp(cmd->cmd[0], "exit"))
    //     return (1);
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
            perror("command path not found");
        if (execve(commandpath, cmd->cmd, env) == -1)
            perror("execve error");
	}
	else
	{
        if (execve(cmd->cmd[0], cmd->cmd, env) == -1)//env to tab;
            perror("commande execve error");
	}
}

int itsbuiltin(t_cmd *cmd)
{
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



void execute( t_exec *exec, t_cmd *cmd , char **env)
{   
    t_exec *exec = initexec(env);//
    t_cmd  *command = NULL;
    setuptestexecute(exec);// just for test;
    int countpipes = count_pipes(exec->cmd);
    //printf("count pipe = %d\n", countpipes);
    int i=0;

    command = exec->cmd;
    while (i < countpipes && command)
    {
        if (itsbuiltin(command))
            ft_execute(exec, command, env, 1);
        else
            ft_execute(exec, command, env, 0);
        command = command->nextcmd;
        i++;
    }
    //execute Last cmd;
}