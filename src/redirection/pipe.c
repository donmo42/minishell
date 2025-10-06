/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:13:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/06 18:45:55 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_pipe(char **tab_argv)
{
	int i;
	int fd;
	int pipe_fd[2];

	i = 0;
	fd = 0;
	while (tab_argv[i])
	{
		if (ft_strncmp(tab_argv[i], "|", ft_strlen(tab_argv[i])))
		{
			pipe(pipe_fd);
			if (fork == 0)
			{
				dup2(fd, 0);
				close(pipe_fd[0]);
			}
			else
			{
				wait(NULL);
				close(pipe_fd[1]);
				fd = pipe_fd[0];
			}
		}
		i++;
	}
}