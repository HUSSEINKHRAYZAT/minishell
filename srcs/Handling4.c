/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:48:00 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/08 12:25:05 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handlepipetoken(t_lexer **lexer, char *line, int *i, t_cmd *ctx)
{
	handle_pipe(lexer, line, i);
	ctx->flag_space = 1;
}

void	handlewordtoken(t_lexer **lexer, char *line, int *i, t_cmd *ctx)
{
	handle_word(lexer, line, i, ctx);
	ctx->flag_space = 0;
}

void	add_redirection_token(t_lexer **lexer, char *line, int *i, int type)
{
	int	len;

	len = 0;
	if ((type == TOKEN_APPEND) || (type == TOKEN_HEREDOC))
		len = 2;
	else if ((type == TOKEN_REDIRECT_IN) || (type == TOKEN_REDIRECT_OUT))
		len = 1;
	add_lexer_token(lexer, init_lexer_token(ft_strndup(line + *i, len), type,
			NO_QUOTE));
	*i += len;
}
