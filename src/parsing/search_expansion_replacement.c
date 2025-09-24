/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expansion_replacement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:22:10 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/23 16:33:55 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*search_expansion_replacement(char *str, char **envp)
{
	char	*expansion_str;
	int		i;

	i = 0;
	expansion_str = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strcmp(envp[i], str) == 0)
			expansion_str = envp[i] + ft_strlen(str + 1);
		i++;
	}
	return (expansion_str);
}
