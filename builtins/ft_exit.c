/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:06:19 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:06:22 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number_valid(char *nb)
{
	int	i;
	int	nbsign;

	i = 0;
	nbsign = 0;
	while (nb[i])
	{
		if (!(ft_isdigit(nb[i]) || nb[i] == '+' || nb[i] == '-'
				|| is_blanks(nb[i])))
			return (2);
		if (nb[i] == '-' || nb[i] == '+')
			nbsign++;
		i++;
	}
	if (nbsign > 1)
		return (2);
	return (1);
}

void	ft_exit1(char **cmd)
{
	int					i;
	unsigned long long	num;

	i = 1;
	while (cmd[i])
	{
		if (is_number_valid(cmd[i]) == 2)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit : numeric argument required\n", 2);
			free_exec(1);
			exit(2);
		}
		i++;
	}
	if (!(i - 1 > 1))
	{
		ft_putstr_fd("exit\n", 1);
		num = ft_atoi(cmd[1]);
		free_exec(1);
		exit(num);
	}
	g_exec->exit_status = 1;
	ft_putstr_fd("exit : too many arguments\n", 2);
}

void	ft_exit(char **cmd)
{
	if (!cmd[1])
	{
		free_exec(1);
		exit(0);
	}
	ft_exit1(cmd);
}
