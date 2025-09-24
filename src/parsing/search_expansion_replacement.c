/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expansion_replacement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:22:10 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/24 20:29:34 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmps(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;
	size_t			i;

	i = 0;
	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	while (i != n && (s1cpy[i] != '\0' || s2cpy[i] != '\0'))
	{
		if (s1cpy[i] != s2cpy[i])
			return (s1cpy[i] - s2cpy[i]);
		i++;
	}
	return (0);
}

char	*search_expansion_replacement(char *var_name, char **envp)
{
	char	*value;
	int		i;

	i = 0;
	value = ft_strdup(" ");
	if (!value)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmps(envp[i], var_name, ft_strlen(var_name)) == 0)
			value = ft_strdup(envp[i] + ft_strlen(var_name) + 1);
		i++;
	}
	if (!value)
		return (NULL);
	return (value);
}
