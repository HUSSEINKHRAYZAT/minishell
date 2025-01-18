/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:50:09 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 11:54:00 by hkhrayza         ###   ########.fr       */
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

void	handle_quotes(t_lexer **lexer, char *line, int *i,
		t_quote_type quote_type, int flag_space)
{
	char	*token_start;
	char	end_quote;
	int		j;

	token_start = &line[*i];
	j = 0;
	(*i)++;
	if (quote_type == SINGLE_QUOTES)
		end_quote = '\'';
	else
		end_quote = '\"';
	while (line[*i] && line[*i] != end_quote)
	{
		(*i)++;
		j++;
	}
	if (!line[*i])
	{
		fprintf(stderr, "minishell: unmatched quote\n");
		return ;
	}
	process_quotes(lexer, quote_type, flag_space, token_start, j);
	(*i)++;
}
