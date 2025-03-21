/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:10:46 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/02/22 11:07:07 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_hervar(char *line, size_t start, size_t len, t_cmd *context)
{
	char	*var_name;
	char	*env_value;
	char	*new_line;

	var_name = ft_substr(line, start + 1, len - 1);
	env_value = get_env_var(context->envp, var_name);
	free(var_name);
	if (env_value)
	{
		var_name = ft_strndup(line, start);
		new_line = ft_strjoin(var_name, env_value);
		free(var_name);
		var_name = ft_strdup(new_line);
		free(new_line);
		new_line = ft_strjoin(var_name, line + start + len);
		free(var_name);
		free(line);
		return (new_line);
	}
	return (line);
}

char	*expand_variables(char *line, t_cmd *context)
{
	char	*expanded_line;
	char	*start;
	char	*end;

	expanded_line = ft_strdup(line);
	start = ft_strchr(expanded_line, '$');
	while (start)
	{
		end = start + 1;
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
		expanded_line = expand_hervar(expanded_line, start - expanded_line, end
				- start, context);
		start = ft_strchr(expanded_line, '$');
	}
	return (expanded_line);
}

int	handle_heredoc_line(int temp_fd, char *line, char *delimiter,
		t_cmd *context)
{
	char	*expanded_line;

	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	expanded_line = expand_variables(line, context);
	if (write(temp_fd, expanded_line, ft_strlen(expanded_line)) == -1
		|| write(temp_fd, "\n", 1) == -1)
	{
		free(expanded_line);
		free(line);
		return (0);
	}
	free(expanded_line);
	free(line);
	return (1);
}

int	process_heredoc(int temp_fd, char *delimiter, t_cmd *context)
{
	char	*line;

	init_heredoc_signals();
	while (1)
	{
		if (!g_sig.g_heredoc_interrupted)
			line = readline("heredoc> ");
		if (g_sig.g_heredoc_interrupted == 1)
		{
			if (line)
				free(line);
			sig_init();
			return (0);
		}
		if (!line)
		{
			printf("minishell-warning:here-doc");
			printf("terminated by end-of-file(wanted'%s')\n", delimiter);
			break ;
		}
		if (!handle_heredoc_line(temp_fd, line, delimiter, context))
			break ;
	}
	sig_init();
	return (1);
}
