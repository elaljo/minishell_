/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:49:55 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/14 22:49:55 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cnt_redir(char **tab)
{
    int i = 0;
    int cnt = 0;

	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|' || tab[i] == NULL)
			break ;
        else if (ft_strcmp("<<", tab[i]) == 0)
            cnt++;
        else if (ft_strcmp("<", tab[i]) == 0)
            cnt++;
        else if (ft_strcmp(">>", tab[i]) == 0)
            cnt++;
        else if (ft_strcmp(">", tab[i]) == 0)
            cnt++;
		i++;
	}
	//printf("cmd_len ----> %d\n\n", i);
	return (cnt);
}