/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/30 01:15:58 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **env)
{
	t_cmd	*cmds;
	t_data	data;
	char	*input_string;
	char	**splitted_cmds;
	
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
		printf("✅splitting✅\n");
		removing_spaces(splitted_cmds);
		printf("✅removing spaces✅\n");
		cmds = get_cmds(splitted_cmds);
		// printf("✅Getting cmds✅\n");
		expand_all(cmds, data);
		printf("✅expanding✅\n");
		if (cmds->args_nbr == 1)
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

void	ft_trim(char **str)
{
	int start = 0;
	int i = 0;
	int end = ft_strlen(*str) - 1;
	char *tmp;
	while (*str[start] == ' ')
		start++;
	while (*str[end] == ' ')
		end++;
	tmp = ft_strdup(*str);
	free(*str);
	printf("ana hna\n");
	*str = malloc(end - start + 1 + 1);//dima kadir end - start katn9es lik 1 dkchi lach kanzido o wahd d \0
	while (start < end + 1)
	{
		*str[i] = tmp[start];
		i++;
		start++;
	}
	*str[i] = '\0';
	free(tmp);
}