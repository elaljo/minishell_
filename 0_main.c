/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:32:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/12 17:19:35 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char *av[], char **env)
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
		if (only_spaces(input_string) == 0)
			continue ;
		if (parsing_errors(input_string) == 2 || successive_redir(input_string) == 2)
			data.new_st = 258;
		else
		{
			splitted_cmds = split(input_string);
			// printf("✅splitting✅\n");
			removing_spaces(splitted_cmds);
			splitted = rm_empty(splitted_cmds);
			cmds = get_cmds(splitted, &data);
			// printf("✅Getting cmds✅\n");
			if (cmd_pipe(splitted, cmds) == 2 || redir_errors(cmds) == 2)
				data.new_st = 258;
			else
			{
				ft_str_free(splitted);
				expand_all(cmds, &data);
				// printf("✅expanding✅\n");
				if (data.new_st != 2)
				{
					if (cmds->redir_nbr != 0 && cmds->argu_nbr == 1)
						execute_redir(cmds, &data);
					else if (cmds->argu_nbr == 1)
					{
						if (cmds[0].argu[0] && is_builtin(cmds[0].argu[0]) == 1 && cmds->argu_nbr == 1)
							execute_builtin(cmds, &data, 0);
						else
							executing_one_cmd(cmds, 0, &data);
					}
					else if (cmds->argu_nbr > 1)
						execute_pipe(cmds, &data);
				}
				free_cmds(cmds);
			}
		}
	}
	free(input_string);
	return (EXIT_SUCCESS);
}








void	ft_trim(char **str, int i)
{
	int start = 0;
	int j = 0;
	char *tmp = ft_strdup(*str);
	// printf("tmp -> (%s)\n", tmp);
	int end = ft_strlen(tmp) - 1;
	
	while (tmp[start] == ' ')
		start++;
	while (tmp[end] == ' ')	
		end--;
	free(str[i]);
	str[i] = ft_calloc(1, end - start + 1 + 1);//dima kadir end - start katn9es lik 1 dkchi lach kanzido o wahd d \0
	while (start < end + 1)
	{
		str[i][j] = tmp[start];
		j++;
		start++;
	}
	str[i][j] = '\0';
	free(tmp);
}

char	**rm_empty(char **tab)
{
	char **tmp = tab_dup(tab);
	ft_str_free(tab);
	int cnt = 0;
	int i = 0;

	while (tmp[i] != NULL)
	{
		if (tmp[i][0] == '\0')
			cnt++;
		i++;
	}
	tab = ft_calloc(1, (i - cnt + 1) * sizeof(char *));
	i = 0;
	cnt = 0;
	while (tmp[cnt] != NULL)
	{
		if (tmp[cnt][0] == 0)
		{
			cnt++;
			continue ;
		}
		tab[i] = ft_strdup(tmp[cnt]);
		// printf("(%s)\n", tab[i]);
		i++;
		cnt++;
	}
	tab[i] = NULL;
	ft_str_free(tmp);
	return (tab);
}

char **tab_dup(char **tab)
{
	int i = 0;
	char **dup;

	while (tab[i] != NULL)
		i++;
	dup = ft_calloc(1, (i + 1) * sizeof(char *));
	i = 0;
	while (tab[i] != NULL)
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	free_cmds(t_cmd *cmds)
{
	int i = 0;
	int j;
	
	while (i < cmds[0].argu_nbr)
	{
		ft_str_free(cmds[i].argu);
		if (cmds[i].redir_nbr != 0)
		{
			j = 0;
			while (j < cmds[i].redir_nbr)
			{
				free(cmds[i].redir[j].eof);
				free(cmds[i].redir[j].redi);
				free(cmds[i].redii[j].eof);
				free(cmds[i].redii[j].redi);
				j++;
			}
			free(cmds[i].redir);
			free(cmds[i].redii);
		}
		free(cmds[i].path);
		i++;
	}
	free(cmds);
}