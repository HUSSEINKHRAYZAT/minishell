/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boolean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:36:23 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/03 12:53:14 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_input_redirection(t_lexer *token)
{
	while (token)
	{
		if (token->token == TOKEN_REDIRECT_IN)
			return (1);
		token = token->next;
	}
	return (0);
}

int	contains_append(t_lexer *token)
{
	while (token)
	{
		if (token->token == TOKEN_APPEND)
			return (1);
		token = token->next;
	}
	return (0);
}

int	contains_output_redirection(t_lexer *token)
{
	while (token)
	{
		if (token->token == TOKEN_REDIRECT_OUT)
			return (1);
		token = token->next;
	}
	return (0);
}

int	contains_heredoc(t_lexer *token)
{
	while (token)
	{
		if (token->token == TOKEN_HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}

int	contains_pipes(t_lexer *token)
{
	while (token)
	{
		if (token->token == TOKEN_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}
