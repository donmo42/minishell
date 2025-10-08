/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:46:46 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/08 14:20:13 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fd_and_cmd_tab(t_data *data, char **av, int ac, char **envp)
{
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
	if (!redirect_and_cmds(data, av, ac, envp))
		return (0);
	return (1);
}
