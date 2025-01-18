/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cleaning2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:44:26 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 10:23:27 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup(t_cmd *context)
{
	free_my_env(context->envp);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp;

	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
		free(temp->str);
		free(temp);
	}
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free_command(temp);
	}
}

void	free_tokens(t_lexer *tokens)
{
	t_lexer	*temp_token;
	t_lexer	*next_token;

	temp_token = tokens;
	while (temp_token)
	{
		next_token = temp_token->next;
		free(temp_token->str);
		free(temp_token);
		temp_token = next_token;
	}
}

void	free_heredoc_delimiters(char **heredoc_delimiters)
{
	int	i;

	i = 0;
	while (heredoc_delimiters[i])
	{
		free(heredoc_delimiters[i]);
		i++;
	}
	free(heredoc_delimiters);
}
