/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:01:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 19:02:55 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_pipes(int **pipes, int cmd_count)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = (cmd_count - 1) * 2;
	*pipes = malloc(pipe_count * sizeof(int));
	if (!*pipes)
	{
		perror("Failed to allocate memory for pipes");
		return (-1);
	}
	while (i < pipe_count)
	{
		if (pipe(*pipes + i) == -1)
		{
			perror("Pipe creation failed");
			free(*pipes);
			return (-1);
		}
		i += 2;
	}
	return (pipe_count);
}

void	setup_child_process(int i, t_pip *data)
{
	int	j;

	j = 0;
	if (i > 0 && dup2(data->pipes[(i - 1) * 2], STDIN_FILENO) == -1)
		handle_error_and_exit("Failed to redirect input");
	if (i < data->pipe_count / 2 && dup2(data->pipes[i * 2 + 1],
			STDOUT_FILENO) == -1)
		handle_error_and_exit("Failed to redirect output");
	while (j < data->pipe_count)
		close(data->pipes[j++]);
	if (is_herdoc(data->cmd->tokens))
		execute_command_with_heredoc(data->cmd, data->context);
	else
		execute_command(data->cmd, data->context);
	exit(EXIT_FAILURE);
}

void	process_commands(t_command *cmd, t_cmd *context, int *pipes,
		int pipe_count)
{
	pid_t	pid;
	int		i;
	t_pip	data;

	i = 0;
	data.context = context;
	data.pipes = pipes;
	data.pipe_count = pipe_count;
	while (cmd)
	{
		data.cmd = cmd;
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			return ;
		}
		if (pid == 0)
			setup_child_process(i, &data);
		cmd = cmd->next;
		i++;
	}
}

void	process_pipes(t_command *cmd_list, t_cmd *context)
{
	int	*pipes;
	int	pipe_count;

	if (count_commands(cmd_list) < 2)
	{
		execute_command(cmd_list, context);
		return ;
	}
	pipe_count = create_pipes(&pipes, count_commands(cmd_list));
	if (pipe_count == -1)
		return ;
	process_commands(cmd_list, context, pipes, pipe_count);
	close_and_wait(pipes, pipe_count);
}
