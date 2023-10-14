/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:05 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 11:15:08 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	successive_p2(char **tab, int *i)
{
	if (tab[(*i) + 1] && is_redir(tab[(*i) + 1]) == 1)
	{
		put_error(tab[(*i) + 1]);
		ft_str_free(tab);
		return (2);
	}
	else if (tab[(*i) + 1] && ft_strcmp(tab[(*i) + 1], "") == 0)
	{
		(*i)++;
		while (tab[*i][0] != '\0' && ft_strcmp(tab[*i], "") == 0)
			(*i)++;
		if (tab[*i] && is_redir(tab[*i]) == 1)
		{
			put_error(tab[*i]);
			ft_str_free(tab);
			return (2);
		}
	}
	else if (tab[(*i) + 1] == NULL)
	{
		put_error("|");
		ft_str_free(tab);
		return (2);
	}
	return (0);
}

int	successive_p3(char **tab, int *i)
{
	(*i)++;
	while (tab[*i] && ft_strcmp(tab[*i], "") == 0)
		(*i)++;
	if (tab[*i] == NULL)
	{
		put_error("|");
		ft_str_free(tab);
		return (2);
	}
	else if (ft_strcmp(tab[*i], "|") == 0)
	{
		put_error("|");
		ft_str_free(tab);
		return (2);
	}
	return (0);
}

int	successive_redir(char *str)
{
	char	**tab;
	int		i;

	tab = split(str);
	removing_spaces(tab);
	i = 0;
	while (tab[i] != NULL)
	{
		if (is_redir(tab[i]) == 1)
			if (successive_p2(tab, &i) == 2)
				return (2);
		if (ft_strcmp(tab[i], "|") == 0)
			if (successive_p3(tab, &i) == 2)
				return (2);
		i++;
	}
	ft_str_free(tab);
	return (0);
}

int	redir_p2(t_cmd *cmds, int *red, int i)
{
	*red = 0;
	while (*red < cmds[i].redir_nbr)
	{
		if (is_redir(cmds[i].redir[*red].redi) == 1)
		{
			if (cmds[i].redir[*red].eof == NULL || \
				cmds[i].redir[*red].eof[0] == '\0')
			{
				ft_putstr_fd("minishell: syntax error", 2);
				ft_putstr_fd(" near unexpected token `newline'\n", 2);
				return (2);
			}
			else if (is_redir(cmds[i].redir[*red].eof) == 1)
			{
				put_error(cmds[i].redir[*red].eof);
				return (2);
			}
		}
		(*red)++;
	}
	return (0);
}

int	redir_errors(t_cmd *cmds)
{
	int	i;
	int	red;

	i = -1;
	while (++i < cmds[0].argu_nbr)
	{
		if (redir_p2(cmds, &red, i) == 2)
			return (2);
		red = 0;
		while (red < cmds[i].redir_nbr)
		{
			if (is_redir(cmds[i].redir[red].redi) == 1)
			{
				if (cmds[i].redir[red].eof == NULL || \
					cmds[i].redir[red].eof[0] == '\0')
				{
					ft_putstr_fd("minishell: syntax error", 2);
					ft_putstr_fd(" near unexpected token `newline'\n", 2);
					return (2);
				}
			}
			red++;
		}
	}
	return (0);
}
