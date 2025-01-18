/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecutionFunctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:42:10 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 09:48:47 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtin_command(t_command *cmd, t_cmd *context)
{
	char	**args;

	args = lexer_to_args(cmd->tokens);
	if (!args)
		return ;
	if (!ft_strcmp(args[0], "echo"))
		builtin_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		builtin_cd(args, context->envp);
	else if (!ft_strcmp(args[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(args[0], "export"))
		builtin_export(args, context->envp);
	else if (!ft_strcmp(args[0], "unset"))
		builtin_unset(args, &context->envp);
	else if (!ft_strcmp(args[0], "env"))
		builtin_env(context->envp);
	else if (!ft_strcmp(args[0], "exit"))
		builtin_exit(cmd);
	free_array(args);
}

char	**lexer_to_args(t_lexer *tokens)
{
	t_lexer	*current;
	char	**args;
	int		i;

	args = allocate_args(count_tokens(tokens));
	if (!args)
		return (NULL);
	current = tokens;
	i = 0;
	while (current)
	{
		args[i] = ft_strdup(current->str);
		if (!args[i])
		{
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

// Function to execute the command using execve
void	exec_command(char *cmd_path, char **args, t_cmd *cmd)
{
	char	**envp_array;

	envp_array = env_list_to_array(cmd);
	execve(cmd_path, args, envp_array);
	free_array(envp_array);
	perror("execve");
	exit(127);
}

// Main function to handle external command execution
void	execute_external_command(char **args, t_cmd *cmd)
{
	pid_t	pid;
	char	*cmd_path;

	if (is_directory(args[0]))
		return ;
	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_command_path(args, cmd);
		exec_command(cmd_path, args, cmd);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
}

int	execution(t_command *cmd, t_cmd *context)
{
	char	**args;

	args = NULL;
	if (is_builtin(cmd->tokens->str))
	{
		execute_builtin_command(cmd, context);
	}
	else
	{
		args = lexer_to_args(cmd->tokens);
		if (args)
		{
			execute_external_command(args, context);
			free_array(args);
		}
	}
	return (0);
}
