/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:01:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 12:57:09 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Parent process handler */
void	parent_process(int *pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i]);
		i++;
	}
	while (wait(NULL) > 0)
	{
	}
}

/* Child process handler */
void	child_process(t_command *cmd, int *pipes, int index, int pipe_count,
		t_cmd *context)
{
	int	i;

	if (index > 0)
	{
		if (dup2(pipes[(index - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("Failed to redirect input");
			exit(EXIT_FAILURE);
		}
	}
	if (index < pipe_count / 2)
	{
		if (dup2(pipes[index * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("Failed to redirect output");
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < pipe_count)
		close(pipes[i++]);
	execute_command(cmd, context);
	free_lexer(cmd->tokens);
	exit(EXIT_FAILURE);
}

void	process_pipes(t_command *cmd_list, t_cmd *context)
{
	int			cmd_count;
	int			pipe_count;
	int			*pipes;
	t_command	*cmd;
	pid_t		pid;
	int			i;

	cmd_count = 0;
	cmd = cmd_list;
	while (cmd)
	{
		cmd_count++;
		cmd = cmd->next;
	}
	if (cmd_count < 2)
	{
		execute_command(cmd_list, context);
		return ;
	}
	pipe_count = (cmd_count - 1) * 2;
	pipes = malloc(pipe_count * sizeof(int));
	if (!pipes)
	{
		perror("Failed to allocate memory for pipes");
		return ;
	}
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipes + i) == -1)
		{
			perror("Pipe creation failed");
			free(pipes);
			return ;
		}
		i += 2;
	}
	cmd = cmd_list;
	i = 0;
	while (cmd && i < cmd_count)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			break ;
		}
		if (pid == 0)
		{
			if (i > 0)
			{
				if (dup2(pipes[(i - 1) * 2], STDIN_FILENO) == -1)
				{
					perror("Failed to redirect input");
					exit(EXIT_FAILURE);
				}
			}
			if (i < cmd_count - 1)
			{
				if (dup2(pipes[i * 2 + 1], STDOUT_FILENO) == -1)
				{
					perror("Failed to redirect output");
					exit(EXIT_FAILURE);
				}
			}
			i = 0;
			while (i < pipe_count)
			{
				close(pipes[i]);
				i++;
			}
			if (contains_heredoc(cmd->tokens))
				execute_command_with_heredoc(cmd, context);
			else
				execute_command(cmd, context);
			exit(EXIT_FAILURE);
		}
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i]);
		i++;
	}
	while (wait(NULL) > 0)
	{
	}
	free(pipes);
}
