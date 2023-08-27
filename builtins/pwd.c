/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:45:08 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 20:45:09 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_pwd(void)
{
	char c_dir[256];

	if (getcwd(c_dir, sizeof(c_dir)) != NULL)
		printf("%s\n", c_dir);
	else
		perror("minishell: pwd: ");
}
