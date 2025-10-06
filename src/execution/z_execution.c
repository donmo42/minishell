/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/06 19:54:33 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_and_close_fd(t_data *data)
{
	if (!data->infile_fd != -1)
	{
		dup2(data->infile_fd, 0);
		close(data->infile_fd);
	}
	 if (!data->outfile_fd != -1)
	{
		dup2(data->outfile_fd, 1);
		close(data->outfile_fd);
	}
	if (!data->error_fd != -1)
	{
		dup2(data->error_fd, 1);
		close(data->error_fd);
	}
}

void	close_fd(t_data *data)
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
}

void	exe(t_data *data, char **av, int ac, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ("fork error", 0);
	if (pid == 0)
	{
		dup_and_close_fd(data);
		
	}
	else
	{
		close_fd(data);
		waitpid(pid, &status, 0);
	}
}
