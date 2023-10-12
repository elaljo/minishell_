/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:39:07 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/15 17:39:07 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cnt_exp(char *str)
{
    int cnt = 0;
    int sq = 0;
    int dq = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\'' && i == 0)
                sq++;
        else if (str[i] == '"' && i == 0)
                dq++;
        else if (str[i] == '\'' && i != 0 && str[i - 1] != '\\')
                sq++;
        else if (str[i] == '"' && i != 0 && str[i - 1] != '\\')
                dq++;
        if(str[i] == '\'' && i != 0 && str[i - 1] != '\\' && sq % 2 != 0 && dq % 2 != 0)
                sq++;
        else if (str[i] == '"' && i != 0 && str[i - 1] != '\\' && dq % 2 != 0 && sq % 2 != 0)
                dq++;
        else if (sq % 2 == 0 && i != 0 && str[i] == '\'' && str[i - 1] != '\\')
                cnt++;
        else if (dq % 2 == 0 && i != 0 && str[i] == '"' && str[i - 1] != '\\')
                cnt++;
        else if (sq % 2 != 0 && i != 0 && str[i] == '\'' && str[i - 1] != '\\' && str[i - 1] != '\'' && str[i - 1] != '"')
                cnt++;
        else if (dq % 2 != 0 && i != 0 && str[i] == '"' && str[i - 1] != '\\' && str[i - 1] != '\'' && str[i - 1] != '"')
                cnt++;
        else if (!str[i + 1])
                cnt++;
        i++;
    }
//     printf("❤️❤️sq --> %d\n❤️❤️dq --> %d\n", sq % 2, dq % 2);
    return (cnt);
}
char    **quotes_split(char *str)
{
    int start = 0;
    int end = 0;
    int i = 0;
    int j = 0;
    int k;
    int sq = 0;
    int dq = 0;
    int len = cnt_exp(str) + 1;
    char **tab = ft_calloc(1,len * sizeof(char *));
    while (str[i])
    {
        start = i;
        if (i != 0 && ((str[i - 1] == '"' && dq % 2 != 0) || (str[i - 1] == '\'' && sq % 2 != 0)))
            start--;
        while (str[i])
        {
                if (str[i] == '\'' && i == 0)
                        sq++;
                else if (str[i] == '"' && i == 0)
                        dq++;
                else if (str[i] == '\'' && i != 0 && str[i - 1] != '\\')
                        sq++;
                else if (str[i] == '"' && i != 0 && str[i - 1] != '\\')
                        dq++;
                if(str[i] == '\'' && i != 0 && str[i - 1] != '\\' && sq % 2 != 0 && dq % 2 != 0)
                        sq++;
                else if (str[i] == '"' && i != 0 && str[i - 1] != '\\' && dq % 2 != 0 && sq % 2 != 0)
                        dq++;
                else if (sq % 2 == 0 && i != 0 && str[i] == '\'' && str[i - 1] != '\\')
                        break ;
                else if (dq % 2 == 0 && i != 0 && str[i] == '\"' && str[i - 1] != '\\')
                        break ;
                else if (sq % 2 != 0 && i != 0 && str[i] == '\'' && str[i - 1] != '\\' && str[i - 1] != '\'' && str[i - 1] != '"')
                        break ;
                else if (dq % 2 != 0 && i != 0 && str[i] == '\"' && str[i - 1] != '\\' && str[i - 1] != '\'' && str[i - 1] != '"')
                        break ;
                else if (!str[i + 1])
                        break ;
                i++;
        }
        tab[j] = ft_calloc(1,(i - start + 2) * sizeof(char));
        // printf("***(%d)***\n", i - start + 2);
        k = 0;
        end = i;
        if ((str[i] == '\"' && dq % 2 == 0) || (str[i] == '\'' && sq % 2 == 0) || str[i + 1] == '\0')
            end++;
        while (start < end)
        {
            tab[j][k] = str[start];
            k++;
            start++;
        }
        tab[j][k] = '\0';
        j++;
        if (str[i])
            i++;
    }
    tab[j] = NULL;
    return (tab);
}
