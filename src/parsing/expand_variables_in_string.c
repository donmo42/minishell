/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:07:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/09/24 16:26:12 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *theString)
{
	size_t	i;

	i = 0;
	while (theString[i])
		i++;
	return (i);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*scpy;

	i = 0;
	if (!*s)
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	scpy = malloc((len + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	while (i < len)
	{
		scpy[i] = s[start];
		start++;
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1s2len;
	size_t	i;
	size_t	j;
	char	*s1s2cpy;

	i = 0;
	j = 0;
	s1s2len = ft_strlen(s1) + ft_strlen(s2);
	s1s2cpy = malloc((s1s2len + 1) * sizeof(char));
	if (!s1s2cpy)
		return (NULL);
	while (s1[i])
	{
		s1s2cpy[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s1s2cpy[i] = s2[j];
		i++;
		j++;
	}
	s1s2cpy[i] = '\0';
	return (s1s2cpy);
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	srclen;
	char	*srcpy;

	i = 0;
	srclen = ft_strlen(src);
	srcpy = malloc((srclen + 1) * sizeof(char));
	if (!srcpy)
		return (NULL);
	while (i < srclen)
	{
		srcpy[i] = src[i];
		i++;
	}
	srcpy[i] = '\0';
	return (srcpy);
}
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
	{
		return (1);
	}
	return (0);
}

char	*ft_extract_var_name(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	while (ft_isspace(str[i]) && str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	return (cpy);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;
	size_t			i;

	i = 0;
	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	while (i != n && (s1cpy[i] != '\0' || s2cpy[i] != '\0'))
	{
		if (s1cpy[i] != s2cpy[i])
			return (s1cpy[i] - s2cpy[i]);
		i++;
	}
	return (0);
}

char	*search_expansion_replacement(char *var_name, char **envp)
{
	char	*value;
	int		i;

	i = 0;
	if (!value)
		return (0);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0)
			value = ft_strdup(envp[i] + ft_strlen(var_name) + 1);
		i++;
	}
	if (!value)
		return (NULL);
	return (value);
}

char	*expand_variables_in_string(char *str, char **envp)
{
	int		i;
	int		j;
	int		in_single_quotes;
	char	*result;
	char	*temp;
	char	*var_name;
	char	*replacement;
	char	char_str[2];

	i = 0;
	j = 0;
	in_single_quotes = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (str[i] == '$' && !in_single_quotes)
		{
			i++;
			j = 0;
			if (ft_isspace(str[i]) || !str[i])
			{
				temp = ft_strjoin(result, "$");
				free(result);
				result = temp;
				free(temp);
			}
			else
			{
				while (str[i + j] && !ft_isspace(str[i + j]) && str[i
					+ j] != '\'' && str[i + j] != '"' && str[i + j] != '$')
					j++;
				var_name = ft_substr(str, i, j);
				if (!var_name)
					return (free(result), NULL);
				replacement = search_expansion_replacement(var_name, envp);
				free(var_name);
				if (replacement)
				{
					temp = ft_strjoin(result, replacement);
					free(result);
					free(replacement);
					result = temp;
				}
				i += j;
			}
		}
		else
		{
			char_str[0] = str[i];
			char_str[1] = '\0';
			temp = ft_strjoin(result, char_str);
			free(result);
			result = temp;
			i++;
		}
	}
	printf("%s", result);
	return (result);
}

int	main(int ac, char **av, char **envp)
{
	char *buffer;
	int readsd = read(0, buffer, 1024);
	expand_variables_in_string(buffer, envp);
}