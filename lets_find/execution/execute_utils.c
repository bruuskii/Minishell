#include "../minishell.h"




int count_pipes(t_cmd *cmd)
{
    int i;
    t_cmd   *temp;

    i = 0;
    temp = cmd;
    while (temp)
    {
        i++;
        temp = temp->nextcmd;
    }
    if (i)
        return (i -1);
    return (i);
}

int countfiles(t_filedescription *files)
{
    t_filedescription *filetmp;
    int i;

    filetmp = files;
    i = 0;
    while (filetmp)
    {
        i++;
        filetmp = filetmp->next;
    }
    return (i);
}



char	**get_paths()
{
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
    if (!paths)
        return (NULL);
    return (paths);
}