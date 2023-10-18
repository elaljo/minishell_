/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 20:20:05 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_p0(t_init *x, t_data *data, t_cmd *cmds)
{
	if (parsing_errors(x->input_string) == 2 || \
	successive_redir(x->input_string) == 2)
		data->new_st = 258;
	else
	{
		x->splitted_cmds = split(x->input_string);
		free(x->input_string);
		removing_spaces(x->splitted_cmds);
		x->splitted = rm_empty(x->splitted_cmds);
		cmds = get_cmds(x->splitted, data);
		if (cmd_pipe(x->splitted, cmds) == 2 || \
			redir_errors(cmds) == 2)
			data->new_st = 258;
		else
		{
			ft_str_free(x->splitted);
			expand_all(cmds, data);
			if (data->new_st != 2)
				executer(cmds, data);
			free_cmds(cmds);
		}
	}
}

int	main(int ac, char *av[], char **env)
{
	t_cmd	*cmds;
	t_data	data;
	t_init	x;

	if (ac != 1 || !av)
		return (0);
	rl_initialize();
	init_data_structs(&data);
	copy_env(&data, env);
	signal_part();
	while (1)
	{
		set_exit_status(&data);
		x.input_string = readline("🌙❓➜ ");
		add_history(x.input_string);
		ctrl_d(x.input_string);
		if (only_spaces(x.input_string) == 0)
		{
			free(x.input_string);
			continue ;
		}
		main_p0(&x, &data, cmds);
		system("leaks -q minishell"); //dont forget to remove this line..
	}
	return (EXIT_SUCCESS);
}
