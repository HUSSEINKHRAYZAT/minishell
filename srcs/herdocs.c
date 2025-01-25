/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:10:46 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 18:41:30 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_heredoc(int temp_fd, char *delimiter)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	while (1)
	{
		init_heredoc_signals();
		printf("heredoc> ");
		fflush(stdout);
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
		{
			perror("minishell: input error\n");
			break ;
		}
		buffer[bytes_read] = '\0';
		process_heredoc_input(temp_fd, buffer, delimiter);
		if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
			&& buffer[strlen(delimiter)] == '\n')
			break ;
	}
	reset_signals_after_heredoc();
}

int	handle_single_heredoc(t_lexer **tokens, char ***temp_filenames,
		int *temp_file_count)
{
	char	*delimiter;
	char	filename[29];
	int		temp_fd;

	if (!tokens || !*tokens || !(*tokens)->next)
		return (handle_heredoc_error(tokens,
				"minishell: syntax error near `newline`\n", 1));
	delimiter = (*tokens)->next->str;
	if (!delimiter || is_invalid_filename(delimiter))
	{
		handle_heredoc_error(tokens,
			"minishell: invalid or no heredoc delimiter specified\n", 1);
		return (0);
	}
	temp_fd = create_temp_file(filename);
	if (temp_fd == -1)
		return (0);
	process_heredoc(temp_fd, delimiter);
	close(temp_fd);
	store_temp_filename(temp_filenames, temp_file_count, filename);
	*tokens = (*tokens)->next->next;
	return (1);
}

int	handle_heredocs(t_command *cmd, char ***temp_filenames,
		int *temp_file_count)
{
	t_lexer	*current;

	current = cmd->tokens;
	while (current)
	{
		if (ft_strcmp(current->str, "<<") == 0)
		{
			handle_single_heredoc(&current, temp_filenames, temp_file_count);
		}
		else
			current = current->next;
	}
	redirect_temp_files(*temp_filenames, *temp_file_count);
	return (1);
}

void	execute_command_with_heredoc(t_command *cmd, t_cmd *context)
{
	char	**temp_filenames;
	int		temp_file_count;

	temp_filenames = NULL;
	temp_file_count = 0;
	if (!handle_heredocs(cmd, &temp_filenames, &temp_file_count))
		return ;
	remove_heredoc_tokens(cmd);
	if (cmd->tokens)
	{
		if (handle_redirections(cmd, context))
			remove_redirection_tokens(&cmd->tokens, NULL, NULL);
		else
			execution(cmd, context);
	}
	cleanup_temp_files(temp_filenames, temp_file_count);
}

void	redirect_temp_files(char **temp_filenames, int temp_file_count)
{
	int	temp_fd;
	int	i;

	i = 0;
	while (i < temp_file_count)
	{
		temp_fd = open(temp_filenames[i], O_RDONLY);
		if (temp_fd == -1)
		{
			perror("minishell: cannot open temporary file for reading");
			i++;
			continue ;
		}
		if (dup2(temp_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: heredoc input redirection");
			close(temp_fd);
			i++;
			continue ;
		}
		close(temp_fd);
		i++;
	}
}
