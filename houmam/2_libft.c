/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_libft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:08:34 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/12 04:13:34 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_tablen(char **tab)
{
	int i = 0;
	while (tab[i])
		i++;
	return (i);
}

int    cnt_wrds(char *str, char c)
{
    int i = 0;
    int wrds = 0;
    int sq = 0;
    int dq = 0;
    
    while (str[i])
    {
        while (str[i] == c  && sq % 2 == 0 && dq % 2 == 0 && str[i])
            i++;
        if (str[i] == 39)
		{
			i++;	
        	sq++;
		}
        if (str[i] == 34)
        {
			i++;
			dq++;
		}
        if (str[i]  && sq % 2 == 0 && dq % 2 == 0)
        {
            while (str[i] != c && str[i])
            {
                if (str[i] == 39)
                    sq++;
                if (str[i] == 34)
                    dq++;
                i++;
            }
            wrds++;
        }
		else if (str[i])
        	i++;
    }
    return (wrds);
}

char    **split_str(char *str, char c)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int start = 0;
    int wrds = cnt_wrds(str, c);
    char **tab = ft_calloc(1,(wrds + 1) * sizeof(char *));
    int sq = 0;
    int dq = 0;

    while (str[i])
    {
        while (str[i] == c  && sq % 2 == 0 && dq % 2 == 0 && str[i])
            i++;
        if (str[i] == 39)
        {
            i++;    
            sq++;
        }
        if (str[i] == 34)
        {
            i++;
            dq++;
        }
        if (str && str[i])
        {
            start = i;
			if (i > 0 && str[i - 1] && (str[i - 1] == 34 || str[i - 1] == 34))
				start = i - 1;
            k = 0;
            while (str[i])
            {
                if (str[i] == c && sq % 2 == 0 && dq % 2 == 0)
                    break;
                if (str[i] == 39)
                    sq++;
                if (str[i] == 34)
                    dq++;
                i++;
            }
            tab[j] = ft_calloc(1,(i - start + 1) * sizeof(char));
            while (start < i)
            {
                tab[j][k] = str[start];
                k++;
                start++;
            }
			if (str[i] == 34 || str[i] == 34)
				i++;
            tab[j][k] = '\0';
            j++;
        }
    }
    tab[j] = NULL;
    return (tab);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	int i = 0;
// 	// int len = start;
// 	char *str = ft_calloc(1,(len + 1) * sizeof(char));

// 	while (s[i] && i < len)
// 	{
// 		str[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	str[5] = '\0';
// 	return (str);
// }

int	only_spaces(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (1);
	}
	return (0);
}

int	nbr_l(int n)
{
	long	num;
	int		i;

	num = n;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		nl;
	char	*p;

	nb = n;
	nl = nbr_l(nb);
	p = ft_calloc (1, nl * sizeof(char) + 1);
	if (!p)
		return (NULL);
	if (n == 0)
		p[0] = 48;
	else if (nb < 0)
	{
		p[0] = 45;
		nb *= -1;
	}
	while (nb)
	{
		p[nl - 1] = nb % 10 + 48;
		nb /= 10;
		nl--;
	}
	p[nbr_l(n)] = 0;
	return (p);
}