/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:39:06 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/08 14:26:30 by macoulib         ###   ########.fr       */
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

int	creat_fd_infile(t_data *data, char **tab_argv, int *i)
{
	if (ft_strncmp(tab_argv[*i], "<", 1))
	{
		data->infile_fd = open(tab_argv[*i + 1], O_RDONLY);
		if (data->infile_fd == -1)
			return (perror("no such file or directory"), -1);
		(*i)++;
	}
	return (1);
}

int	creat_fd_outfile(t_data *data, char **tab_argv, int *i)
{
	if (ft_strncmp(tab_argv[*i], ">", 1))
	{
		data->outfile_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd == -1)
			return (perror("open in fd"), -1);
		(*i)++;
	}
	else if (ft_strncmp(tab_argv[*i], ">>", 2))
	{
		data->outfile_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
		data->error_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd == -1)
			return (perror("open out fd"), -1);
	}
	else if (ft_strncmp(tab_argv[*i], "2>", 2))
	{
		data->error_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->error_fd == -1)
			return (perror("open error fd"), -1);
		(*i)++;
	}
	return (1);
}

int	redirect_and_cmds(t_data *data, char **av, int ac, char **envp)
{
	int	i;

	(void)envp;
	i = 0;
	
	while (av[i])
	{
		if (!creat_fd_infile(data, av, &i))
			return (-1);
		if (!creat_fd_outfile(data, av, &i))
			return (-1);
		i++;
	}
	created_tab_only_cmd(av, data, ac);
	return (1);
}
