/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_split_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:07:17 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/09 18:32:57 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count(char *str)
{
	int i = 0;
	int prt = 0;
	t_quote quote;
	quote.sq = 0;
	quote.dq = 0;

	while (str[i])
	{
		if (i == 0)
		{
			while (str[i] && (str[i] == ' ' ||  str[i] == '\t'))
				i++;
		}
		if (str[i] == 39) // 39 '
			quote.sq++;
		if (str[i] == 34) // 34 "
			quote.dq++;
		if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && i != 0 && str[i - 1] != '|' && str[i - 1] != ' ' && str[i] != '\t' && str[i - 1] != '>' && str[i - 1] != '<' && (str[i] == ' ' ||  str[i] == '\t'))
			prt++;                //in case l9ina space mora chi redir or space or pipe or chi character special that's why I check i - 1
		else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[i] == '|')
			prt++;
		else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[i] == '>' && str[i + 1] && str[i + 1] != '>')
			prt++;
		else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[i] == '<' && str[i + 1] && str[i + 1] != '<')
			prt++;
		else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[i] == '>' && str[i + 1] && str[i + 1] == '>')
		{
			prt++;
			i++;
		}
		else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			prt++;
			i++;
		}
		else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && !str[i + 1] && str[i - 1] != '|' && str[i - 1] != ' ' && str[i - 1] != '\t' && str[i - 1] != '>' && str[i - 1] != '<')
			prt++;           //in case wslna lchar li 9bl nul o kan 3ad 9bel mno chi pipe ola chi haja li deja 7sbna
		i++;
	}
	return (prt);
}

char	**split(char *str)
{
	// printf("ana hna");
	t_ndx	ndx;
	ndx.i = 0;
	ndx.j = 0;
	ndx.cnt = count(str);
	// printf("---------------> cnt : %d\n", ndx.cnt);
	char **tab = malloc((ndx.cnt + 1) * sizeof(char *));
	t_quote quote;
	quote.sq = 0;
	quote.dq = 0;
	ndx.check_space = 0;
	
	while (str[ndx.i])
	{
		if (ndx.i == 0)
		{
			while (str[ndx.i] == ' ' || str[ndx.i] == '\t')
				ndx.i++;
		}
		ndx.start = ndx.i;
		while (str[ndx.i])
		{
			// printf("ana dkhelt %d\n", i);
			if (ndx.i != 0 && str[ndx.i] == 39 && str[ndx.i - 1] != '\\')
				quote.sq++;
			else if (ndx.i != 0 && str[ndx.i] == 34 && str[ndx.i - 1] != '\\')
				quote.dq++;
			else if (ndx.i == 0 && str[ndx.i] == 39)
				quote.sq++;
			else if (ndx.i == 0 && str[ndx.i] == 34)
				quote.dq++;
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && (str[ndx.i] == ' ' ||  str[ndx.i] == '\t') \
					 && ndx.i != 0 && str[ndx.i - 1] != '|' && str[ndx.i - 1] != ' ' && str[ndx.i - 1] != '\t' && \
					str[ndx.i - 1] != '>' && str[ndx.i - 1] != '<' )
			{
				ndx.check_space = 1;
				// printf("ana f space f %d\n", ndx.i);
				break ;                //in case l9ina space mora chi redir or space or pipe or chi character special that's why I check i - 1
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '|')
			{
				printf("ana f pipe f %d\n", ndx.i);
				handle_pipe(tab, &ndx);
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '>' && str[ndx.i + 1] && str[ndx.i + 1] != '>')
			{
				// printf("ana f redir > f %d\n", ndx.i);
				handle_redir(str, tab, &ndx, quote);
				// break ;
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '<' && str[ndx.i + 1] && str[ndx.i + 1] != '<')
			{
				// printf("ana f redir < f %d\n", ndx.i);
				handle_redir(str, tab, &ndx, quote);
				// break ;
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '>' && str[ndx.i + 1] && str[ndx.i + 1] == '>')
			{
				printf("ana f  >> f %d\n", ndx.i);
				handle_redir(str, tab, &ndx, quote);
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '<' && str[ndx.i + 1] && str[ndx.i + 1] == '<')
			{
				printf("ana f <redir >< f %d\n", ndx.i);
				handle_redir(str, tab, &ndx, quote);
			}
			// else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && !str[ndx.i + 1] && str[ndx.i - 1] != '|' && str[ndx.i - 1] != ' ' && str[ndx.i - 1] != '\t' && str[ndx.i - 1] != '>' && str[ndx.i - 1] != '<')
			// {
			// 	printf("ana f lkher %d\n", ndx.i);
			// 	break ;           //in case wslna lchar li 9bl nul o kan 3ad 9bel mno chi pipe ola chi haja li deja 7sbna
			// }
			if (str[ndx.i])
				ndx.i++;
		}
		tab[ndx.j] = malloc((ndx.i - ndx.start + 1) * sizeof(char));
		ndx.k = 0;
		while (ndx.start < ndx.i)
		{
			tab[ndx.j][ndx.k] = str[ndx.start];
			ndx.start++;
			ndx.k++;
		}
		tab[ndx.j][ndx.k] = '\0';
		if (ndx.check_space == 1)
		{
			while ((str[ndx.i] == ' ' || str[ndx.i] == '\t') && quote.sq % 2 == 0 && quote.dq % 2 == 0)
				ndx.i++;
			ndx.i--;//hadi dernaha 7itach f had if kan incrementer ta kanl9a chi haja mn ghir space o mn mora makykhrej mn had condition kayna hadi if (str[ndx.i]) katzid t incrementer mara akhra o kan9adro nskipiw chi space o ndekhlo f word akhor
			ndx.check_space = 0;
		}
		printf("(%s)\n", tab[ndx.j]);
		ndx.j++;
		// printf("the last start :-> %d\n", ndx.start);
		if (str[ndx.i])
			ndx.i++;
	}
	tab[ndx.j] = NULL;
	// printf("split done\n");
	return (tab);
}

// int main()
// {               //  1  23     4                                   56   78    9
// 	char str[] = "ls -l | echo "  \"\"   hel>> lo >>  $USER bye>   tses>" | ls >>   > txt txt >> hello Hi How | good  luck   test  &&  hello";  //9

// 	printf("cnt -> (%d)\n", count(str));
// 	int i = 0;
// 	char **tab = split(str);

// 	// while (i < 21)
// 	// {
// 	// 	printf("%s\n", tab[i]);
// 	// 	i++;
// 	// }
	
// }


