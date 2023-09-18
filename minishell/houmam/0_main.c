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

int main()
{
	char	*input_string;
	char	**splitted_cmds;
	t_cmd	*cmds;
	t_cmd	*cmds_expanded;
	
	rl_initialize();
	while (1)
	{
		input_string = readline("minishell-0.5$ ");
		add_history(input_string);
		if (!*input_string)
			continue ;
		if (only_spaces(input_string) == 0)
			continue ;
		if (ft_strcmp(input_string, "exit") == 0)
			exit(0);
		splitted_cmds = split(input_string);
		cmds = get_cmds(splitted_cmds);
		printf("+++ %s +++\n", cmds[0].args[0]);
    	printf("+++ %s +++\n", cmds[0].args[1]);
		expand_all(cmds);
		// quotes_split(input_string);
	}
}