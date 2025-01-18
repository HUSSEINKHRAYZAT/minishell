/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:16:57 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 12:16:06 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Initialize a new command structure
*/
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("Failed to allocate memory for command");
		return (NULL);
	}
	cmd->tokens = NULL;
	cmd->builtin = NULL;
	cmd->redirects = NULL;
	cmd->heredoc_delimiters = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
** Utility to add a lexer token to a linked list
*/
static t_lexer	*add_token_to_list(t_lexer *list, t_lexer *new_token)
{
	t_lexer	*temp;

	if (!list)
		return (new_token);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	return (list);
}

/*
** Add a token to the current command's token list
*/
void	add_token_to_command(t_command *cmd, t_lexer *token)
{
	t_lexer	*new_token;

	if (!cmd || !token)
		return ;
	new_token = init_lexer_token(ft_strdup(token->str), token->token,
			token->quote_type);
	if (!new_token)
	{
		perror("Failed to allocate memory for lexer token");
		return ;
	}
	cmd->tokens = add_token_to_list(cmd->tokens, new_token);
}

/*
** Add a command to the command linked list
*/

t_command	*parser(t_lexer *lexer)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_lexer		*current_token;

	cmd_list = NULL;
	current_cmd = NULL;
	current_token = lexer;
	while (current_token)
	{
		if (current_token->token == TOKEN_PIPE)
			handle_pipe_token(&cmd_list, &current_cmd);
		else
			handle_other_token(&current_cmd, current_token);
		current_token = current_token->next;
	}
	if (current_cmd)
	{
		handle_placeholder_token(current_cmd);
		add_command(&cmd_list, current_cmd);
	}
	return (cmd_list);
}
