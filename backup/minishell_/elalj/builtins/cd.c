/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:48:37 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/05 20:51:26 by hait-sal         ###   ########.fr       */
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
		if ((ft_strncmp(env_var, name, name_len) == 0) && (env_var[name_len] == '='))
			return (&env_var[name_len + 1]);
		i++;
	}
	return (NULL);
}
char	*get_old_pwd()
{
	size_t	size;
	char	*buffer;
	char	*old_pwd;

	size = 1024;
	buffer = ft_calloc(1,size + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	old_pwd = getcwd(buffer, size);
	if (old_pwd == NULL)
		perror("getcwd");
	return (old_pwd);
}
void	export_old_pwd(char *old_pwd, t_data *data)
{
	int	i;
	char *full_env;

	full_env = "OLDPWD=";
	full_env = ft_strjoin(full_env, old_pwd);
	i = 0;
	while (data->c_env[i] != NULL)
	{
		if (ft_strncmp(data->c_env[i], "OLDPWD", 6) == 0)
		{
			data->c_env[i] = full_env;
			break ;
		}
		i++;
	}
	data->c_env[i] = full_env;
}

void	my_cd(t_cmd *cmd, int i, t_data *data, int j)
{
	char	*home_dir;
	int		check;
	char 	*old_pwd;

	check = 0;
	home_dir = my_getenv("HOME", data);
	if (!cmd[i].args[j + 1] || cmd[i].args[j + 1][0] == '\0')
	{
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
		}
	}
	else
	{
		old_pwd = get_old_pwd();
		export_old_pwd(old_pwd, data);
		check = chdir(cmd[i].args[j + 1]);
		export_pwd(data);
	}
	if (check != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		data->new_st = 1;
		perror(cmd[i].args[j + 1]);
	}
}
