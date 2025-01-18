/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainFunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:07:42 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/17 14:09:16 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Converts environment list to an array of "key=value" strings
*/

char	**env_list_to_array(t_cmd *cmd)
{
	int		count;
	t_env	*tmp;
	char	**envp_array;
	int		i;

	count = 0;
	tmp = cmd->envp;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!envp_array)
		return (NULL);
	tmp = cmd->envp;
	i = 0;
	while (i < count)
	{
		envp_array[i] = ft_strjoin_three(tmp->key, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp_array[count] = NULL;
	return (envp_array);
}

/* Function to create the full path by joining directory and command */
char	*create_full_path(char *directory, char *command)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(directory, "/");
	full_path = ft_strjoin(temp_path, command);
	free(temp_path);
	return (full_path);
}

char	*generate_prompt(t_cmd *context)
{
	char	*pwd;
	char	*home;
	char	*prompt;
	char	*relative_path;

	pwd = get_env_var(context->envp, "PWD");
	home = get_env_var(context->envp, "HOME");
	if (!pwd || !home)
		prompt = ft_strdup(BLUE "Mini" RED "shell>>  " GREEN);
	else
	{
		relative_path = get_relative_path(pwd, home);
		if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
			prompt = ft_strjoin_three(BLUE "Mini" RED "shell>>" CYAN "~",
					relative_path, "$  " GREEN);
		else
			prompt = ft_strjoin_three(BLUE "Mini" RED "shell>>" CYAN,
					pwd, "$  " GREEN);
	}
	return (prompt);
}

void	initialize_context(t_cmd *context, char **envp)
{
	char	*shlvl_str;
	char	*new_shlvl_str;

	context->envp = my_env(envp);
	context->last_exit_status = 0;
	if (!context->envp)
	{
		fprintf(stderr, "Error: Failed to initialize environment.\n");
		exit(1);
	}
	shlvl_str = get_env_var(context->envp, "SHLVL");
	new_shlvl_str = ft_itoa(ft_atoi(shlvl_str) + 1);
	if (!new_shlvl_str)
	{
		fprintf(stderr, "Error: Failed to update SHLVL.\n");
		free_my_env(context->envp);
		exit(1);
	}
	set_env_var(context->envp, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
	print_welcome_message();
}

void	process_input(char *line, t_cmd *context)
{
	char		*trimmed_line;
	t_lexer		*token;
	t_command	*commands;
	int			flage;

	flage = 0;
	if (line[0] == '\0')
		return (free(line));
	trimmed_line = ft_strtrim(line, " \t\f");
	free(line);
	if (!trimmed_line || trimmed_line[0] == '\0')
		return (free(trimmed_line));
	if (*trimmed_line)
		add_history(trimmed_line);
	token = lexer(trimmed_line, context);
	if (!token)
		return ;
	if (contains_pipes(token))
		flage = 1;
	commands = parser(token);
	handle_command(commands, context, flage);
	free(trimmed_line);
	free_lexer(token);
	free_command_list(commands);
}
