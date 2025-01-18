/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:00:11 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/15 17:51:26 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

char	**allocate_args(int count)
{
	char	**args;

	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	context;

	(void)argc;
	(void)argv;
	initialize_context(&context, envp);
	handle_user_input(&context);
	cleanup(&context);
	return (0);
}
