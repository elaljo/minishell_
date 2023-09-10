/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:05:29 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/10 18:08:03 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_cmds(char **tab)
{
	int i = 0;
	int cnt = 1;

	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
			cnt++;
		i++;
	}
	// printf ("(((((((((%d)))))))))\n", cnt);
	return (cnt);
}
/**
 * count the number of parts the command
 * have in order to allocate for it
 * @param tab all splitted tokens in a tab
 * @return the number of arguments that the command have.
 */
int cmd_len(char **tab)
{
	int i = 0;
	int cnt = 1;

	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|' || tab[i] == NULL)
			break ;
		i++;
	}
	return (i);
}

t_cmd	*get_cmds(char **tab)
{
	int		commande_len;
	t_cmd	*cmds;
	int		i;
	int		j;
	int		k;
	int		nbr;

	nbr = count_cmds(tab);
	// printf("*=**=* %d\n", nbr);
	cmds = malloc((nbr) * sizeof(t_cmd));
	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
		{
			i++;
			continue ;
		}
		commande_len = cmd_len(&tab[i]);
		printf("++++ commande len -> %d ++++  i -> %d ++++ j -> %d ++++\n", commande_len, i, j);
		if (commande_len == 1)
		{
			printf("ana f commande_len == 1\n");
			cmds[j].nbr = nbr;
			cmds[j].cmd = ft_strdup(tab[i]);
			printf("///////--< cmd >>>> %s *\n", tab[i]);
			printf("j(%d)get cmd 1--< cmd >>>> %s *\n",j,  cmds[j].cmd);
			cmds[j].args = malloc(sizeof(char *));
			cmds[j].args[0] = NULL;
			j++;
			i++;
		}
		else if (commande_len != 1)
		{
			printf("ana f commande_len == 2\n");
			cmds[j].nbr = nbr;
			printf("..... cmds.nbr -> %d\n", cmds[j].nbr);
			printf("====-> %s\n", tab[i]);
			cmds[j].cmd = ft_strdup(tab[i]);
			printf("///////--< cmd >>>> %c *\n", tab[i][0]);
			printf("\"\"\"\"\"   %d   \"\"\"\n", i);
			printf("get cmd (%d) 2--< cmd >>>> %s *\n",j, cmds[j].cmd);
			i++;
			cmds[j].args = malloc((commande_len) * sizeof(char *));
			k = 0;
			while (k < commande_len - 1)
			{
				cmds[j].args[k] = ft_strdup(tab[i]);
				printf("get cmd(%d) --< args(%d) >>>> %s *\n",j, k, cmds[j].args[k]);
				k++;
				i++;
			}
			cmds[j].args[k] = NULL;
			j++;
		}
	}
	return (cmds);
}

// int main()
// {
// 	char str[] = "ls -l | echo \"     \"\"hel>> lo >>   bye> $USER  tses>\"test | ls >>   > txt txt >> hello Hi How | good  luck   test  && hello";  //9

// 	// char str[] = "echo hello";
// 	t_cmd	*cmds_expanded;
// 	printf("*cnt -> (%d)\n", count(str));
// 	char **tab = split(str);
// 	// printf("tablen -> (%d)\n", ft_tablen(tab));
// 	int nbr = count_cmds(tab);
// 	printf("cmds : %d\n", nbr);
// 	t_cmd *cmds = get_cmds(tab);
// 	printf("==== %d ====\n", cmds[0].nbr);
// 	cmds_expanded = expandables(cmds);
// 	int i = 0;
// 	// while (i < cmds[i])

// 	// printf("%s\n", getenv("$USER"));
// 	// while(1) ;
// }