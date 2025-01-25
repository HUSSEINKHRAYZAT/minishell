/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerFunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:05:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/24 20:47:42 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Main Lexer Function
*/
t_lexer	*lexer(char *line, t_cmd *cmd)
{
	t_lexer		*lexer;
	int			i;
	t_context	ctx;

	lexer = NULL;
	i = 0;
	ctx.flag_space = 1;
	ctx.exp = 9;
	ctx.cmd = cmd;
	while (line[i])
	{
		handle_token(&lexer, line, &i, &ctx);
		if (ctx.exp == 0)
		{
			free_lexer(lexer);
			return (NULL);
		}
	}
	return (lexer);
}

/*
** Initialize a New Lexer Token
*/
t_lexer	*init_lexer_token(char *str, t_tokens token, t_quote_type quote_type)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
	{
		perror("Failed to allocate memory for lexer token");
		return (NULL);
	}
	new_token->str = ft_strdup(str);
	if (!new_token->str)
	{
		perror("Failed to allocate memory for lexer token string");
		free(new_token);
		return (NULL);
	}
	free(str);
	new_token->token = token;
	new_token->quote_type = quote_type;
	new_token->next = NULL;
	return (new_token);
}

/*
** Process Tokens Inside Quotes
*/
int	process_quotes(t_lexer **lexer, t_process_data *data, int j)
{
	char	*combined_str;
	char	*new_str;
	t_lexer	*last_token;

	last_token = *lexer;
	while (last_token && last_token->next)
		last_token = last_token->next;
	new_str = ft_substr(data->token_start + 1, 0, j);
	if ((last_token && last_token->token == TOKEN_WORD
			&& data->flag_space == 0))
	{
		combined_str = ft_strjoin(last_token->str, new_str);
		free(last_token->str);
		last_token->str = combined_str;
		free(new_str);
	}
	else
		add_lexer_token(lexer, init_lexer_token(new_str, TOKEN_WORD,
				data->quote_type));
	return (0);
}

/*
** Add a Token to the Lexer List
*/
void	add_lexer_token(t_lexer **lexer, t_lexer *new_token)
{
	t_lexer	*temp;

	if (!new_token)
		return ;
	if (!*lexer)
		*lexer = new_token;
	else
	{
		temp = *lexer;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

/*
** Count the Number of Tokens in the Lexer List
*/
int	count_tokens(t_lexer *tokens)
{
	int		count;
	t_lexer	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
