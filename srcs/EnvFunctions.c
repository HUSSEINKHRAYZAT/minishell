/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnvFunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:47:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/04 11:48:56 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_sorted_env(t_env **sorted_env, char *key,
char *value, int hidden)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->hidden = hidden;
	new_node->next = *sorted_env;
	*sorted_env = new_node;
}

void	add_env_to_sorted_list(t_env **sorted, t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current != NULL)
	{
		add_to_sorted_env(sorted, current->key,
			current->value, current->hidden);
		current = current->next;
	}
}

void	swap_env_nodes(t_env *current)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_hidden;

	tmp_key = current->key;
	tmp_value = current->value;
	tmp_hidden = current->hidden;
	current->key = current->next->key;
	current->value = current->next->value;
	current->hidden = current->next->hidden;
	current->next->key = tmp_key;
	current->next->value = tmp_value;
	current->next->hidden = tmp_hidden;
}

t_env	*bubble_sort_env(t_env *sorted)
{
	int		swapped;
	t_env	*current;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = sorted;
		while (current != NULL && current->next != NULL)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap_env_nodes(current);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (sorted);
}

t_env	*sort_env(t_env *envp)
{
	t_env	*sorted;

	sorted = NULL;
	add_env_to_sorted_list(&sorted, envp);
	sorted = bubble_sort_env(sorted);
	return (sorted);
}
