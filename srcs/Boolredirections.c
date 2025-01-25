/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boolredirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:59:42 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/20 17:04:04 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_output_redirection(t_lexer *current)
{
	return (!ft_strcmp(current->str, ">"));
}

int	is_append_redirection(t_lexer *current)
{
	return (!ft_strcmp(current->str, ">>"));
}

int	is_input_redirection(t_lexer *current)
{
	return (!ft_strcmp(current->str, "<"));
}

int	herdoo(t_command *cmd)
{
	(void)cmd;
	return (0);
}

int	is_herdoc_redirection(t_lexer *current)
{
	return (!ft_strcmp(current->str, "<<"));
}
