/* Main function to handle the user input loop */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:50:09 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/04 21:00:00 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** is_invalid_pipe_sequence
** Returns 1 if the first token is a pipe or if two consecutive pipes are found,
** otherwise returns 0.
*/
int	is_invalid_pipe_sequence(t_lexer *lexer)
{
	t_lexer	*current;

	if (lexer && lexer->token == TOKEN_PIPE)
		return (1);
	current = lexer;
	while (current && current->next)
	{
		if (current->token == TOKEN_PIPE && current->next->token == TOKEN_PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

static char	*append_input_to_buffer(char *buffer, t_cmd *context)
{
	char	*line;
	char	*temp;
	char	*trim;

	trim = ft_strtrim(buffer, "\t\f ");
	if (ft_strlen(buffer) == 0 || *trim == '\0')
	{
		free(trim);
		line = read_input(context);
	}
	else
	{
		free(trim);
		line = readline("> ");
	}
	if (!line)
	{
		if (ft_strlen(buffer) > 0)
		{
			printf("minishell: syntax error: unexpected end of file\n");
			free(buffer);
			return (NULL);
		}
		ft_putstr_fd("exit\n", STDERR);
		free(buffer);
		return (NULL);
	}
	temp = ft_strjoin(buffer, line);
	free(buffer);
	free(line);
	return (temp);
}

/*
** check_command_complete
** Tokenizes the accumulated buffer and checks whether the command is complete.
** Returns:
**   1 if the command is complete (last token is not a pipe),
**   0 if the command is incomplete,
**  -1 (or -2) if tokenization failed due to unmatched quotes or invalid pipes.
*/
static int	check_command_complete(char *buffer, t_cmd *context)
{
	t_lexer	*lexer_tokens;
	t_lexer	*last;
	int		complete;

	lexer_tokens = lexer(buffer, context);
	complete = 1;
	if (!lexer_tokens)
	{
		if (context->exp == 0)
			return (-1);
		return (0);
	}
	if (is_invalid_pipe_sequence(lexer_tokens))
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		context->last_exit_status = 2;
		free_lexer(lexer_tokens);
		return (-2);
	}
	last = lexer_tokens;
	while (last->next)
		last = last->next;
	if (last && last->token == TOKEN_PIPE)
		complete = 0;
	free_lexer(lexer_tokens);
	return (complete);
}

/*
** read_complete_code
** Reads lines from input until a complete command is accumulated.
** A command is considered complete when tokenization succeeds and the last token
** is not a pipe. If tokenization fails (due to unmatched quotes, etc.),
	the buffer
	if (!buffer)
		return (NULL);
** is reset and the loop continues.
*/
char	*read_complete_code(t_cmd *context)
{
	char	*buffer;
	int		comp;

	buffer = ft_strdup("");
	context->exp = 1;
	while (1)
	{
		buffer = append_input_to_buffer(buffer, context);
		if (!buffer)
			return (NULL);
		comp = check_command_complete(buffer, context);
		if (comp < 0)
		{
			context->exp = 1;
			free(buffer);
			buffer = ft_strdup("");
			if (!buffer)
				return (NULL);
			continue ;
		}
		if (comp == 1)
			break ;
	}
	return (buffer);
}

void	handle_redirection_token(t_lexer **lexer, char *line, int *i,
		t_cmd *ctx)
{
	int	check_index;

	check_index = *i - 1;
	if (is_inside_quotes(line, check_index))
		return (handle_word(lexer, line, i, ctx));
	if (line[*i] == '>' && line[*i + 1] == '>')
		add_redirection_token(lexer, line, i, TOKEN_APPEND);
	else if (line[*i] == '>')
		add_redirection_token(lexer, line, i, TOKEN_REDIRECT_OUT);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		add_redirection_token(lexer, line, i, TOKEN_HEREDOC);
	else if (line[*i] == '<')
		add_redirection_token(lexer, line, i, TOKEN_REDIRECT_IN);
}

// void	handle_redirection_token(t_lexer **lexer, char *line, int *i,
// 		t_cmd *ctx)
// {
// 	int	check_index;

// 	check_index = *i - 1;
// 	if (is_inside_quotes(line, check_index))
// 	{
// 		handle_word(lexer, line, i, ctx);
// 		return ;
// 	}
// 	if (line[*i] == '>' && line[*i + 1] == '>')
// 	{
// 		add_lexer_token(lexer, init_lexer_token(ft_strdup(">>"), TOKEN_APPEND,
// 				NO_QUOTE));
// 		(*i) += 2;
// 	}
// 	else if (line[*i] == '>')
// 	{
// 		add_lexer_token(lexer, init_lexer_token(ft_strdup(">"),
// 				TOKEN_REDIRECT_OUT, NO_QUOTE));
// 		(*i)++;
// 	}
// 	else if (line[*i] == '<' && line[*i + 1] == '<')
// 	{
// 		add_lexer_token(lexer, init_lexer_token(ft_strdup("<<"), TOKEN_HEREDOC,
// 				NO_QUOTE));
// 		(*i) += 2;
// 	}
// 	else if (line[*i] == '<')
// 	{
// 		add_lexer_token(lexer, init_lexer_token(ft_strdup("<"),
// 				TOKEN_REDIRECT_IN, NO_QUOTE));
// 		(*i)++;
// 	}
// }
