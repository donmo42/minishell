/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:39:06 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/08 23:54:56 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_operator(char *av)
{
	if (ft_strcmp(av, "<") == 0 || ft_strcmp(av, ">") == 0 || ft_strcmp(av,
			">>") == 0 || ft_strcmp(av, "2>") == 0 || ft_strcmp(av, "|") == 0)
		return (1);
	return (0);
}

int	creat_fd_infile(t_data *data, int i)
{
	if (ft_strcmp(data->argv[i], "<") == 0)
	{
		data->infile_fd = open(data->argv[i + 1], O_RDONLY);
		if (data->infile_fd == -1)
			return (perror("no such file or directory"), -1);
	}
	return (1);
}

int	creat_fd_outfile(t_data *data, int i)
{
	if (ft_strncmp(data->argv[i], ">", 1) == 0)
	{
		data->outfile_fd = open(data->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd == -1)
			return (perror("open in fd"), -1);
	}
	else if (ft_strncmp(data->argv[i], ">>", 2) == 0)
	{
		data->outfile_fd = open(data->argv[i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		data->error_fd = open(data->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd == -1)
			return (perror("open out fd"), -1);
	}
	else if (ft_strncmp(data->argv[i], "2>", 2) == 0)
	{
		data->outfile_fd = open(data->argv[i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->error_fd == -1)
			return (perror("open error fd"), -1);
	}
	return (1);
}

int	redirect_and_cmds(t_data *data, int ac, char **envp)
{
	int	i;

	(void)envp;
	(void)ac;
	i = 0;
	while (data->argv[i])
	{
		if (!creat_fd_infile(data, i))
			return (-1);
		if (!creat_fd_outfile(data, i))
			return (-1);
		i++;
	}
	return (1);
}
