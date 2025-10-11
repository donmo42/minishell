/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:39:06 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/11 16:35:00 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	creat_fd_infile(t_data *data, int *i)
{
	if (ft_strcmp(data->argv[*i], "<") == 0 && data->argv[*i + 1])
	{
		data->infile_fd = open(data->argv[*i + 1], O_RDONLY);
		if (data->infile_fd == -1)
			return (perror("no such file or directory"), -1);
		(*i)++;
	}
	return (1);
}

int	creat_fd_outfile(t_data *data, int *i)
{
	if (ft_strncmp(data->argv[*i], ">>", 2) == 0 && data->argv[*i + 1])
	{
		if (data->outfile_fd != -1)
			close(data->outfile_fd);
		data->outfile_fd = open(data->argv[*i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->outfile_fd == -1)
			return (perror(data->argv[*i + 1]), -1);
		(*i)++;
	}
	else if (ft_strncmp(data->argv[*i], "2>", 2) == 0 && data->argv[*i + 1])
	{
		data->error_fd = open(data->argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->error_fd == -1)
			return (perror(data->argv[*i + 1]), -1);
		(*i)++;
	}
	else if (ft_strncmp(data->argv[*i], ">", 1) == 0 && data->argv[*i + 1])
	{
		if (data->outfile_fd != -1)
			close(data->outfile_fd);
		data->outfile_fd = open(data->argv[*i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile_fd == -1)
			return (perror(data->argv[*i + 1]), -1);
		(*i)++;
	}
	return (1);
}

int	redirect_and_cmds(t_data *data, int ac, char **envp)
{
	int	i;

	(void)envp;
	(void)ac;
	i = 0;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
	while (data->argv[i])
	{
		if (!creat_fd_infile(data, &i))
			return (-1);
		if (!creat_fd_outfile(data, &i))
			return (-1);
		i++;
	}
	create_cmd_tab(data);
	create_pipeline_tab(data);
	return (1);
}
