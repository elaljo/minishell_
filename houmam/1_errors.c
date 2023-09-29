/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:05 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/29 22:10:46 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parsing_errors(char *str)
{
    t_quote qt = unclosed_quotes(str);
    if (qt.sq % 2 != 0 || qt.dq % 2 != 0)
    {
        ft_putstr_fd("syntax error : unclosed quotes\n", 2);
        exit (1);//exit status
    }
}

t_quote unclosed_quotes(char *str)
{
    t_quote qt;
    int i;
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
        if(str[i] == '\'' && i != 0 && str[i - 1] != '\\' && qt.sq % 2 != 0 && qt.dq % 2 != 0)
                qt.sq++;
        else if (str[i] == '"' && i != 0 && str[i - 1] != '\\' && qt.dq % 2 != 0 && qt.sq % 2 != 0)
                qt.dq++;
        i++;
    }
    return (qt);
}
