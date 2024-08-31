/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:13 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 18:56:09 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_last_infile(t_exec_utils *exec_utils, int *fileinfd, int *tmpfderror)
{
	if (!*exec_utils->file->filename)
	{
		ft_putstr_fd("bash : ambiguous redirect\n", 2);
		exec_utils->file = exec_utils->file->next;
		*tmpfderror = -1;
		return (-1);
	}
	if (exec_utils->file->isherdoc)
		execute_herdoc(exec_utils, fileinfd);
	else
	{
		*fileinfd = open(exec_utils->file->filename, O_RDONLY, 0777);
		if (*fileinfd == -1)
		{
			ft_putstr_fd("no sush file or directory\n", 2);
			*tmpfderror = *fileinfd;
			return (-1);
		}
	}
	return (1);
}

int	getinputfile(t_cmd *cmd, t_exec_utils *exec_utils)
{
	int	fileinfd;
	int	size;
	int	i;
	int	tmpfderror;

	i = 0;
	fileinfd = -1;
	size = countfiles(cmd->infile);
	exec_utils->file = cmd->infile;
	tmpfderror = 0;
	if (!size)
		return (STDIN_FILENO);
	while (i < size && exec_utils->file)
	{
		if (get_last_infile(exec_utils, &fileinfd, &tmpfderror) == -1)
			g_exec->exit_status = 1;
		if  (exec_utils->exit_state == 130)
			return (130);
		exec_utils->file = exec_utils->file->next;
		i++;
	}
	if (tmpfderror == -1)
		return (tmpfderror);
	return (fileinfd);
}

int	get_lastoutfile(t_filedescriptiom *file, int *fd, int size)
{
	int	i;

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

int	getoutputfile(t_cmd *cmd, t_exec_utils *exec_utils)
{
	int	fileoutfd;
	int	size;
	int	i;
	int	*fd;

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

void	set_upfdfiles(int fdin, int fdout, t_cmd *cmd, t_cmd *prev)
{
	if (fdin == -1)
		exit(EXIT_FAILURE);
	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	else if (prev)
	{
		dup2(prev->fd[0], STDIN_FILENO);
		close(prev->fd[0]);
		close(prev->fd[1]);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	else if (cmd->next)
	{
		close(cmd->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}
