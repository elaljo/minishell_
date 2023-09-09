/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:16:38 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/08 17:45:34 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
	int		nbr;
	char	*cmd;
	char	**args;
} t_cmd;

typedef	struct s_quote
{
	int sq;
	int dq;
} t_quote;

typedef	struct s_ndx
{
	int i;
	int j;
	int k;
	int check;
	int check_space;
	int start;
	int cnt;
} t_ndx;

/* - - - - - - - - - - - - - - Splitter - - - - - - - - - - - - - - */
int		count(char *str);
int		handle_redir(char *str, char **tab, t_ndx *ndx, t_quote quote);
int		handle_pipe(char **tab, t_ndx *ndx);
char	**split(char *str);
int count_cmds(char **tab);

/* - - - - - - - - - - - - - - libft - - - - - - - - - - - - - - */

/**
 * duplicate a string using malloc
 * @param str the string to be duplicated
 * @return the duplicated string.
 */
char	*ft_strdup(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_tablen(char **tab);
char    **split_str(char *str, char c);
int		cnt_wrds(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
int	only_spaces(char *str);
// char	*tab_join(char **tab);



char	*expand_variables(char* input);
void	expand_variable(const char* var_name, char* expanded, size_t* j);
int		is_alnum(char c);
t_cmd	*expandables(t_cmd *cmds);
void	handle_quoted(char *str);
int check_quoted(char *str);
int count_cmds(char **tab);
int cmd_len(char **tab);
t_cmd	*get_cmds(char **tab);

#endif