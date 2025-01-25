/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:45:48 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/25 09:13:52 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_token(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	if (ft_isspace(line[*i]))
		handlespace(ctx, i);
	else if (line[*i] == '\'' || line[*i] == '\"')
		ctx->exp = handlequotetoken(lexer, line, i, ctx);
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

int	handlequotetoken(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	t_quote_context	quote_ctx;

	if (line[*i] == '\'')
		quote_ctx.quote_type = SINGLE_QUOTES;
	else
		quote_ctx.quote_type = DOUBLE_QUOTES;
	if (line[*i + 1] == '$')
	{
		(*i)++;
		if ((ft_isalpha(line[*i + 1]))
			&& (quote_ctx.quote_type == DOUBLE_QUOTES))
		{
			(*i)++;
			handle_dollar_variable(lexer, line, i, ctx);
		}
		(*i)--;
	}
	quote_ctx.flag_space = ctx->flag_space;
	ctx->exp = handle_quotes(lexer, line, i, quote_ctx);
	ctx->flag_space = 0;
	return (ctx->exp);
}

void	handledollartoken(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	handle_dollar(lexer, line, i, ctx);
	ctx->flag_space = 0;
}

void	handlered(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	handle_redirection_token(lexer, line, i);
	ctx->flag_space = 1;
}
