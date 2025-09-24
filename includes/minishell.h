/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:02:12 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/24 20:29:40 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../librairie/ft_libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_isspace(char c);
int		closed_quotes(char *str);
char	*expand_variables_in_string(char *str, char **envp);
char	*find_path(char **env, char *cmd);
char	*delete_multiple_space(char *str);
int		ft_strncmps(const char *s1, const char *s2, size_t n);
char	*search_expansion_replacement(char *str, char **envp);
char	*expand_variables_in_string(char *str, char **envp);

#endif
