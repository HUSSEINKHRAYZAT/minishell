/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:47:12 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/22 11:19:59 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_command(t_command *cmd, t_cmd *context, int pip)
{
	int	backup_fds[2];

	if (!cmd || !cmd->tokens || !cmd->tokens->str)
		return (0);
	backup_fds[0] = dup(STDIN_FILENO);
	backup_fds[1] = dup(STDOUT_FILENO);
	if (handle_flag_or_heredoc(cmd, context, pip, backup_fds))
		return (0);
	if (handle_redirections(cmd, context))
	{
		context->last_exit_status = 2;
		restore_fds(backup_fds);
		return (0);
	}
	if (cmd->tokens)
		execution(cmd, context);
	restore_fds(backup_fds);
	return (0);
}

int	handle_flag_or_heredoc(t_command *cmd, t_cmd *context, int pip,
		int *backup_fds)
{
	if (pip == 1)
	{
		process_pipes(cmd, context);
		restore_fds(backup_fds);
		return (1);
	}
	if (contains_heredoc(cmd->tokens) && (pip != 1))
	{
		if (!execute_command_with_heredoc(cmd, context))
		{
			restore_fds(backup_fds);
			return (1);
		}
	}
	return (0);
}

void	restore_fds(int *backup_fds)
{
	dup2(backup_fds[0], STDIN_FILENO);
	dup2(backup_fds[1], STDOUT_FILENO);
	close(backup_fds[0]);
	close(backup_fds[1]);
}

void	exec_command(char *cmd_path, char **args, t_cmd *cmd)
{
	char	**envp_array;

	envp_array = env_list_to_array(cmd);
	execve(cmd_path, args, envp_array);
	free_array(envp_array);
	perror("execve");
	exit(127);
}
