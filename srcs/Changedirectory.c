/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Changedirectory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:19:21 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/15 17:50:33 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Handles the `cd` command
void	builtin_cd(char **args, t_env *envp)
{
	char	*dir;

	dir = get_target_directory(args, envp);
	change_directory(dir, envp);
}

// Changes the current directory and updates environment variables
// Try to get the current working directory
// If getcwd fails, attempt to move up one directory (cd ..)
// After moving to the parent directory, refresh oldpwd
// Handle `cd -` case
// Try to change directory to the target directory
// Update the new working directory
// Update the environment variables

void	*handle_directory(char *oldpwd)
{
	printf("minishell: getcwd failed, ");
	printf("attempting to move to parent directory (..)");
	if (chdir("..") != 0)
	{
		perror("minishell: cd .. failed");
		return (oldpwd);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("minishell: getcwd after cd ..");
	return (oldpwd);
}

void	change_directory(char *dir, t_env *envp)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = handle_directory(oldpwd);
	if (!oldpwd)
		return ;
	if (dir && ft_strcmp(dir, "~") == 0)
		dir = get_env_var(envp, "HOME");
	if (dir && ft_strcmp(dir, "-") == 0)
	{
		dir = get_env_var(envp, "OLDPWD");
		if (!dir)
			return (printf("minishell: cd: OLDPWD not set\n"), free(oldpwd));
	}
	if (!dir || chdir(dir) != 0)
		return (perror("minishell: cd"), free(oldpwd));
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror("minishell: getcwd"), free(oldpwd));
	set_env_var(envp, "OLDPWD", oldpwd);
	set_env_var(envp, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
}

// Processes an argument for `export` command
void	process_export_argument(char *arg, t_env *envp)
{
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
	{
		*eq_pos = '\0';
		set_env_var(envp, arg, eq_pos + 1);
		*eq_pos = '=';
	}
	else
	{
		set_env_var_hidden(envp, arg, NULL, 1);
	}
}
