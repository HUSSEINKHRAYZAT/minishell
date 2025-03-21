/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GettingFunctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:44:00 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 10:25:35 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_heredoc_delimiter(t_lexer *token)
{
	while (token)
	{
		if (ft_strcmp(token->str, "<<") == 0 && token->next)
		{
			return (token->next->str);
		}
		token = token->next;
	}
	return (NULL);
}

char	*get_append_file(t_lexer *token)
{
	while (token)
	{
		if (ft_strcmp(token->str, ">>") == 0 && token->next)
		{
			if (ft_strcmp(token->next->str, ">>") != 0
				&& ft_strcmp(token->next->str, ">") != 0
				&& ft_strcmp(token->next->str, "<") != 0)
				return (token->next->str);
		}
		token = token->next;
	}
	return (NULL);
}

char	*get_output_file(t_lexer *token)
{
	while (token)
	{
		if (ft_strcmp(token->str, ">") == 0 && token->next)
		{
			return (token->next->str);
		}
		token = token->next;
	}
	return (NULL);
}

char	*get_input_file(t_lexer *token)
{
	while (token)
	{
		if (ft_strcmp(token->str, "<") == 0 && token->next)
		{
			return (token->next->str);
		}
		token = token->next;
	}
	return (NULL);
}

/* Function to get the PATH environment variable from the t_env linked list */
char	*get_path_from_env(t_env *envp)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
