/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:45:31 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/06 18:40:51 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parsing(char *str, t_data *data, char **envp)
{
	int		quote;
	char	*str_whithout_space;
	char	**argv_tab;
	char	*if_variable;

	if (data->argv)
		free(data->argv);
	quote = closed_quotes(str);
	if (!quote)
		return (0);
	str_whithout_space = delete_multiple_space(str);
	if (direction_error(str_whithout_space, data))
		return (0);
	if_variable = expand_variables_in_string(str_whithout_space, envp);
	argv_tab = argv_valid_tab(str_whithout_space);
	data->argv = argv_tab;
	return (1);
}
