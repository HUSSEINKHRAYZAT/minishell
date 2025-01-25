/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintingFunctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:57 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 16:10:03 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Prints all environment variables, sorted
void	print_sorted_env_vars(t_env *envp)
{
	t_env	*sorted_envp;
	t_env	*current;

	sorted_envp = sort_env(envp);
	current = sorted_envp;
	while (current)
	{
		if (current->hidden == 1)
			printf("declare -x %s\n", current->key);
		else
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
	free_sorted_env(sorted_envp);
}

void	print_welcome_message(void)
{
	printf("\n");
	printf("%s        ███╗   ███╗ ██╗ ███╗   ██╗ ██╗\n", RED);
	printf("%s        ████╗ ████║ ██║ ████╗  ██║ ██║\n", RED);
	printf("%s        ██╔████╔██║ ██║ ██╔██╗ ██║ ██║\n", RED);
	printf("%s        ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║\n", RED);
	printf("%s        ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║\n", RED);
	printf("%s        ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝\n", RED);
	printf("%s        SHELL                              \n", BYELLOW);
	printf("%s        BY HUSSEIN KHRAYZAT AND KAMEL ABBASS\n\n", BGREEN);
}

// Function to print lexer tokens
void	print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("Token: %s, Type: %d\n", lexer->str, lexer->token);
		lexer = lexer->next;
	}
}

void	print_commands(t_command *cmd_list)
{
	t_command	*cmd;
	t_lexer		*token;

	cmd = cmd_list;
	token = cmd->tokens;
	while (cmd)
	{
		printf("Command:\n");
		while (token)
		{
			printf("  Token: %s, Type: %d, Quote: %d\n", token->str,
				token->token, token->quote_type);
			token = token->next;
		}
		if (cmd->next)
			printf("--- Next Command ---\n");
		cmd = cmd->next;
	}
}
