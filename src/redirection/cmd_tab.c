/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:23:42 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/08 10:56:35 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nbr_new_cmd_tab(char **av)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (av[i])
	{
		if (is_redirection_operator(av[i]))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	created_tab_only_cmd(char **av, t_data *data, int ac)
{
	int i;

	i = 0;
	(void)ac;
	data->argv_only_cmd = (char **)malloc(sizeof(char *) * (nbr_new_cmd_tab(av)
				+ 1));
	if (!data->argv_only_cmd)
		return ;
	while (av[i])
	{
		if (is_redirection_operator(av[i]))
			i += 2;
		else
		{
			data->argv_only_cmd[i] = ft_strdup(av[i]);
			if (!data->argv_only_cmd[i])
			{
				while (i > 0)
					free(data->argv_only_cmd[--i]);
				free(data->argv_only_cmd);
				return ;
			}
			i++;
		}
	}
	data->argv_only_cmd[i] = NULL;
}