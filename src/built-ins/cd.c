/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:26:51 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:21:43 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data, char *owd, t_key *home)
{
	owd = getcwd(NULL, 0);
	if (!owd)
		return (perror("getcwd"));
	if (data->argc >= 2)
	{
		if (chdir(data->argv[1]) == 0)
			ft_update_dir(data, owd);
		else
			ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
	}
	else
	{
		if (ft_key_exist(data->env, "HOME"))
		{
			home = ft_get_keymap(data->env, "HOME");
			if (chdir(home->value) == 0)
				ft_update_dir(data, owd);
			else
				ft_putstr_fd("bash: cd: HOME not reachable\n", data->fdout);
		}
		else
			ft_putstr_fd("bash: cd: HOME not set\n", data->fdout);
	}
	free(owd);
}

void	ft_oldpwd(t_data *data, char *owd)
{
	if (!data || !owd)
		return ;
	if (ft_key_exist(data->env, "OLDPWD"))
		ft_update_map(data->env, owd, "OLDPWD");
	else
		ft_add_key(data->env, ft_new_key("OLDPWD", owd));
}

void	ft_update_dir(t_data *data, char *owd)
{
	char	*nwd;

	nwd = getcwd(NULL, 0);
	if (!nwd)
	{
		free(owd);
		data->status = ENOENT;
		return ;
	}
	if (ft_key_exist(data->env, "PWD"))
		ft_update_map(data->env, nwd, "PWD");
	else
		ft_add_key(data->env, ft_new_key("PWD", nwd));
	ft_oldpwd(data, owd);
	free (nwd);
	data->status = EXIT_SUCCESS;
}
