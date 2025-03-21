/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:01:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/22 11:28:07 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_pipes(int **pipes, int cmd_count)
{
	int	i;
	int	pipe_count;

	i = 0;
	i = 0;
	pipe_count = (cmd_count - 1) * 2;
	*pipes = malloc(pipe_count * sizeof(int));
	if (!*pipes)
		return (-1);
	while (i < pipe_count)
	{
		if (pipe(*pipes + i) == -1)
		{
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
		exit(EXIT_FAILURE);
	if (i < data->pipe_count / 2 && dup2(data->pipes[i * 2 + 1],
			STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	while (j < data->pipe_count)
		close(data->pipes[j++]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(data->cmd, data->context) != 0)
		exit(EXIT_FAILURE);
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
			return ;
		if (pid == 0)
			setup_child_process(i, &data);
		cmd = cmd->next;
		i++;
	}
}

void	process_pipes(t_command *cmd_list, t_cmd *context)
{
	t_command	*current;
	int			*pipes;
	int			pipe_count;

	current = cmd_list;
	while (current)
	{
		if (contains_heredoc(current->tokens)
			&& !execute_command_with_heredoc(current, context))
			return ;
		current = current->next;
	}
	if (count_commands(cmd_list) < 2)
	{
		execute_command(cmd_list, context);
		return ;
	}
	pipe_count = create_pipes(&pipes, count_commands(cmd_list));
	if (pipe_count == -1)
		return ;
	context->parser = cmd_list;
	signal(SIGINT, SIG_IGN);
	process_commands(cmd_list, context, pipes, pipe_count);
	close_and_wait(pipes, pipe_count);
	sig_init();
}
