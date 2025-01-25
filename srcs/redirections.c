/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:37:16 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 17:03:52 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_herdoc(t_lexer *current)
{
	while (current)
	{
		if (ft_strcmp(current->str, "<<"))
			return (1);
		current = current->next;
	}
	return (0);
}

int	is_invalid_filename(const char *filename)
{
	if (!filename)
		return (1);
	while (*filename)
	{
		if (*filename == '<' || *filename == '>' || *filename == '|')
			return (1);
		filename++;
	}
	return (0);
}

t_lexer	*process_redirection(t_command *cmd, t_lexer *current,
		int (*handler)(t_command *), char *type)
{
	t_lexer	*file_token;

	file_token = current->next;
	if (!file_token)
	{
		if (ft_strcmp(type, "<<") != 0)
			fprintf(stderr, "Syntax error: Missing file after '%s'\n", type);
		return (NULL);
	}
	if (is_invalid_filename(file_token->str))
	{
		fprintf(stderr, "Syntax error: Invalid file name '%s'\n",
			file_token->str);
		return (NULL);
	}
	if (handler(cmd) == -1)
		return (NULL);
	remove_redirection_tokens(&cmd->tokens, current, file_token);
	return (cmd->tokens);
}

int	handle_redirections(t_command *cmd, t_cmd *context)
{
	t_lexer	*current;

	(void)context;
	current = cmd->tokens;
	while (current)
	{
		if (is_output_redirection(current))
			current = process_redirection(cmd, current, &handle_output, ">");
		else if (is_append_redirection(current))
			current = process_redirection(cmd, current, &handle_append, ">>");
		else if (is_input_redirection(current))
			current = process_redirection(cmd, current, &handle_input, "<");
		else if (is_herdoc_redirection(current))
			current = process_redirection(cmd, current, &herdoo, "<<");
		if (current == NULL)
			return (1);
		current = current->next;
	}
	return (0);
}
