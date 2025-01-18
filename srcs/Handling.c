/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:12:47 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 11:02:42 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(t_lexer **lexer, char *line, int *i)
{
	(void)(line);
	printf("Detected Pipe Token at index %d\n", *i);
	add_lexer_token(lexer, init_lexer_token(ft_strdup("|"), TOKEN_PIPE,
			NO_QUOTE));
	(*i)++;
}

void	handle_word(t_lexer **lexer, char *line, int *i, int flag_space)
{
	char	*new_token;

	new_token = extract_word(line, i);
	if (flag_space == 1 || *lexer == NULL)
		add_lexer_token(lexer, init_lexer_token(new_token, TOKEN_WORD,
				NO_QUOTE));
	else
		merge_or_add_token(lexer, new_token);
}

char	*extract_word(char *line, int *i)
{
	int		token_start;
	char	*new_token;

	token_start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|'
		&& line[*i] != '\'' && line[*i] != '\"' && line[*i] != '$'
		&& line[*i] != '>' && line[*i] != '<')
		(*i)++;
	new_token = ft_substr(line, token_start, *i - token_start);
	return (new_token);
}

void	merge_or_add_token(t_lexer **lexer, char *new_token)
{
	t_lexer	*last_token;
	char	*combined_str;

	last_token = *lexer;
	while (last_token && last_token->next)
		last_token = last_token->next;
	if (last_token && last_token->token == TOKEN_WORD)
	{
		combined_str = ft_strjoin(last_token->str, new_token);
		free(last_token->str);
		last_token->str = combined_str;
		free(new_token);
	}
	else
		add_lexer_token(lexer, init_lexer_token(new_token, TOKEN_WORD,
				NO_QUOTE));
}
