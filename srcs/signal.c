/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/17 14:53:09 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 14:53:09 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	disable_ctrl_c(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// Custom signal handler for Ctrl+C (SIGINT)
void	sig_int(int code)
{
	(void)code;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_tstp(int code)
{
	(void)code;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.sigtstp = 1;
}

// Custom signal handler for Ctrl+\ (SIGQUIT)
void	sig_quit(int code)
{
	(void)code;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Initialize signals
// disable_ctrl_c();
void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.sigtstp = 0;
	g_sig.g_heredoc_interrupted = 0;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	signal(SIGTSTP, sig_tstp);
}
