/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:19:08 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 18:41:21 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:19:08 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 18:30:00 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc_error(t_lexer **tokens, char *message, int move_next)
{
	write(STDERR_FILENO, message, strlen(message));
	if (move_next && tokens && *tokens)
	{
		*tokens = (*tokens)->next;
		return (1);
	}
	return (0);
}

int	create_temp_file(char *filename)
{
	int	temp_fd;

	strcpy(filename, "/tmp/minishell_heredocXXXXXX");
	temp_fd = mkstemp(filename);
	if (temp_fd == -1)
		perror("minishell: cannot create temporary file");
	return (temp_fd);
}

void	store_temp_filename(char ***temp_filenames, int *temp_file_count,
		char *filename)
{
	char	**new_temp_filenames;

	new_temp_filenames = realloc(*temp_filenames, sizeof(char *)
			* (*temp_file_count + 1));
	if (!new_temp_filenames)
	{
		perror("minishell: memory allocation error");
		unlink(filename);
		return ;
	}
	*temp_filenames = new_temp_filenames;
	(*temp_filenames)[*temp_file_count] = strdup(filename);
	if (!(*temp_filenames)[*temp_file_count])
	{
		perror("minishell: memory allocation error");
		unlink(filename);
		return ;
	}
	(*temp_file_count)++;
}

void	cleanup_temp_files(char **temp_filenames, int temp_file_count)
{
	int	i;

	i = 0;
	while (i < temp_file_count)
	{
		if (temp_filenames[i])
		{
			unlink(temp_filenames[i]);
			free(temp_filenames[i]);
		}
		i++;
	}
	free(temp_filenames);
}

void	remove_heredoc_tokens(t_command *cmd)
{
	t_lexer	*current;
	t_lexer	*prev;
	t_lexer	*temp;

	current = cmd->tokens;
	prev = NULL;
	while (current)
	{
		if (current->token == TOKEN_HEREDOC && current->next)
		{
			temp = current->next->next;
			if (prev)
				prev->next = temp;
			else
				cmd->tokens = temp;
			current->next->next = NULL;
			free_lexer(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}
