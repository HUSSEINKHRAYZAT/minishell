/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:50:09 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/24 20:46:30 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Main function to handle the user input loop */

void	handle_user_input(t_cmd *context)
{
	char	*line;

	sig_init();
	while (1)
	{
		line = read_input(context);
		if (!line)
		{
			ft_putstr_fd("exit\n", STDERR);
			break ;
		}
		process_input(line, context);
	}
}

void	handle_redirection_token(t_lexer **lexer, char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_lexer_token(lexer, init_lexer_token(ft_strdup(">>"), TOKEN_APPEND,
				NO_QUOTE));
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		add_lexer_token(lexer, init_lexer_token(ft_strdup(">"),
				TOKEN_REDIRECT_OUT, NO_QUOTE));
		(*i)++;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_lexer_token(lexer, init_lexer_token(ft_strdup("<<"), TOKEN_HEREDOC,
				NO_QUOTE));
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		add_lexer_token(lexer, init_lexer_token(ft_strdup("<"),
				TOKEN_REDIRECT_IN, NO_QUOTE));
		(*i)++;
	}
}

char	determinequote(t_quote_type quote_ctx)
{
	if (quote_ctx == SINGLE_QUOTES)
		return ('\'');
	else if (quote_ctx == DOUBLE_QUOTES)
		return ('\"');
	return (0);
}

int	handle_quotes(t_lexer **lexer, char *line, int *i,
		t_quote_context quote_ctx)
{
	char			*token_start;
	char			end_quote;
	int				j;
	t_process_data	data;

	token_start = &line[*i];
	j = 0;
	(*i)++;
	end_quote = determinequote(quote_ctx.quote_type);
	while (line[*i] && line[*i] != end_quote)
	{
		(*i)++;
		j++;
	}
	if (!line[*i])
	{
		printf("minishell:unmatched quote near '%c'\n", token_start[0]);
		return (0);
	}
	data.quote_type = quote_ctx.quote_type;
	data.flag_space = quote_ctx.flag_space;
	data.token_start = token_start;
	process_quotes(lexer, &data, j);
	(*i)++;
	return (data.quote_type);
}
