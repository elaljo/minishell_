/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/09 21:12:19 by hait-sal         ###   ########.fr       */
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
	data.new_st = 0;
	while (1)
	{
		data.old_st = data.new_st;
		data.new_st = 0;
		input_string = readline("🌙❓➜ ");
		// input_string = readline("minishell-0.5$ ");
		add_history(input_string);
		if (!input_string)
		{
			printf("exit\n");
			exit (0);
		}
		// parsing_errors(input_string);
		// printf("✅parsing errors✅\n");
		// successive_redir(input_string);
		// printf("✅successive redir✅\n");
		// printf("Ana hna\n");
		if (only_spaces(input_string) == 0)
		{
			free(input_string);
			continue ;
		}
		if (parsing_errors(input_string) == 2 || successive_redir(input_string) == 2)
			data.new_st = 258;
		else
		{
			splitted_cmds = split(input_string);
			// printf("✅splitting✅\n");
			removing_spaces(splitted_cmds);
			// printf("✅removing spaces✅\n");
			cmds = get_cmds(splitted_cmds, &data);
			ft_str_free(splitted_cmds);
			// printf("✅Getting cmds✅\n");
			if (redir_errors(cmds) == 2)
				data.new_st = 258;
			else
			{
				// printf("✅tedir errors✅\n");
				expand_all(cmds, &data);
				// printf("✅expanding✅\n");
				if (data.new_st != 2)
				{
					if (cmds->redir_nbr != 0 && cmds->args_nbr == 1)
						execute_redir(cmds, &data);
					else if (cmds->args_nbr == 1)
					{
						int i = 0;
						while (cmds[0].args[i] && cmds[0].args[i][0] == '\0')
							i++;
						if (cmds[0].args[i] && is_builtin(cmds[0].args[i]) == 1 && cmds->args_nbr == 1)
							execute_builtin(cmds, &data, 0);
						else
							executing_one_cmd(cmds, 0, &data, i);
					}
					else if (cmds->args_nbr > 1)
						execute_pipe(cmds, &data);
				}
			}
			
		}
		free_cmds(cmds);
	}
	return (EXIT_SUCCESS);
}

void	ft_trim(char **str, int i)
{
	int start = 0;
	int j = 0;
	int end = ft_strlen(str[i]) - 1;
	char *tmp = ft_strdup(str[i]);
	
	while (tmp[start] == ' ')
		start++;
	while (tmp[end] == ' ')	
		end--;
	free(str[i]);
	str[i] = malloc(end - start + 1 + 1);//dima kadir end - start katn9es lik 1 dkchi lach kanzido o wahd d \0
	while (start < end + 1)
	{
		str[i][j] = tmp[start];
		j++;
		start++;
	}
	str[i][j] = '\0';
	// printf("test --> %s\n", str[i]);
	free(tmp);
}