/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/29 21:49:51 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **env)
{
	t_cmd	*cmds;
	t_data	data;
	char	*input_string;
	char	**splitted_cmds;
	
	if (!env || !*env)
	{
		printf("Aaaaaaa mexiiiiiiiii ltabon dyemak\n");
		return (1);
	}
	(void)av;
	if (ac != 1)
		return (0);
	rl_initialize();
	init_data_structs(&data);
	copy_env(&data, env);
	data.key_env = ft_calloc(data.len_env + 1, sizeof(char *));
	signal_part();
	while (1)
	{
		input_string = readline("🌙❓➜ ");
		// input_string = readline("minishell-0.5$ ");
		add_history(input_string);
		if (!input_string)
		{
			printf("exit\n");
			exit (0);
		}
		parsing_errors(input_string);
		if (only_spaces(input_string) == 0)
			continue ;
		splitted_cmds = split(input_string);
		// printf("✅splitting✅\n");
		removing_spaces(splitted_cmds);
		// printf("✅removing spaces✅\n");
		cmds = get_cmds(splitted_cmds);
		// printf("✅Getting cmds✅\n");
		expand_all(cmds, data);
		// printf("✅expanding✅\n");
		if (cmds->redir_nbr != 0)
			execute_redir(cmds, &data);
		else if (cmds->args_nbr == 1)
		{
			if (is_builtin(cmds[0].args[0]) == 1 && cmds->args_nbr == 1)
				execute_builtin(cmds, &data, 0);
			else
				executing_one_cmd(cmds, 0, &data);
		}
		else
			execute_pipe(cmds, &data);
	}
	free(input_string);
	ft_str_free(splitted_cmds);
	return (EXIT_SUCCESS);
}