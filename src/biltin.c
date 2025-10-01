#include "minishell.h"

char **copy_envp(char **envp)

{
	int count = 0;
	int i;
	char **copy;

	while (envp[count])
		count++;
	copy = malloc ((count + 1) * sizeof(char *));
	if(!copy)
		return NULL;
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[count] = NULL;
	return copy;
}

int builtin_pwd(void)
{
	char cwd[1024];
	if(getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return(0);
	}
	perror("pwd");
	return (1);
}

int builtin_echo(char **argv)
{
	int i;
	int newline;

	i = 1;
	newline = 1;

	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while(argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
 void update_pwd(char **envp)
{
	char cwd[1024];
	char *new_pwd;
	char *prefix;
	int i;
	i = 0;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return;
	prefix = ft_strdup("PWD=");
	if (!prefix)
		return;

	new_pwd = ft_strjoin(prefix, cwd);
		free(prefix);
	if(!new_pwd)
		return;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			free(envp[i]);
			envp[i] = new_pwd;
			return;
		}
		i++;
	}

}
int builtin_cd(char **argv, char **envp)
{
	
	if(!argv[1])
	{
		ft_putstr_fd("minishell: cd: missing argument\n", 2);
		return (1);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(argv[1]) !=0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	update_pwd(envp);
	return (0);
}

int execute_builtin(char **argv, char **envp)
{
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return builtin_pwd();
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return builtin_echo(argv);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return builtin_cd(argv, envp);
	return (-1);
}