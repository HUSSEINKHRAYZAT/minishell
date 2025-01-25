/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:48:00 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/24 20:22:50 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handlepipetoken(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	handle_pipe(lexer, line, i);
	ctx->flag_space = 1;
}

void	handlewordtoken(t_lexer **lexer, char *line, int *i, t_context *ctx)
{
	handle_word(lexer, line, i, ctx->flag_space);
	ctx->flag_space = 0;
}
