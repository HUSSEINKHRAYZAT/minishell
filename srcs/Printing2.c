/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:09:22 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 16:09:55 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	print_array(char **cmd)
{
	int	i;

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
