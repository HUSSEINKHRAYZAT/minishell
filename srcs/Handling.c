/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabbas <kabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:12:47 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/03 10:00:00 by kabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"'
		|| c == '$');
}

static int	process_no_quote(char **buffer, char *line, int *i, t_cmd *ctx)
{
	char	current;

	current = line[*i];
	if (current == '\'')
		ctx->quote_type = SINGLE_QUOTES;
	else if (current == '\"')
		ctx->quote_type = DOUBLE_QUOTES;
	else if (current == '$')
	{
		*buffer = ft_strjoin_free(*buffer, handle_dollar_expansion(line, i,
					ctx));
		return (1);
	}
	else if (ft_isspace(current) || is_special_char(current))
		return (0);
	else
		*buffer = append_char(*buffer, current);
	(*i)++;
	return (1);
}

static int	process_single_quote(char **buffer, char *line, int *i, t_cmd *ctx)
{
	char	current;

	current = line[*i];
	if (current == '\'')
	{
		ctx->quote_type = NO_QUOTE;
		(*i)++;
	}
	else
	{
		*buffer = append_char(*buffer, current);
		(*i)++;
	}
	return (1);
}

static int	process_double_quote(char **buffer, char *line, int *i, t_cmd *ctx)
{
	char	current;

	current = line[*i];
	if (current == '\"')
	{
		ctx->quote_type = NO_QUOTE;
		(*i)++;
	}
	else if (current == '$')
	{
		*buffer = ft_strjoin_free(*buffer, handle_dollar_expansion(line, i,
					ctx));
	}
	else
	{
		*buffer = append_char(*buffer, current);
		(*i)++;
	}
	return (1);
}

void	handle_word(t_lexer **lexer, char *line, int *i, t_cmd *ctx)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (!buffer)
		return ;
	ctx->quote_type = NO_QUOTE;
	while (line[*i])
	{
		if (ctx->quote_type == NO_QUOTE)
		{
			if (!process_no_quote(&buffer, line, i, ctx))
				break ;
		}
		else if (ctx->quote_type == SINGLE_QUOTES)
			process_single_quote(&buffer, line, i, ctx);
		else if (ctx->quote_type == DOUBLE_QUOTES)
			process_double_quote(&buffer, line, i, ctx);
	}
	if (ctx->quote_type != NO_QUOTE)
	{
		free_lexer2(lexer);
		return (free(buffer));
	}
	add_lexer_token(lexer, init_lexer_token(buffer, TOKEN_WORD, NO_QUOTE));
}
//
//
//
//
// if you want to stop if unmatched quotes. put this before add lexer
// printf("unmatched quotes\n");
// ctx->last_exit_status = 2;
// 	ctx->exp = 0;
//
//
//
//
// void	handle_word(t_lexer **lexer, char *line, int *i, t_cmd *ctx)
// {
// 	char	*buffer;
// 	char	current_char;
// 	char	*expanded;
//
// 	buffer = ft_strdup("");
// 	if (!buffer)
// 		return ;
// 	ctx->quote_type = NO_QUOTE;
// 	while (line[*i])
// 	{
// 		current_char = line[*i];
// 		if (ctx->quote_type == NO_QUOTE)
// 		{
// 			if (current_char == '\'')
// 			{
// 				ctx->quote_type = SINGLE_QUOTES;
// 				(*i)++;
// 				continue ;
// 			}
// 			else if (current_char == '\"')
// 			{
// 				ctx->quote_type = DOUBLE_QUOTES;
// 				(*i)++;
// 				continue ;
// 			}
// 			else if (current_char == '$')
// 			{
// 				expanded = handle_dollar_expansion(line, i, ctx);
// 				if (!expanded)
// 					expanded = ft_strdup("");
// 				buffer = ft_strjoin_free(buffer, expanded);
// 				continue ;
// 			}
// 			else if (ft_isspace(current_char) || is_special_char(current_char))
// 			{
// 				break ;
// 			}
// 			else
// 			{
// 				buffer = append_char(buffer, current_char);
// 				(*i)++;
// 				continue ;
// 			}
// 		}
// 		else if (ctx->quote_type == SINGLE_QUOTES)
// 		{
// 			if (current_char == '\'')
// 			{
// 				ctx->quote_type = NO_QUOTE;
// 				(*i)++;
// 				continue ;
// 			}
// 			else
// 			{
// 				buffer = append_char(buffer, current_char);
// 				(*i)++;
// 				continue ;
// 			}
// 		}
// 		else if (ctx->quote_type == DOUBLE_QUOTES)
// 		{
// 			if (current_char == '\"')
// 			{
// 				ctx->quote_type = NO_QUOTE;
// 				(*i)++;
// 				continue ;
// 			}
// 			else if (current_char == '$')
// 			{
// 				expanded = handle_dollar_expansion(line, i, ctx);
// 				if (!expanded)
// 					expanded = ft_strdup("");
// 				buffer = ft_strjoin_free(buffer, expanded);
// 				continue ;
// 			}
// 			else
// 			{
// 				buffer = append_char(buffer, current_char);
// 				(*i)++;
// 				continue ;
// 			}
// 		}
// 	}
// 	if (ctx->quote_type != NO_QUOTE)
// 	{
// 		// printf("minishell: unmatched quote\n");
// 		free(buffer);
// 		// Optionally, set an error status in ctx
// 		ctx->last_exit_status = 2;
// 		free_lexer(*lexer);
// 		*lexer = NULL;
// 		return ;
// 	}
// 	add_lexer_token(lexer, init_lexer_token(buffer, TOKEN_WORD,
// 			ctx->quote_type));
// }