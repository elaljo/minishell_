/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/17 17:27:37 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **env)
{
	t_cmd	*cmds;
	// t_cmd	*cmds_expanded;
	t_data data;
	char	*input_string;
	char	**splitted_cmds;
	
	if (ac != 1 && !av)
		return (0);
	rl_initialize();
	init_data_structs(&data);
	copy_env(&data, env);
	data.key_env = ft_calloc(data.len_env + 1, sizeof(char *));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	// if (signal(SIGINT, signal_handler) == SIG_ERR)
	// 	perror("signal");
	while (1)
	{
		input_string = readline("minishell-0.5$ ");
		add_history(input_string);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
		// if (signal(SIGINT, signal_handler) == SIG_ERR)
		// perror("signal");
		if (!input_string)
		{
			printf("exit\n");
			//need to free all things..
			exit(0);
		}
		if (only_spaces(input_string) == 0)
			continue ;
		splitted_cmds = split(input_string);
		cmds = get_cmds(splitted_cmds);
		expand_all(cmds);
		//printf("---------- %s\n", cmds_expanded[0].args[0]);
		// int i = 0;
		// while (i < cmds_expanded->nbr)
		// {
		// 	printf("command (%d)= %s\n",i,  cmds_expanded[i].cmd);
		// 	i++;
		// }
		// i = 0;
		// while (i < cmds_expanded->nbr)
		// {
		// 	int j = 0;
		// 	while (cmds_expanded[i].args[j] != NULL)
		// 	{
		// 		printf("commande(%d)arguments(%d)-> %s\n", i, j,cmds_expanded[i].args[j]);
		// 		j++;
		// 	}
		// 	i++;
		// }
		if (is_builtin(cmds) == 1)
			execute_builtin(cmds, &data);
		else
			found_cmd(splitted_cmds, cmds, env, 0);
	}
	free(input_string);
	ft_str_free(splitted_cmds);
	return (EXIT_SUCCESS);
}