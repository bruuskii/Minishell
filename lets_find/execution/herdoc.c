/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:10 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/27 17:51:45 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sig_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		exit(2);
	}
}

int	heredoc(char *delimeter, int fd)
{
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sig_herdoc);
		tmp = readline("");
		if (ft_heredoc(delimeter, fd, tmp) == 0)
			break ;
		free(tmp);
	}
	free(tmp);
	exit(0);
	return (1);
}

void	ft_execute_child(int *fd, t_exec_utils *exec_utils)
{
	close(fd[0]);
	heredoc(exec_utils->file->delimeter, fd[1]);
	close(fd[1]);
	exit(0);
}

int	ft_execute_parent(int status, int exit_status, int *fileinfd, int *fd)
{
	close(fd[1]);
	wait(&status);
	exit_status = WEXITSTATUS(status);
	if (exit_status == 1)
	{
		g_exec->exit_status = exit_status;
		return (1);
	}
	else if (exit_status == 2)
	{
		g_exec->exit_status = 130;
		return (130);
	}
	else if (exit_status == 3)
		return (3);
	*fileinfd = fd[0];
	return (0);
}

int	execute_herdoc(t_exec_utils *exec_utils, int *fileinfd)
{
	int	fd[2];
	int	status;
	int	pid;
	int	exit_status;

	exit_status = 0;
	status = 0;
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		ft_execute_child(fd, exec_utils);
	else
	{
		exec_utils->sig_rec = ft_execute_parent(status, exit_status, fileinfd,
				fd);
		printf("seg_rec :%d\n", exec_utils->sig_rec);
		if (exec_utils->sig_rec == 130)
			exec_utils->exit_state = 130;
	}
	return (*fileinfd);
}
