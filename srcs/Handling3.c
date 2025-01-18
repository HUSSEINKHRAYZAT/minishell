/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:45:48 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 11:53:33 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_token(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	if (ft_isspace(line[*i]))
		handlespace(ctx, i);
	else if (line[*i] == '\'' || line[*i] == '\"')
		handlequotetoken(lexer, line, i, ctx);
	else if (line[*i] == '$')
		handledollartoken(lexer, line, i, ctx);
	else if (line[*i] == '>' || line[*i] == '<')
		handlered(lexer, line, i, ctx);
	else if (line[*i] == '|')
		handlepipetoken(lexer, line, i, ctx);
	else
		handlewordtoken(lexer, line, i, ctx);
}

void	handlespace(t_context *ctx, int *i)
{
	ctx->flag_space = 1;
	(*i)++;
}

void	handlequotetoken(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	int	quoting;

	if (line[*i] == '\'')
		quoting = SINGLE_QUOTES;
	else
		quoting = DOUBLE_QUOTES;
	handle_quotes(lexer, line, i, quoting, ctx->flag_space);
	ctx->flag_space = 0;
}

void	handledollartoken(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	handle_dollar(lexer, line, i, ctx->cmd);
	ctx->flag_space = 0;
}

void	handlered(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	handle_redirection_token(lexer, line, i);
	ctx->flag_space = 1;
}
