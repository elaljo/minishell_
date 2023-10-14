/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_errors_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:59:25 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 11:00:46 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_error(char *str)
{
	if (ft_strcmp(str, "<") == 0)
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putstr_fd(" near unexpected token `<'\n", 2);
	}
	else if (ft_strcmp(str, ">") == 0)
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putstr_fd(" near unexpected token `>'\n", 2);
	}
	else if (ft_strcmp(str, ">>") == 0)
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putstr_fd(" near unexpected token `>>'\n", 2);
	}
	else if (ft_strcmp(str, "<<") == 0)
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putstr_fd(" near unexpected token `<<'\n", 2);
	}
	else if (ft_strcmp(str, "|") == 0)
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putstr_fd(" near unexpected token `|'\n", 2);
	}
}

int	parsing_errors(char *str)
{
	t_quote	qt;

	qt = unclosed_quotes(str);
	if (qt.sq % 2 != 0 || qt.dq % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
		return (2);
	}
	return (0);
}

t_quote	unclosed_quotes(char *str)
{
	int		i;
	t_quote	qt;

	qt.sq = 0;
	qt.dq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && i == 0)
			qt.sq++;
		else if (str[i] == '"' && i == 0)
			qt.dq++;
		else if (str[i] == '\'' && i != 0 && str[i - 1] != '\\')
			qt.sq++;
		else if (str[i] == '"' && i != 0 && str[i - 1] != '\\')
			qt.dq++;
		if (str[i] == '\'' && i != 0 && str[i - 1] != '\\' && \
			qt.sq % 2 != 0 && qt.dq % 2 != 0)
			qt.sq++;
		else if (str[i] == '"' && i != 0 && str[i - 1] != '\\' && \
			qt.dq % 2 != 0 && qt.sq % 2 != 0)
			qt.dq++;
		i++;
	}
	return (qt);
}

//*******************************************************************
int	cmd_pipe(char **tab, t_cmd *cmds)
{
	if (tab[0] && ft_strcmp(tab[0], "|") == 0)
	{
		put_error("|");
		return (2);
	}
	else if (tab[0] && ft_strcmp(tab[0], "|") == 0 && \
			cmds->redir_nbr != 0)
	{
		put_error("|");
		return (2);
	}
	return (0);
}
