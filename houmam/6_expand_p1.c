/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:46 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/09 16:27:04 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quoted(char *str)
{
	int len = ft_strlen(str) - 1;
	if (str[0] == '"' && str[len] == '"')
		return (1);
	return (0);
}
void	handle_quoted(char *str)
{
	int i;
	int j;
	int len;
	char *tmp;

	while (check_quoted(str) != 0)
	{
		tmp = ft_strdup(str);
		free(str);
		len = ft_strlen(tmp);
		str = malloc((len - 1) * sizeof(char));
		i = 1;
		j = 0;
		while (i < len - 1)
		{
			str[j] = tmp[i];
			i++;
			j++;
		}
		str[j] = '\0';
	}
}

t_cmd	*expandables(t_cmd *cmds)
{
	int i;
	int j;
	char *tmp;
	
	i = 0;
	while (i < cmds->nbr)
	{
		if (check_quoted(cmds[i].cmd) == 1)
		{
			printf("99999\n\n\n\n");
			handle_quoted(cmds[i].cmd);
			printf("handle_quoted ******* %s\n", cmds[i].cmd);
		}
		tmp = ft_strdup(cmds[i].cmd);
		free(cmds[i].cmd);
		cmds[i].cmd = ft_strdup(expand_variables(tmp));
		free(tmp);
		printf("-> %s *\n", cmds[i].cmd);
		i++;
	}
	i = 0;
	while (i < cmds->nbr)
	{
		j = 0;
		while (cmds[i].args[j] != NULL)
		{
			if (check_quoted(cmds[i].args[j]) == 1)
				handle_quoted(cmds[i].args[j]);
			tmp = ft_strdup(cmds[i].args[j]);
			free(cmds[i].args[j]);
			cmds[i].args[j] = ft_strdup(expand_variables(tmp));
			free(tmp);
			expand_variables(cmds[i].args[j]);
			printf("----> %s **\n", cmds[i].args[j]);
			j++;
		}
		i++;
	}
	return (cmds);
}

// int main()
// {
// 	rl_initialize();
// 	char *str[] = readline("---, $ ");
// 	expandables()
// }
