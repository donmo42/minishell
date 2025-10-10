/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/10 17:28:16 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_cmd(t_data *data, char **envp)
{
	char	**split_cmd;
	char	*cmd_path;

	split_cmd = ft_split(data->argv_only_cmd[0], ' ');
	// if (!split_cmd[0] || !split_cmd)
	// print_error_and_exit("Error split command");
	cmd_path = find_path(envp, split_cmd[0]);
	if (cmd_path == NULL)
			ft_putstr_fd("command not found: ", 2);
	execve(cmd_path, data->argv_only_cmd, envp);
	// print_error_and_exit("execve");
}

void	dup_and_close_fd(t_data *data)
{
	if (data->infile_fd != -1)
	{
		dup2(data->infile_fd, 0);
		close(data->infile_fd);
	}
	if (data->outfile_fd != -1)
	{
		dup2(data->outfile_fd, 1);
		close(data->outfile_fd);
	}
	if (data->error_fd != -1)
	{
		dup2(data->error_fd, 2);
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

void	exe(t_data *data, char *input, int ac, char **env)
{
	int		i;
	char	**av;
	pid_t	pid;
	int		status;

	i = 0;
	av = argv_valid_tab(input);
	while (av[i])
		i++;
	data->argv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (av[i])
	{
		data->argv[i] = ft_strdup(av[i]);
		i++;
	}
	data->argv[i] = NULL;
	i = 0;
	redirect_and_cmds(data, ac, env);
	
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		dup_and_close_fd(data);
		exe_cmd(data, env);
	}
	else
	{
		close_fd(data);
		waitpid(pid, &status, 0);
	}
}
