/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handling5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:02:12 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/25 09:14:34 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(t_lexer **lexer, char *line, int *i)
{
	(void)line;
	add_lexer_token(lexer, init_lexer_token(ft_strdup("|"), TOKEN_PIPE,
			NO_QUOTE));
	(*i)++;
}

char	*append_char(char *buffer, char c)
{
	char	*new_buffer;
	size_t	len;

	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	len = ft_strlen(buffer);
	new_buffer = malloc(len + 2);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	ft_memcpy(new_buffer, buffer, len);
	new_buffer[len] = c;
	new_buffer[len + 1] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		joined = ft_strdup(s2);
		free(s2);
		return (joined);
	}
	if (!s2)
	{
		joined = ft_strdup(s1);
		free(s1);
		return (joined);
	}
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*expand_variable(char *line, int *i, t_cmd *ctx)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*expanded;

	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var_name = ft_substr(line, start, *i - start);
	if (!var_name)
		return (ft_strdup(""));
	var_value = get_env_var(ctx->envp, var_name);
	if (var_value)
		expanded = ft_strdup(var_value);
	else
		expanded = ft_strdup("");
	free(var_name);
	return (expanded);
}

char	*handle_dollar_expansion(char *line, int *i, t_cmd *ctx)
{
	char	*expanded;

	expanded = NULL;
	(*i)++;
	if (line[*i] == '$')
		expanded = ft_itoa(ft_getpid());
	else if (line[*i] == '?')
		expanded = ft_itoa(ctx->last_exit_status);
	else if (ft_isalpha(line[*i]) || line[*i] == '_')
		return (expand_variable(line, i, ctx));
	else if (ft_isdigit(line[*i]))
		expanded = ft_strdup("");
	else if (line[*i] == '\"')
	{
		if (ctx->quote_type == NO_QUOTE)
			return (ft_strdup(""));
	}
	else
		return (ft_strdup("$"));
	(*i)++;
	return (expanded);
}
