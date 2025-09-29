/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:43 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/29 19:19:50 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_semicolon_backslash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ';' || str[i] == '\\')
			return (1);
	}
	return (0);
}

int	check_cmd_error(char *str)
{
	int	i;
	int	j;

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
	return (0);
}

int	is_separator(const char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "|"));
}

int	check_after_redirection(char **av)
{
	int i;

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