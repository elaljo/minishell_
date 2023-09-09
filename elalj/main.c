/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:09:36 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 15:09:37 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_structs(t_data *data, t_cmd *cmd)
{
	data->c_env = NULL;
	data->len_env = 0;
	data->key_env = NULL;
	cmd->cmd = NULL;
	cmd->cmd_args = NULL;
	cmd->path = NULL;
	cmd->split_cmd = NULL;
}

int	main(int ac, char *av[], char **env)
{
	t_data	data;
	t_cmd	cmd;
	char	*line;
	char	**sline;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	init_data_structs(&data, &cmd);
	copy_env(&data, env);
	data.key_env = ft_calloc(data.len_env + 1, sizeof(char *));
	while (1)
	{
		line = readline("minishell: ");
		if (ft_strcmp(line, "") == 0)
			continue ;
		sline = ft_split(line);
		add_history(line);
		if (is_builtin(sline) == 1)
			execute_builtin(sline, &data);
		else
			found_cmd(sline, &cmd, env, 0);
		free(line);
		ft_str_free(sline);
	}
	return (EXIT_SUCCESS);
}
