/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_split_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:07:17 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/30 00:33:47 by hait-sal         ###   ########.fr       */
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
	t_ndx	ndx;
	ndx.i = 0;
	ndx.j = 0;
	ndx.cnt = count(str) + 1;
	char **tab = malloc((ndx.cnt + 1) * sizeof(char *));
	t_quote quote;
	quote.sq = 0;
	quote.dq = 0;
	ndx.check_space = 0;
	ndx.pipe = 0;
	
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
			printf("🟥🟥start = %d 🟥🟥\n",ndx.start);
			if (ndx.i != 0 && str[ndx.i] == 39 && str[ndx.i - 1] != '\\')
				quote.sq++;
			else if (ndx.i != 0 && str[ndx.i] == 34 && str[ndx.i - 1] != '\\')
				quote.dq++;
			else if (ndx.i == 0 && str[ndx.i] == 39)
				quote.sq++;
			else if (ndx.i == 0 && str[ndx.i] == 34)
				quote.dq++;
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i + 1] != '\0' && (str[ndx.i + 1] == '|' || (str[ndx.i + 1] == '<' && str[ndx.i] != '<') || (str[ndx.i + 1] == '>' && str[ndx.i] != '>')))
			{
				printf("🟥🟥cnd-1🟥i = %d *** str[i] = (%c)🟥\n", ndx.i, str[ndx.i]);
				// printf("❤️❤️❤️❤️ana dkhelt \n");
				ndx.pipe = 1;
				break;
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && (str[ndx.i] == ' ' ||  str[ndx.i] == '\t') \
					 && ndx.i != 0 && str[ndx.i - 1] != '|' && str[ndx.i - 1] != ' ' && str[ndx.i - 1] != '\t' && \
					str[ndx.i - 1] != '>' && str[ndx.i - 1] != '<' )
			{
				printf("🟥🟥cdn-2🟥i = %d *** str[i] = (%c)🟥\n", ndx.i, str[ndx.i]);
				ndx.check_space = 1;
				break ;                //in case l9ina space mora chi redir or space or pipe or chi character special that's why I check i - 1
			}
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '|')
				handle_pipe(tab, &ndx, str);
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '>' && str[ndx.i + 1] && str[ndx.i + 1] != '>')
			{
				printf("🟥🟥redi-1🟥i = %d *** str[i] = (%c)🟥\n", ndx.i, str[ndx.i]);
				handle_redir(str, tab, &ndx, quote);
			}	
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '<' && str[ndx.i + 1] && str[ndx.i + 1] != '<')
			{
				printf("🟥🟥redi-2🟥i = %d *** str[i] = (%c)🟥\n", ndx.i, str[ndx.i]);
				handle_redir(str, tab, &ndx, quote);
			}	
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '>' && str[ndx.i + 1] && str[ndx.i + 1] == '>')
			{
				printf("🟥🟥redi-3🟥i = %d *** str[i] = (%c)🟥\n", ndx.i, str[ndx.i]);
				handle_redir(str, tab, &ndx, quote);
			}	
			else if (quote.sq % 2 == 0 && quote.dq % 2 == 0 && str[ndx.i] == '<' && str[ndx.i + 1] && str[ndx.i + 1] == '<')
			{
				printf("🟥🟥redi-4🟥i = %d *** str[i] = (%c)🟥\n", ndx.i, str[ndx.i]);
				handle_redir(str, tab, &ndx, quote);
			}	
			printf("🟥before🟥i = %d *** str[i] = (%c)🟥🟥\n", ndx.i, str[ndx.i]);
			if (str[ndx.i])
				ndx.i++;
			printf("🟥after🟥i = %d *** str[i] = (%c)🟥🟥\n", ndx.i, str[ndx.i]);
		}
		tab[ndx.j] = malloc((ndx.i - ndx.start + 1) * sizeof(char));
		if (ndx.pipe == 1)
			ndx.i++;
		ndx.k = 0;
		printf("🟥after after🟥start = %d |||| i = %d *** str[i] = (%c)🟥🟥\n",ndx.start, ndx.i, str[ndx.i]);
		while (ndx.start < ndx.i)
		{
			tab[ndx.j][ndx.k] = str[ndx.start];
			ndx.start++;
			ndx.k++;
		}
		tab[ndx.j][ndx.k] = '\0';
		if (ndx.pipe == 1)
		{
			ndx.i--;
			ndx.pipe = 0;
		}
		printf("➡️split --> (%s)⬅️\n", tab[ndx.j]);
		if (ndx.check_space == 1)
		{
			// printf("2nnnnnnnnnnnnnnnnnnnn\n");
			while ((str[ndx.i] == ' ' || str[ndx.i] == '\t') && quote.sq % 2 == 0 && quote.dq % 2 == 0)
				ndx.i++;
			ndx.i--;//hadi dernaha 7itach f had if kan incrementer ta kanl9a chi haja mn ghir space o mn mora makykhrej mn had condition kayna hadi if (str[ndx.i]) katzid t incrementer mara akhra o kan9adro nskipiw chi space o ndekhlo f word akhor
			ndx.check_space = 0;
		}
		ndx.j++;
		if (str[ndx.i])
			ndx.i++;
	}
	tab[ndx.j] = NULL;
	return (tab);
}

char	*rm_spaces(char *str)
{
	int i = 0;
	char *start;
	// char *end;
	int len;

	while (str[i] == ' ')
		i++;
	start = ft_strdup(&str[i]);
	len = ft_strlen(start);
	len--;
	if (start[len] == ' ')
	{
		i = 0;
		while (start[i] != ' ')
		{
			str[i] = start[i];
			i++;
		}
		str[i] = '\0';
		free(start);
		return (str);
	}
	return (start);
}

void	removing_spaces(char **str)
{
	int i = 0;
	char *tmp;

	while (str[i] != NULL)
	{
		tmp = ft_strdup(rm_spaces(str[i]));
		str[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}
