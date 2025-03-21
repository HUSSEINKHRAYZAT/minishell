/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:47:35 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/04 11:48:50 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Main function to construct the environment linked list
t_env	*my_env(char **envp)
{
	return (initialize_env_list(envp));
}

void	remove_env_var(char *key, t_env **envp)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
