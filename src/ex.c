#include "minishell.h"

int has_slash(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int is_executable_file(const char *path)
{
	struct stat st;

	if (!path)
		return(0);
	if (stat(path, &st) == -1)
		return (0);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

static char *path_join_cmd( char *dir, char *cmd)
{
	size_t	len;
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	len = ft_strlen(dir);
	if (len > 0 && dir[len - 1] == '/')
	{
		full = ft_strjoin(dir, cmd);
		return (full);
	}
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*find_command_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;
	
	if(!cmd || !*cmd)
		return (NULL);

	if (has_slash(cmd))
	{
		if (is_executable_file(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env || !*path_env)
		path_env = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	paths = ft_split(path_env, ':');
	if (!paths)
		return(NULL);

	i = 0;
	while (paths[i])
	{
		if (*(paths[i]) != '\0')
			full = path_join_cmd(paths[i], cmd);
		else
			full = ft_strdup(cmd);
		if (full && is_executable_file(full))
		{
			ft_free_split(paths);
			return (full);
		}
		if (full)
			free (full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
	}
	

void print_cmd_error(char *cmd, int has_slash)
{
	if (has_slash)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void run_execve(char *cmd_path, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
		{
			execve(cmd_path, argv, envp);
			perror("execve");
			exit(126);
		}
		else
		{
			if (waitpid(pid, &status, 0) < 0)
				perror("waitpid");
		}
		
}

	void	execute_command(char *input, char **envp)
	{
		char	**argv;
		char	*cmd_path;
		int		builtin_status;
		
		if (!input)
			return;
		argv = ft_split(input, ' ');
		
		if (!argv)
			return;
		if (!argv || !argv[0] || argv[0][0] == '\0')
			return (ft_free_split(argv));

		builtin_status = execute_builtin(argv,envp);
		if (builtin_status != -1)
			return (ft_free_split(argv));

		cmd_path = find_command_path(argv[0]);
		if (!cmd_path)
		{
			print_cmd_error(argv[0], has_slash(argv[0]));
			return (ft_free_split(argv));
		}
		run_execve(cmd_path, argv, envp);
		free(cmd_path);
		ft_free_split(argv);
	}