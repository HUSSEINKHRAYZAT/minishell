/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:46:06 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/04 11:48:03 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_env_var(t_env *envp, char *key, char *value, int hidden)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->hidden = hidden;
	new_var->next = envp->next;
	envp->next = new_var;
}

void	set_env_var(t_env *envp, char *key, char *value)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			current->hidden = 0;
			return ;
		}
		current = current->next;
	}
	add_env_var(envp, key, value, 0);
}

void	set_env_var_hidden(t_env *envp, char *key, char *value, int hidden)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
				current->hidden = 0;
			}
			else
				current->hidden = hidden;
			return ;
		}
		current = current->next;
	}
	add_env_var(envp, key, value, hidden);
}

// Creates a new environment node by splitting
//  the envp string into key and value
t_env	*create_env_node(char *env_var)
{
	t_env	*new_node;
	char	*equals_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equals_sign = ft_strchr(env_var, '=');
	if (equals_sign)
	{
		new_node->key = ft_substr(env_var, 0, equals_sign - env_var);
		new_node->value = ft_strdup(equals_sign + 1);
	}
	else
	{
		new_node->key = ft_strdup(env_var);
		new_node->value = NULL;
	}
	new_node->hidden = 0;
	new_node->next = NULL;
	return (new_node);
}

// Initializes the environment linked list
t_env	*initialize_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_my_env(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
