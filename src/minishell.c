/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:57:07 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/26 22:33:48 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)

{
	(void)av;
	(void)ac;
	(void)envp;

	int reado;
	char buffer[100];

	reado = read(0, buffer, 1024);

	char *xs = delete_multiple_space(buffer);
	char *s = expand_variables_in_string(xs, envp);
	
	char **result = argv_valid_tab(s);
	if (result != NULL)
	{
		for (int i = 0; result[i] != NULL; i++)
		{
			printf("Partie %d: %s\n", i + 1, result[i]);
		}
	}
	//printf("%s", s);

	return (0);
}