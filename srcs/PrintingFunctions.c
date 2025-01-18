/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintingFunctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:57 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/18 13:56:15 by hkhrayza         ###   ########.fr       */
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
	for (t_command *cmd = cmd_list; cmd; cmd = cmd->next)
	{
		printf("Command:\n");
		for (t_lexer *token = cmd->tokens; token; token = token->next)
		{
			printf("  Token: %s, Type: %d, Quote: %d\n", token->str,
				token->token, token->quote_type);
		}
		if (cmd->next)
			printf("--- Next Command ---\n");
	}
}

void	print_parser(t_command *cmd_list)
{
	t_lexer	*token;

	while (cmd_list)
	{
		if (cmd_list->tokens)
		{
			token = cmd_list->tokens;
			while (token)
			{
				printf("  Token: %s\n", token->str);
				token = token->next;
			}
		}
		cmd_list = cmd_list->next;
	}
}

// // Function to print a t_lexer structure
void	print_lexerr(t_lexer *lexer)
{
	printf("Lexer Structure:\n");
	while (lexer)
	{
		printf("  str: %s\n", lexer->str);
		printf("  i: %d\n", lexer->i);
		printf("  space: %d\n", lexer->space);
		printf("  token: %d\n", lexer->token);
		printf("  quote_type: %d\n", lexer->quote_type);
		printf("  next: %p\n", (void *)lexer->next);
		lexer = lexer->next;
		if (lexer)
			printf("\n");
	}
}

// Function to print a t_command structure
void	print_command(t_command *command)
{
	printf("Command Structure:\n");
	while (command)
	{
		printf("  Tokens: %s\n", command->tokens->str);
		command = command->next;
		if (command)
			printf("\n");
	}
}
void	print_Array(char **cmd)
{
	int i;

	if (cmd == NULL)
	{
		printf("Array is NULL.\n");
		return ;
	}
	i = 0;
	while (cmd[i] != NULL)
	{
		printf("cmd : %s\n", cmd[i]);
		i++;
	}
}