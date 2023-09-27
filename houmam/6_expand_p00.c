/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:46:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/16 05:46:53 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_var(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
}

int cnt_dollars(char *str)
{
    if (!str)
        return (0);
    int i = 0;
    int cnt = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && is_var(str[i + 1]) == 1)
        {
            i++;
            while (str[i] && is_var(str[i]) == 1)
                i++;
            cnt++;
        }
        else
        {
            while (str[i])
            {
                if (str[i] == '$' && str[i + 1] && is_var(str[i + 1]) == 1)
                    break;
                i++;
            }
            cnt++;
        }
    }
    return (cnt);
}

char    **dollar_split(char *str)
{
    int i = 0;
    int j = 0;
    int k;
    int start = 0;
    int len = cnt_dollars(str) + 1;
    char **tab = malloc(len * sizeof(char *));
    while (len > 1 && str[i])
    {
        start = i;
        while (str[i])
        {
            if (str[i] == '$' && str[i + 1] && is_var(str[i + 1]) == 1)
            {
                i++;
                while (str[i] && is_var(str[i]) == 1)
                    i++;
                break ;
            }
            else
            {
                while (str[i])
                {
                    if (str[i] == '$' && str[i + 1] && is_var(str[i + 1]) == 1)
                        break;
                    i++;
                }
                break ;
            }
        }
        tab[j] = malloc(i - start + 1);
        k = 0;
        while (start < i)
        {
            tab[j][k] = str[start];
            k++;
            start++;
        }
        tab[j][k] = '\0';
        j++;
    }
    tab[j] = NULL;
    return (tab);
}

char    *expand_var(char *str)
{
    char *tmp = ft_strdup(str);
    free(str);
    str = ft_strdup(getenv(tmp + 1));
    free(tmp);
    return (str);
}