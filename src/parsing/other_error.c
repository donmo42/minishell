/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:43 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/06 18:40:04 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(const char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "|"));
}

int	check_after_redirection(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_separator(av[i]))
		{
			if (av[i + 1] == NULL || is_separator(av[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	direction_error(char *str, t_data *data)
{
	int i;
	int j;

	i = ft_strlen(str) - 1;
	j = 0;
	while (j > i && (str[i] == ' ' || str[i] == '\t'))
		j++;
	if (str[j] == '|' || str[j] == '>')
		return (1);
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
		return (1);
	if (check_after_redirection(data->argv))
		return (1);
	return (0);
}