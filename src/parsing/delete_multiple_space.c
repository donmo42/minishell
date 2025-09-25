/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_multiple_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:07:33 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/25 15:20:06 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
	{
		return (1);
	}
	return (0);
}

char	*delete_multiple_space(char *str)
{
	int		i;
	int		j;
	char	*correct_str;

	i = 0;
	j = 0;
	correct_str = malloc(1024);
	if (!correct_str)
		return (NULL);
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			if (j > 0 && !ft_isspace(correct_str[j - 1]))
				correct_str[j++] = ' ';
		}
		else
		{
			correct_str[j++] = str[i];
		}
		i++;
	}
	correct_str[j] = '\0';
	return (correct_str);
}
