/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getting2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:41:11 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/25 09:39:47 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Main function to find the command in the system PATH */
char	*find_command_path(char *command, t_cmd *cmd)
{
	struct stat	sb;
	char		*path_env;
	char		**paths;
	char		*full_path;
	int			i;

	path_env = get_path_from_env(cmd->envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = create_full_path(paths[i], command);
		if (stat(full_path, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

// Gets the target directory for `cd` command
char	*get_target_directory(char **args, t_env *envp)
{
	if (args[1])
		return (args[1]);
	return (get_env_var(envp, "HOME"));
}

/*
** Returns the relative path from home directory
*/

char	*get_relative_path(char *pwd, char *home)
{
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		return (pwd + ft_strlen(home));
	return (pwd);
}

// Function to get the command path
// (either absolute, relative, or found in PATH)
// if (args[0][0] == '<')
// 	exit(127);
char	*get_command_path(char **args, t_cmd *cmd)
{
	char	*cmd_path;

	if (ft_strchr(args[0], '/') != NULL)
		return (args[0]);
	cmd_path = find_command_path(args[0], cmd);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "minishell: %s: command not found\n", args[0]);
		cmd->last_exit_status = 127;
		exit(127);
	}
	return (cmd_path);
}

char	*get_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
