/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:05 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/04 04:42:13 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parsing_errors(char *str)
{
    t_quote qt = unclosed_quotes(str);
    if (qt.sq % 2 != 0 || qt.dq % 2 != 0)
    {
        ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
        exit (1);//exit status
    }
}

t_quote unclosed_quotes(char *str)
{
    int i;
    t_quote qt;
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

int successive_redir(char *str)
{
        char **tab = split(str);
        removing_spaces(tab);
        int i = 0;
        
        while (tab[i] != NULL)
        {
            if (ft_strcmp(tab[i], "<") == 0 || ft_strcmp(tab[i], "<<") == 0 || ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i], ">>") == 0)
            {
                // printf("(%d)(%s) Ana hna\n", i, tab[i]);
                if (tab[i + 1] && (ft_strcmp(tab[i + 1], "<") == 0 || ft_strcmp(tab[i + 1], "<<") == 0 || ft_strcmp(tab[i + 1], ">") == 0 || ft_strcmp(tab[i + 1], ">>") == 0))
                {
                    if (ft_strcmp(tab[i + 1], "<") == 0)
                        ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
                    else if (ft_strcmp(tab[i + 1], ">") == 0)
                        ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
                    else if (ft_strcmp(tab[i + 1], ">>") == 0)
                        ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
                    else if (ft_strcmp(tab[i + 1], "<<") == 0)
                        ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
                    else if (ft_strcmp(tab[i + 1], "|") == 0)
                        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                    exit (1);
                }
                else if (tab[i + 1] && ft_strcmp(tab[i + 1], "") == 0)
                {
                    while (tab[++i][0] != '\0' && ft_strcmp(tab[i], "") == 0);
                    if (tab[i] && (ft_strcmp(tab[i], "<") == 0 || ft_strcmp(tab[i], "<<") == 0 || ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i], ">>") == 0))
                    {
                        if (ft_strcmp(tab[i], "<") == 0)
                            ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
                        else if (ft_strcmp(tab[i], ">") == 0)
                            ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
                        else if (ft_strcmp(tab[i], ">>") == 0)
                            ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
                        else if (ft_strcmp(tab[i], "<<") == 0)
                            ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
                        else if (ft_strcmp(tab[i], "|") == 0)
                            ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                        exit (1);
                    }
                }
            }
            if (ft_strcmp(tab[i], "|") == 0)
            {
                while (tab[++i] && ft_strcmp(tab[i], "") == 0);
                if (tab[i] == NULL)
                {
                     ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                     exit (0);   
                }
                else if (ft_strcmp(tab[i], "|") == 0)
                {
                //      printf("ana f li te7t NULL\n");
                     ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                     exit (0);   
                }
            }
        //     printf("---%s--\n", tab[i]);
            i++;
        }
        return (0);
}

int     redir_errors(t_cmd *cmds)
{
    int i = 0;
    int red;

    while (i < cmds[0].args_nbr)
    {
        red = 0;
        while (red < cmds[i].redir_nbr)
        {
            if (ft_strcmp(cmds[i].redir[red].redi, "<<") == 0 || ft_strcmp(cmds[i].redir[red].redi, ">>") == 0 || ft_strcmp(cmds[i].redir[red].redi, ">") == 0 || ft_strcmp(cmds[i].redir[red].redi, "<") == 0)
            {
                if (cmds[i].redir[red].eof == NULL || cmds[i].redir[red].eof[0] == '\0')
                {
                    ft_putstr_fd("minishell: syntax error near unexpected token `newline'", 2);
                    exit (0);
                }
            }
            red++;
        }
        i++;
    }
    return (0);
}