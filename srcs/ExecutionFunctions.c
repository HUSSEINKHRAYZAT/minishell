/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecutionFunctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:42:10 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/08 11:51:59 by hkhrayza         ###   ########.fr       */
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
		builtin_exit(cmd, context);
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

void	handle_child_process(char **args, t_cmd *cmd)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd_path = get_command_path(args, cmd);
	exec_command(cmd_path, args, cmd);
	cmd->last_exit_status = 0;
	exit(EXIT_SUCCESS);
}

void	execute_external_command(char **args, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (is_directory(args[0]))
	{
		cmd->last_exit_status = 126;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		handle_child_process(args, cmd);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		sig_init();
		if (status & 127)
			cmd->last_exit_status = 128 + (status & 127);
		else
			cmd->last_exit_status = status >> 8;
		return ;
	}
	perror("fork");
}

int	execution(t_command *cmd, t_cmd *context)
{
	char	**args;

	args = NULL;
	if (is_builtin(cmd->tokens->str))
	{
		execute_builtin_command(cmd, context);
		context->last_exit_status = 0;
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
