/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:39:06 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/29 17:57:07 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	creat_fd_in_out(int *enter_fd, int *out_fd, int *error_fd, char *tab_argv,
		int *i)
{
	if (ft_strncmp(tab_argv[*i], "<", 1))
	{
		*enter_fd = open(tab_argv[*i + 1], O_RDONLY);
		if (*enter_fd == -1)
			return (perror("no such file or directory"), -1);
		(*i)++;
	}
	else if (ft_strncmp(tab_argv[*i], ">", 1))
	{
		*out_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*out_fd == -1)
			return (perror("open out fd"), -1);
		(*i)++;
	}
	else if (ft_strncmp(tab_argv[*i], ">>", 2))
	{
		*out_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*out_fd == -1)
			return (perror("open out fd"), -1);
	}
	else if (ft_strncmp(tab_argv[*i], "2>", 2))
	{
		*error_fd = open(tab_argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*error_fd == -1)
			return (perror("open in fd"), -1);
		(*i)++;
	}
	return (1);
}

int	handle_redirection(char **av, int *enter_fd, int *out_fd, int *error_fd)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!creat_fd_in_out(&enter_fd, &out_fd, &error_fd, av[i], &i))
			return (-1);
	}
	return (1);
}
