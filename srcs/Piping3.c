/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piping3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:55:30 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 19:03:15 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_and_wait(int *pipes, int pipe_count)
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
	free(pipes);
}

void	handle_error_and_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	count_commands(t_command *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}
