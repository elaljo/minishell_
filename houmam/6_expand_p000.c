/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p000.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:52:12 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/16 16:52:12 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    expand_all(t_cmd *cmds, t_data data)
{
    int i = 0;
    while (i < cmds->args_nbr && cmds->args[i] != NULL)
    {
        // printf("\n\n\nI'm here\n\n\n\n");
        expander(&cmds[i], cmds[i].cmd_len, data);
        i++;
    }
    
}

void    expander(t_cmd *cmd, int len, t_data data)
{
    char **args = cmd->args;
    int i = 0;
    int j;
    int k;
    int quoted;//if quoted = 1 then 
    int empty = 0;
    char *tmp;
    char *joigned_0;
    char *joigned_1;
    char **quote_splitted;
    char **dollar_splitted;
    while (i < len)
    {
        quote_splitted = quotes_split(args[i]);
        j = 0;
        while (quote_splitted[j] != NULL)
        {
            quoted = check_quoted(quote_splitted[j]);

            if (quoted != 0)
            {
                if (ft_strlen(quote_splitted[j]) == 2)
                {
                    free(quote_splitted[j]);
                    quote_splitted[j] = NULL;
                    empty = 1;
                }
                else
                {
                    tmp = ft_strdup(quote_splitted[j]);
                    free(quote_splitted[j]);
                    quote_splitted[j] = handle_quoted(tmp);
                }
            }
            dollar_splitted = dollar_split(quote_splitted[j]);
            k = 0;
            while (dollar_splitted[k] != NULL)
            {
                if (quoted != 1 && dollar_splitted[k][0] == '$' && dollar_splitted[k][1] == '?')
                {
                    tmp = ft_itoa(g_exit_status);
                    free(dollar_splitted[k]);
                    dollar_splitted[k] = ft_strdup(tmp);
                }
                else if (quoted != 1 && dollar_splitted[k][0] == '$' && is_var(dollar_splitted[k][1]) == 1 )
                {
                    tmp = ft_strdup(dollar_splitted[k]);
                    free(dollar_splitted[k]);
                    dollar_splitted[k] = ft_strdup(expand_var(tmp, data));
                }
                if (k == 0)
                    joigned_0 = ft_strjoin("", dollar_splitted[k]);
                else if (k != 0)
                {
                    tmp = ft_strdup(joigned_0);
                    free(joigned_0);
                    joigned_0 = ft_strjoin(tmp, dollar_splitted[k]);
                    free(tmp);
                }
                k++;
            }
            if (empty == 1)
            {
                joigned_0 = ft_strdup("");
                empty = 0;
            }
            free(quote_splitted[j]);
            quote_splitted[j] = ft_strdup(joigned_0);
            free(joigned_0);
            if (j == 0)
                joigned_1 = ft_strjoin("", quote_splitted[j]);
            else
            {
                tmp = ft_strdup(joigned_1);
                free(joigned_1);
                joigned_1 = ft_strjoin(tmp, quote_splitted[j]);
                free(tmp);
            }
            j++;
        }
        free(args[i]);
        args[i] = ft_strdup(joigned_1);
        // printf("%s", args[i]);
        free(joigned_1);
        // printf("\n\n\nI'm here(%d)*(len = %d)---(joined --> %s)\n\n\n\n", i, len, args[i]);
        i++;
    }
}
