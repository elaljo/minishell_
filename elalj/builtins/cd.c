/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:48:37 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/19 11:30:07 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*my_getenv(char *name, t_data *data)
{
	int		i;
	char	*env_var;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	env_var = NULL;
	while (data->c_env[i] != NULL)
	{
		env_var = data->c_env[i];
		if ((ft_strncmp(env_var, name, name_len) == 0)
			&& (env_var[name_len] == '='))
			return (&env_var[name_len + 1]);
		i++;
	}
	return (NULL);
}

char	*get_old_pwd(void)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 1024);
	if (old_pwd == NULL)
	{
		perror("getcwd");
		exit (1);
	}
	return (old_pwd);
}

void	export_old_pwd(char *old_pwd, t_data *data)
{
	int		i;
	char	*full_env;
	char	*tmp;

	full_env = ft_strjoin("OLDPWD=", old_pwd);
	i = 0;
	while (data->c_env[i] != 0)
	{
		tmp = strback(data->c_env[i]);
		if (ft_strcmp(tmp, "OLDPWD") == 0)
		{
			free(data->c_env[i]);
			data->c_env[i] = ft_strdup(full_env);
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	free(full_env);
}

int	run_cd_only(t_data *data, char *home_dir)
{
	char	*old_pwd;
	int		check;

	check = 0;
	if (home_dir == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		data->new_st = 1;
	}
	else
	{
		old_pwd = get_old_pwd();
		export_old_pwd(old_pwd, data);
		check = chdir((const char *)home_dir);
		export_pwd(data);
		free(old_pwd);
	}
	return (check);
}

void	my_cd(t_cmd *cmd, int i, t_data *data)
{
	char	*home_dir;
	int		check;
	char	*old_pwd;

	check = 0;
	home_dir = my_getenv("HOME", data);
	if (!cmd[i].argu[1])
		check = run_cd_only(data, home_dir);
	else
	{
		old_pwd = get_old_pwd();
		export_old_pwd(old_pwd, data);
		check = chdir(cmd[i].argu[1]);
		export_pwd(data);
		free(old_pwd);
	}
	if (check != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		data->new_st = 1;
		perror(cmd[i].argu[1]);
	}
}
