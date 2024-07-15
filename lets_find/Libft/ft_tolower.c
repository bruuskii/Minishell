/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:28:56 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 18:25:20 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_uppercase(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else
		return (0);
}

int	ft_tolower(int c)
{
	if (is_uppercase(c))
		return (c + 32);
	else
		return (c);
}
