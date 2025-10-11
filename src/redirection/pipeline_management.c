/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:33:40 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/11 16:58:15 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipeline(t_data *data)
{
	int	i;
	int	pipe_count;

	pipe_count = 0;
	i = 0;
	while (data->argv_only_cmd[i])
	{
		if (strcmp(data->argv_only_cmd[i], "|") == 0)
		{
			pipe_count++;
		}
		i++;
	}
	return (pipe_count);
}

int	count_args_in_cmd(t_data *data, int start_index)
{
	int	count;
	int	i;

	count = 0;
	i = start_index;
	while (data->argv_only_cmd[i] != NULL && strcmp(data->argv_only_cmd[i],
			"|") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

void	create_pipeline_tab(t_data *data)
{
	int		i;
	int		j;
	int		k;
	int		num_args;
	char	***table_pipe;

	i = 0;
	j = 0;
	k = 0;
	table_pipe = (char ***)malloc((count_pipeline(data) + 1) * sizeof(char **));
	if (table_pipe == NULL)
		return ;
	while (data->argv_only_cmd[i])
	{
		num_args = count_args_in_cmd(data, i);
		table_pipe[j] = (char **)malloc((num_args + 1) * sizeof(char *));
		if (table_pipe[j] == NULL)
			return ;
		if (strcmp(data->argv_only_cmd[i], "|") == 0)
		{
			table_pipe[j][k] = NULL;
			j++;
			k = 0;
		}
		else
		{
			table_pipe[j][k] = ft_strdup(data->argv_only_cmd[i]);
			k++;
		}
		i++;
	}
	table_pipe[j][k] = NULL;
}
