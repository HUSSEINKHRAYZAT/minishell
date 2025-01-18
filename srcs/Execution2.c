/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:47:12 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/18 15:20:32 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_command(t_command *cmd, t_cmd *context, int flage)
{
	int	backup_fds[2];

	if (!cmd || !cmd->tokens || !cmd->tokens->str)
		return (0);
	backup_fds[0] = dup(STDIN_FILENO);
	backup_fds[1] = dup(STDOUT_FILENO);
	if (handle_flag_or_heredoc(cmd, context, flage, backup_fds))
		return (0);
	if (contains_redirection(cmd->tokens) && handle_redirections(cmd,
			context) != 0)
	{
		restore_fds(backup_fds);
		return (0);
	}
	if (cmd->tokens)
		execution(cmd, context);
	restore_fds(backup_fds);
	return (0);
}

int	handle_flag_or_heredoc(t_command *cmd, t_cmd *context, int flage,
		int *backup_fds)
{
          if (contains_heredoc(cmd->tokens))
	{
		execute_command_with_heredoc(cmd, context);
		restore_fds(backup_fds);
		return (1);
	}
          
	if (flage == 1)
	{
                    if(handle_redirections(cmd,context))
                              return (1);
		process_pipes(cmd, context);
		restore_fds(backup_fds);
		return (1);
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
