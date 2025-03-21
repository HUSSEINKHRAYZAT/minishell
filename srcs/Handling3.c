/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:45:48 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/08 11:17:47 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_token(t_lexer **lexer, char *line, int *i, t_cmd *ctx)
{
	if (ft_isspace(line[*i]))
		handlespace(ctx, i);
	else if (line[*i] == '>' || line[*i] == '<')
		handlered(lexer, line, i, ctx);
	else if (line[*i] == '|')
		handlepipetoken(lexer, line, i, ctx);
	else
		handlewordtoken(lexer, line, i, ctx);
	if (ctx->exp == 0)
		return ;
}

void	handlespace(t_cmd *ctx, int *i)
{
	ctx->flag_space = 1;
	(*i)++;
}

void	handlered(t_lexer **lexer, char *line, int *i, t_cmd *ctx)
{
	handle_redirection_token(lexer, line, i, ctx);
	ctx->flag_space = 1;
}

/*
** handle_user_input remains unchanged.
*/
void	handle_user_input(t_cmd *context)
{
	char	*line;

	sig_init();
	while (1)
	{
		line = read_complete_code(context);
		if (context->exp == 0)
		{
			free(line);
			continue ;
		}
		if (!line)
			break ;
		process_input(line, context);
		g_sig.sigint = 0;
	}
}

int	is_inside_quotes(char *line, int index)
{
	int				i;
	t_quote_type	quote_type;

	quote_type = NO_QUOTE;
	i = 0;
	while (line[i] && i < index)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote_type == NO_QUOTE)
			{
				if (line[i] == '\'')
					quote_type = SINGLE_QUOTES;
				else
					quote_type = DOUBLE_QUOTES;
			}
			else if ((quote_type == SINGLE_QUOTES && line[i] == '\'')
				|| (quote_type == DOUBLE_QUOTES && line[i] == '\"'))
			{
				quote_type = NO_QUOTE;
			}
		}
		i++;
	}
	return (quote_type != NO_QUOTE);
}
