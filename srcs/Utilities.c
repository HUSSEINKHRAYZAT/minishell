/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:45:28 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/15 15:48:16 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to check if the given path is a directory
int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", path);
		return (1);
	}
	return (0);
}

int	contains_redirection(t_lexer *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->str, "<") == 0)
			return (1);
		if (ft_strcmp(tokens->str, ">") == 0)
			return (1);
		if (ft_strcmp(tokens->str, ">>") == 0)
			return (1);
		if (ft_strcmp(tokens->str, "<<") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

void	builtin_exit(t_command *cmd)
{
	char	**args;
	int		exit_code;

	args = lexer_to_args(cmd->tokens);
	if (args)
	{
		if (args[1])
		{
			exit_code = atoi(args[1]);
			free_array(args);
			exit(exit_code);
		}
		free_array(args);
	}
	exit(0);
}

/* Function to read input and manage prompt generation */
char	*read_input(t_cmd *context)
{
	char	*line;
	char	*prompt;

	prompt = generate_prompt(context);
	line = readline(prompt);
	free(prompt);
	return (line);
}
