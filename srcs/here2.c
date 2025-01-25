/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:20:53 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/24 21:51:39 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_heredoc_input(int temp_fd, char *buffer, char *delimiter)
{
	if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
		&& buffer[strlen(delimiter)] == '\n')
		return ;
	if ((ft_strchr(buffer, '$') || ft_strchr(buffer, '\"'))
		&& !ft_strchr(buffer, '\''))
	{
		handle_env_variable(temp_fd, buffer);
		return ;
	}
	if (write(temp_fd, buffer, strlen(buffer)) == -1)
		perror("minishell: write to temporary file\n");
}

void	handle_env_variable(int temp_fd, char *buffer)
{
	char	*variable_name;
	char	*newline_pos;
	char	*env_value;

	if (ft_strchr(buffer, '\"'))
	{
		variable_name = ft_strchr(buffer, '$') + 1;
		newline_pos = ft_strchr(variable_name, '\"');
	}
	else if (ft_strchr(buffer, '$'))
	{
		variable_name = ft_strchr(buffer, '$') + 1;
		newline_pos = ft_strchr(variable_name, '\n');
	}
	if (newline_pos)
		*newline_pos = '\0';
	env_value = getenv(variable_name);
	if (env_value)
	{
		if (write(temp_fd, env_value, ft_strlen(env_value)) == -1)
			perror("minishell: write to temporary file\n");
		write(temp_fd, "\n", 1);
	}
}
