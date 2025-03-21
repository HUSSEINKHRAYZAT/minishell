/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:45:28 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/03/21 08:51:29 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to check if the given path is a directory
int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && (path_stat.st_mode & S_IFMT) == S_IFDIR)
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
// context->last_exit_status = 0;

void	builtin_exit(t_command *cmd, t_cmd *context)
{
	char	**args;
	int		count;

	args = lexer_to_args(cmd->tokens);
	count = 0;
	while (args && args[count])
		count++;
	if (args)
	{
		if (count >= 3)
		{
			printf("Minishell: exit: too many arguments\n");
			return (free_array(args));
		}
		if (args[1])
		{
			context->last_exit_status = ft_atoi(args[1]);
			free_array(args);
			exit(context->last_exit_status);
		}
		free_array(args);
	}
	exit(context->last_exit_status);
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
