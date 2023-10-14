/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/13 03:42:08 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_cmd	*cmds;
	t_data	data;
	char	*input_string;
	char	**splitted_cmds;
	char	**splitted;

	(void)av;
	if (ac != 1)
		return (0);
	rl_initialize();
	init_data_structs(&data);
	copy_env(&data, env);
	signal_part();
	while (1)
	{
		set_exit_status(&data);
		input_string = readline("🌙❓➜ ");
		add_history(input_string);
		ctrl_d(&data, input_string);
		if (only_spaces(input_string) == 0)
			continue ;
		if (parsing_errors(input_string) == 2 || \
			successive_redir(input_string) == 2)
			data.new_st = 258;
		else
		{
			splitted_cmds = split(input_string);
			free(input_string);
			removing_spaces(splitted_cmds);
			splitted = rm_empty(splitted_cmds);
			cmds = get_cmds(splitted, &data);
			if (cmd_pipe(splitted, cmds) == 2 || \
				redir_errors(cmds) == 2)
				data.new_st = 258;
			else
			{
				ft_str_free(splitted);
				expand_all(cmds, &data);
				if (data.new_st != 2)
					executer(cmds, &data);
				free_cmds(cmds);
			}
		}
	}
	return (EXIT_SUCCESS);
}
