/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:55:22 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/22 11:25:41 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_single_heredoc(t_lexer **tokens, char ***temp_filenames,
		int *temp_file_count, t_cmd *context)
{
	char	*delimiter;
	char	filename[29];
	int		temp_fd;

	if (!tokens || !*tokens || !(*tokens)->next)
		return (handle_heredoc_error(tokens,
				"minishell: syntax error near unexpected token `newline'\n",
				1));
	delimiter = (*tokens)->next->str;
	if (!delimiter || is_invalid_filename(delimiter))
		return (handle_heredoc_error(tokens,
				"minishell: invalid or no heredoc delimiter specified\n", 1),
			0);
	temp_fd = create_temp_file(filename);
	if (temp_fd == -1)
		return (0);
	if (!process_heredoc(temp_fd, delimiter, context))
	{
		handle_heredoc_error(tokens, "minishell: heredoc interrupted\n", 1);
		return (0);
	}
	close(temp_fd);
	store_temp_filename(temp_filenames, temp_file_count, filename);
	*tokens = (*tokens)->next->next;
	return (1);
}

int	handle_heredocs(t_command *cmd, char ***temp_filenames,
		int *temp_file_count, t_cmd *context)
{
	t_lexer	*current;

	current = cmd->tokens;
	while (current)
	{
		if (ft_strcmp(current->str, "<<") == 0)
		{
			if (!handle_single_heredoc(&current, temp_filenames,
					temp_file_count, context))
				return (0);
		}
		else
			current = current->next;
	}
	redirect_temp_files(*temp_filenames, *temp_file_count);
	return (1);
}

int	execute_command_with_heredoc(t_command *cmd, t_cmd *context)
{
	char	**temp_filenames;
	int		temp_file_count;

	temp_filenames = NULL;
	temp_file_count = 0;
	if (!handle_heredocs(cmd, &temp_filenames, &temp_file_count, context))
	{
		context->last_exit_status = 130;
		cleanup_temp_files(temp_filenames, temp_file_count);
		return (0);
	}
	remove_heredoc_tokens(cmd);
	if (cmd->tokens)
	{
		if (handle_redirections(cmd, context) == 0)
			remove_redirection_tokens(&cmd->tokens, NULL, NULL);
	}
	cleanup_temp_files(temp_filenames, temp_file_count);
	return (1);
}
