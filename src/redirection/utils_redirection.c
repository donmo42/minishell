/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:42:54 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/06 19:00:51 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	redirection_detected(char **av)
{
	int i;
	i = 0;

	while (av[i])
	{
		if (!ft_strcmp(av[i], ">") || !ft_strcmp(av[i], "<")
			|| !ft_strcmp(av[i], ">>") || !ft_strcmp(av[i], "2>"))
			return (1);
	}
	return (0);
}