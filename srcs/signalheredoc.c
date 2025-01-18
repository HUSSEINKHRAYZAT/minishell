/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:32:16 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 14:53:00 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Signal handler for SIGINT during heredoc
void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nheredoc> ", 11);
	g_sig.g_heredoc_interrupted = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
}

// Initialize signals for heredoc
void	init_heredoc_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Reset signals after heredoc
void	reset_signals_after_heredoc(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	sig_init();
}
