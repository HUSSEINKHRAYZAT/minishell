/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cleaningfunctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:32:25 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 10:24:41 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function to free the split PATH array */
void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	free_my_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	free_tokens(cmd->tokens);
	if (cmd->redirects)
		free_lexer(cmd->redirects);
	if (cmd->heredoc_delimiters)
		free_heredoc_delimiters(cmd->heredoc_delimiters);
	free(cmd);
}

void	free_sorted_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_array(char **array)
{
	char	**temp;

	if (array)
	{
		temp = array;
		while (*temp)
		{
			free(*temp);
			temp++;
		}
		free(array);
	}
}

// void	free_command(t_command *cmd)
// {
// 	t_lexer	*temp_token;
// 	t_lexer	*next_token;
// 	int		i;

// 	if (!cmd)
// 		return ;
// 	temp_token = cmd->tokens;
// 	while (temp_token)
// 	{
// 		next_token = temp_token->next;
// 		free(temp_token->str);
// 		free(temp_token);
// 		temp_token = next_token;
// 	}
// 	if (cmd->redirects)
// 		free_lexer(cmd->redirects);
// 	if (cmd->heredoc_delimiters)
// 	{
// 		i = 0;
// 		while (cmd->heredoc_delimiters[i])
// 		{
// 			free(cmd->heredoc_delimiters[i]);
// 			i++;
// 		}
// 		free(cmd->heredoc_delimiters);
// 	}
// 	free(cmd);
// }