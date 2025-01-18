/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:08:25 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 12:15:44 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_command(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*temp;

	if (!cmd_list || !new_cmd)
		return ;
	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		temp = *cmd_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
		new_cmd->prev = temp;
	}
}

/*
** Parser function to convert lexer tokens into commands
*/
void	handle_placeholder_token(t_command *current_cmd)
{
	t_lexer	*placeholder_token;

	if (!current_cmd->tokens && current_cmd->redirects)
	{
		placeholder_token = init_lexer_token(ft_strdup(""), TOKEN_WORD,
				NO_QUOTE);
		if (!placeholder_token)
		{
			perror("Failed to allocate placeholder token");
			free_command(current_cmd);
			return ;
		}
		add_token_to_command(current_cmd, placeholder_token);
	}
}

void	handle_pipe_token(t_command **cmd_list, t_command **current_cmd)
{
	if (*current_cmd)
	{
		handle_placeholder_token(*current_cmd);
		add_command(cmd_list, *current_cmd);
		*current_cmd = NULL;
	}
}

void	handle_other_token(t_command **current_cmd, t_lexer *current_token)
{
	if (!*current_cmd)
		*current_cmd = init_command();
	add_token_to_command(*current_cmd, current_token);
}
