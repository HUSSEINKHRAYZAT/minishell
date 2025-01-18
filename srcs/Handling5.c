/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:02:12 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 11:06:22 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_dollar(t_lexer **lexer, char *line, int *i, t_cmd *cmd)
{
	(*i)++;
	if (line[*i] == '$')
		handle_dollar_pid(lexer, i);
	else if (line[*i] == '?')
		handle_dollar_exit_status(lexer, i, cmd);
	else if (ft_isalpha(line[*i]) || line[*i] == '_')
		handle_dollar_variable(lexer, line, i, cmd);
	else
		add_lexer_token(lexer, init_lexer_token(ft_strdup("$"), TOKEN_WORD,
				NO_QUOTE));
}

void	handle_dollar_pid(t_lexer **lexer, int *i)
{
	add_lexer_token(lexer, init_lexer_token(ft_itoa(ft_getpid()), TOKEN_WORD,
			NO_QUOTE));
	(*i)++;
}

void	handle_dollar_exit_status(t_lexer **lexer, int *i, t_cmd *cmd)
{
	add_lexer_token(lexer, init_lexer_token(ft_itoa(cmd->last_exit_status),
			TOKEN_WORD, NO_QUOTE));
	(*i)++;
}

void	handle_dollar_variable(t_lexer **lexer, char *line, int *i, t_cmd *cmd)
{
	char	*var_start;
	char	*var_name;
	char	*var_value;

	var_start = &line[*i];
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var_name = ft_substr(var_start, 0, &line[*i] - var_start);
	var_value = get_env_var(cmd->envp, var_name);
	if (var_value)
		add_lexer_token(lexer, init_lexer_token(ft_strdup(var_value),
				TOKEN_WORD, NO_QUOTE));
	else
		add_lexer_token(lexer, init_lexer_token(ft_strdup(""), TOKEN_WORD,
				NO_QUOTE));
	free(var_name);
}
