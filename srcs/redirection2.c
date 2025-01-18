/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:00:01 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 13:43:37 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_redirection_tokens(t_lexer **tokens, t_lexer *redirection,
		t_lexer *file_token)
{
	t_lexer	*current;
	t_lexer	*prev;
	t_lexer	*to_free;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current == redirection || current == file_token)
		{
			to_free = current;
			if (prev)
				prev->next = current->next;
			else
				*tokens = current->next;
			current = current->next;
			free(to_free->str);
			free(to_free);
			if (to_free == file_token)
				break ;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	handle_append(t_command *cmd)
{
	int		fd;
	char	*file_name;

	file_name = get_append_file(cmd->tokens);
	if (!file_name)
	{
		fprintf(stderr, "minishell: no append file specified\n");
		return (-1);
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: open file for append");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: redirect append output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_output(t_command *cmd)
{
	int		fd;
	char	*file_name;

	file_name = get_output_file(cmd->tokens);
	if (!file_name)
	{
		fprintf(stderr, "minishell: no output file specified\n");
		return (-1);
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: open file for writing");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: redirect output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_input(t_command *cmd)
{
	char	*file_name;
	int		fd;

	file_name = get_input_file(cmd->tokens);
	if (!file_name)
	{
		fprintf(stderr, "minishell: no input file specified\n");
		return (-1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: open file for reading");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: redirect input");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
