#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	char	*input;
	char	**my_env;
	(void)argc;
	(void)argv;
	my_env = copy_envp(envp);
	if(!my_env)
		return(1);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit", 1);
			write(1, "\n", 1);
			break;
		}
		if (*input)
			add_history(input);
		execute_command(input, my_env);
		free(input);
	}
	return(0);
}