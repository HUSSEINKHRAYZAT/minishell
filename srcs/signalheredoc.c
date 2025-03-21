/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:32:16 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/07 21:22:26 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_sig.g_heredoc_interrupted = 1;
	write(STDERR_FILENO, "\n", 1);
	close(STDIN_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
}

// Initialize signals for heredoc
void	init_heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
