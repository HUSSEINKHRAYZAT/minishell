/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:39:37 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/03 20:50:49 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Handles the `export` command
void	builtin_export(char **args, t_env *envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		process_export_argument(args[i], envp);
		i++;
	}
	if (i == 1)
		print_sorted_env_vars(envp);
}

// Handles the `unset` command
void	builtin_unset(char **args, t_env **envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(args[i], envp);
		i++;
	}
}

// Prints all non-hidden environment variables
void	builtin_env(t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		if (current->hidden == 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

// Handles the `echo` command
void	builtin_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

// Prints the current working directory
void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("minishell: pwd");
}
