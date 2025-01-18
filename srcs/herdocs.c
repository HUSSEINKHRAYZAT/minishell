/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:10:46 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/18 15:24:31 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_heredoc(int temp_fd, char *delimiter)
{
	char	buffer[1024];
	char	*variable_name;
	char	*newline_pos;
	char	*env_value;
	ssize_t	bytes_read;

	while (1)
	{
                    init_heredoc_signals();
                    fflush(stdout);
		printf("heredoc> ");
		fflush(stdout);
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
		{
			perror("minishell: input error\n");
			break ;
		}
		buffer[bytes_read] = '\0';
		if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
			&& buffer[strlen(delimiter)] == '\n')
			break ;
		if (buffer[0] == '$')
		{
			variable_name = buffer + 1;
			newline_pos = strchr(variable_name, '\n');
			if (newline_pos)
				*newline_pos = '\0';
			env_value = getenv(variable_name);
			if (env_value)
			{
				if (write(temp_fd, env_value, strlen(env_value)) == -1)
				{
					perror("minishell: write to temporary file\n");
					break ;
				}
				write(temp_fd, "\n", 1);
				continue ;
			}
		}
		if (write(temp_fd, buffer, strlen(buffer)) == -1)
		{
			perror("minishell: write to temporary file\n");
			break ;
		}
	}
          reset_signals_after_heredoc();
}

void	handle_single_heredoc(t_lexer **tokens, char ***temp_filenames,
		int *temp_file_count)
{
	char	*delimiter;
	char	filename[29];
	int		temp_fd;

	strcpy(filename, "/tmp/minishell_heredocXXXXXX");
	temp_fd = mkstemp(filename);
	if (!(*tokens) || !(*tokens)->next)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline`\n \n", 58);
		if (*tokens)
			*tokens = (*tokens)->next;
		return ;
	}
	delimiter = (*tokens)->next->str;
	if (!delimiter || is_invalid_filename(delimiter))
	{
		write(STDERR_FILENO, "minishell: invalid or no heredoc delimiter specified\n", 54);
		*tokens = (*tokens)->next->next;
		return ;
	}
	if (temp_fd == -1)
	{
		perror("minishell: cannot create temporary file");
		return ;
	}
	process_heredoc(temp_fd, delimiter);
	close(temp_fd);
	*temp_filenames = realloc(*temp_filenames, sizeof(char *)
			* (*temp_file_count + 1));
	if (!*temp_filenames)
	{
		perror("minishell: memory allocation error");
		unlink(filename);
		return ;
	}
	(*temp_filenames)[*temp_file_count] = strdup(filename);
	if (!(*temp_filenames)[*temp_file_count])
	{
		perror("minishell: memory allocation error");
		unlink(filename);
		return ;
	}
	(*temp_file_count)++;
	*tokens = (*tokens)->next->next;
}

void	handle_heredocs(t_command *cmd, char ***temp_filenames,
		int *temp_file_count)
{
	t_lexer	*current;
	int		i;
	int		temp_fd;

	current = cmd->tokens;
	i = 0;
	while (current)
	{
		if (strcmp(current->str, "<<") == 0)
			handle_single_heredoc(&current, temp_filenames, temp_file_count);
		else
			current = current->next;
	}
	while (i < *temp_file_count)
	{
		temp_fd = open((*temp_filenames)[i], O_RDONLY);
		if (temp_fd == -1)
		{
			perror("minishell: cannot open temporary file for reading\n");
			continue ;
		}
		if (dup2(temp_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: heredoc input redirection\n");
			close(temp_fd);
			continue ;
		}
		close(temp_fd);
		i++;
	}
}

void	execute_command_with_heredoc(t_command *cmd, t_cmd *context)
{
	char	**temp_filenames;
	int		temp_file_count;
	t_lexer	*current;
	t_lexer	*temp;
	int		i;
          t_lexer   *prev = NULL;

	temp_filenames = NULL;
	temp_file_count = 0;
	handle_heredocs(cmd, &temp_filenames, &temp_file_count);
	current = cmd->tokens;
	while (current && current->next)
	{
		if (current->token == TOKEN_HEREDOC)
		{
			temp = current->next->next;
                              if(prev)
                                        prev->next = temp;
			current->next->next = NULL;
			free_lexer(current);
                              if(prev)
                                        cmd->tokens = prev;
                              else
                                        cmd->tokens = temp;
                              current = cmd->tokens;
                              continue;
		}
                    prev = current;
		current = current->next;
	}
	if (cmd->tokens)
          {
                    handle_command(cmd,context,1);
		// execution(cmd, context);

          }
                    
         
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
