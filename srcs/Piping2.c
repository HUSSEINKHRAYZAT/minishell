/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Piping2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:36:26 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 12:50:30 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Execute a single command */
char	**create_argv(t_lexer *tokens, int *argc)
{
	char	**argv;
	int		i;
	t_lexer	*token;

	*argc = 0;
	token = tokens;
	while (token)
	{
		(*argc)++;
		token = token->next;
	}
	argv = malloc((*argc + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	token = tokens;
	while (token)
	{
		argv[i++] = token->str;
		token = token->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	handle_command_redirections(t_command *cmd, t_cmd *context, char **argv)
{
	if (contains_heredoc(cmd->tokens))
	{
		execute_command_with_heredoc(cmd, context);
		free(argv);
		return (1);
	}
	if (handle_redirections(cmd, context) != 0)
	{
		perror("Error handling redirections");
		free(argv);
		return (-1);
	}
	return (0);
}

void	execute_command(t_command *cmd, t_cmd *context)
{
	char	**argv;
	int		argc;
	int		ret;

	if (!cmd || !cmd->tokens)
		return ;
	argv = create_argv(cmd->tokens, &argc);
	if (!argv)
		return ;
	while (contains_redirection(cmd->tokens))
	{
		ret = handle_command_redirections(cmd, context, argv);
		if (ret != 0)
			return ;
	}
	if (!contains_heredoc(cmd->tokens) && execution(cmd, context) == -1)
		perror("Command execution failed");
	free(argv);
}
