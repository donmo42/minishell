/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:46:46 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/29 18:21:09 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirection(char **av, char **envp)
{
	int		enter_fd;
	int		out_fd;
	int		error_fd;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	**path;

	enter_fd = -1;
	out_fd = -1;
	error_fd = -1;
	if (!handle_redirection(&enter_fd, &out_fd, &error_fd, av))
		return (0);
	pid = fork();
	if (pid == -1)
		return ("fork error", 0);
	if (pid == 0)
	{
		if (!enter_fd != -1)
		{
			dup2(enter_fd, 0);
			close(enter_fd);
		}
		if (!out_fd != -1)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		if (!error_fd != -1)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execve(path, av, envp);
	}
	else
	{
		if (enter_fd != -1)
			close(enter_fd);
		if (out_fd != -1)
			close(out_fd);
		waitpid(pid, &status, 0);
	}
}
