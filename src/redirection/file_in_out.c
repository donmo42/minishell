/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:39:06 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/01 15:46:50 by macoulib         ###   ########.fr       */
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
	int	i;

	i = 0;
	data->argv_only_cmd = (char **)malloc(sizeof(char *) * (nbr_new_cmd_tab(av)
				+ 1));
	if (!data->argv_only_cmd)
		return (NULL);
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
			return (NULL);
			}
			i++;
		}
	}
	data->argv_only_cmd[i] = NULL;
}

int	creat_fd_in_out(t_data *data, char *tab_argv, int *i)
{
	if (ft_strncmp(tab_argv[*i], "<", 1))
	{
		data->infile_fd = open(tab_argv[*i + 1], O_RDONLY);
		if (data->infile_fd == -1)
			return (perror("no such file or directory"), -1);
		(*i)++;
	}
	else if (ft_strncmp(tab_argv[*i], ">", 1))
	{
		data->outfile_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd == -1)
			return (perror("open out fd"), -1);
		(*i)++;
	}
	else if (ft_strncmp(tab_argv[*i], ">>", 2))
	{
		data->outfile_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (data->outfile_fd == -1)
			return (perror("open out fd"), -1);
	}
	else if (ft_strncmp(tab_argv[*i], "2>", 2))
	{
		data->error_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->error_fd == -1)
			return (perror("open in fd"), -1);
		(*i)++;
	}
	return (1);
}

int	handle_redirection(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!creat_fd_in_out(data, av[i], &i))
			return (-1);
	}
	created_tab_only_cmd(&data->argv_only_cmd, av, ac);
	return (1);
}
