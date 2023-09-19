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

// char    *tab_join(char *s1, char s2*)
// {

// }

void    expand_all(t_cmd *cmds)
{
    printf("************* start expand all ********************\n");
    int i = 0;

    printf("+++ %s +++\n", cmds[0].args[0]);
    printf("+++ %s +++\n", cmds[0].args[1]);
    // cmds[0].args[0];
    // cmds[0].args[0];
    while (i < cmds->args_nbr)
    {
        expander(&cmds[i], cmds[i].cmd_len);
        i++;
    }
    printf("************* end expand all ********************\n");
}

void    expander(t_cmd *cmd, int len)
{
    char **args = cmd->args;
    printf("+++ %s +++\n", args[0]);
    printf("+++ %s +++\n", args[1]);
    printf("************* start expander ********************\n");
    int i = 0;
    int j;
    int k;
    int quoted;//if quoted = 1 then 
    int empty = 0;
    char *tmp;
    // int sq_nbr;
    // int dq_nbr;
    char *joigned_0;
    char *joigned_1;
    // char *joigned_2;
    char **quote_splitted;
    char **dollar_splitted;
    // int is_expandable = 0;/*blati ankhdmoh hada ila kanet chi haja 7yedna liha "" 
    //ghadi n expandiwha w ila 7yedna liha ghir single ma3endna mandiro liha*/
    printf("************ len -? %d ************** %d \n",len, cmd->args_nbr);
    while (i < len)
    {
        printf("✅args[i]before --> (%s)\n", args[i]);
        quote_splitted = quotes_split(args[i]);
        j = 0;
        while (quote_splitted[j] != NULL)
        {
            // while (quoted != 0)
            // {
                quoted = check_quoted(quote_splitted[j]);
                // if (ft_strlen(quote_splitted[j]) == 2 && quoted != 0)
                // if (quoted == 1)
                //     sq++;
                // else if (quoted == 2)
                //     dq += 2;
                printf("🌕   quoted --> %d\n", quoted);

            // }
            if (quoted != 0)
            {
                if (ft_strlen(quote_splitted[j]) == 2)
                {
                    printf("➡️\n");
                    free(quote_splitted[j]);
                    quote_splitted[j] = NULL;
                    empty = 1;
                }
                else
                {
                    printf("➡️➡️\n");
                    tmp = ft_strdup(quote_splitted[j]);
                    free(quote_splitted[j]);
                    quote_splitted[j] = handle_quoted(tmp);
                }
            }
            printf("❌quote splitted ======> %s\n", quote_splitted[j]);
            // if (quote_splitted[j] != NULL)
            dollar_splitted = dollar_split(quote_splitted[j]);
            printf("➡️➡️➡️➡️➡️➡️➡️➡️➡️➡️➡️➡️➡️➡️\n");
            k = 0;
            while (dollar_splitted[k] != NULL)
            {
                // printf("kkkkkkkkkkkk --> %d\n", k);
                printf("🔴🔴*dollar_splitted[%d] --> (%s)\n", empty, dollar_splitted[k]);
                if (quoted != 1 && dollar_splitted[k][0] == '$' && is_var(dollar_splitted[k][1]) == 1 )
                {
                    tmp = ft_strdup(dollar_splitted[k]);
                    free(dollar_splitted[k]);
                    dollar_splitted[k] = ft_strdup(expand_var(tmp));
                    free(tmp);
                }
                printf("\n****** im here ---(%d)--*******\n\n", k);
                if (k == 0)
                    joigned_0 = ft_strjoin("", dollar_splitted[k]);
                else if (k != 0)
                {
                    printf("🔴🔴🔴joigned_0 ---------> %s\n", joigned_0);
                    tmp = ft_strdup(joigned_0);
                    free(joigned_0);
                    joigned_0 = ft_strjoin(tmp, dollar_splitted[k]);
                    free(tmp);
                }
                printf("🔴🔴🔴🔴dollar_splitted[%d] --> (%s)\n", k, dollar_splitted[k]);
                k++;
                printf("🔴🔴🔴🔴🔴-------- dollar | joined : %s --------\n", joigned_0);
            }
            printf("👾👾👾👾👾\n");
            // printf("||-----joigned_1 ======> %s\n", joigned_1);
            // if (empty == 1)
            // {
            // joigned_0 = NULL;
            free(quote_splitted[j]);
            quote_splitted[j] = ft_strdup(joigned_0);
            printf("jjjjjjjjjjjjjj -> %d\n", j);
            free(joigned_0);
            // }
            // printf("___ joigned_1 :-> %s\n", joigned_0);
            if (j == 0)
                joigned_1 = ft_strjoin("", quote_splitted[j]);
            else
            {
                tmp = ft_strdup(joigned_1);
                printf("❌❌       <<<<< tmp --> %s >>>>>>\n", tmp);
                free(joigned_1);
                joigned_1 = ft_strjoin(tmp, quote_splitted[j]);
                free(tmp);
            }
            printf("❌❌❌-------- quotes joined : %s --------\n", joigned_1);
            // printf("\n\n\n\n\n");
            j++;
        }
        free(args[i]);
        args[i] = ft_strdup(joigned_1);
        printf("* i -> %d * j -> %d * k -> %d\n", i, j, k);
        printf("💕 args[i]after --> (%s)\n", args[i]);
        free(joigned_1);
        i++;
    }
    printf("-------- %d --------\n", i);
    printf("************* end expander ********************\n");
}

