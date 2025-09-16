/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:12:31 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:22:26 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_check(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "ECHO"))
		return (ECHO);
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "CD"))
		return (CD);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "PWD"))
		return (PWD);
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "EXPORT"))
		return (EXP);
	if (!ft_strcmp(str, "unset") || !ft_strcmp(str, "UNSET"))
		return (UNST);
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "ENV"))
		return (ENV);
	if (!ft_strcmp(str, "exit") || !ft_strcmp(str, "EXIT"))
		return (EXIT);
	if (!ft_strcmp(str, "./minishell"))
		return (DEF);
	return (FALSE);
}

void	ft_exec_built(t_data *data, char *input)
{
	int	builtin;

	builtin = ft_builtin_check(input);
	if (builtin == CD)
		ft_cd(data, NULL, NULL);
	else if (builtin == ECHO)
		ft_echo(data);
	else if (builtin == ENV)
		ft_env(data);
	else if (builtin == EXP)
		ft_export(data, NULL, 0);
	else if (builtin == EXIT)
		ft_exit(data);
	else if (builtin == PWD)
		ft_pwd(data);
	else if (builtin == UNST)
		ft_unset(data);
	else if (builtin == DEF)
		data->lvl++;
}

int	ft_is_env_builtin(char *input)
{
	int	builtin;

	builtin = ft_builtin_check(input);
	if (builtin == CD)
		return (TRUE);
	else if (builtin == EXP)
		return (TRUE);
	else if (builtin == EXIT)
		return (TRUE);
	else if (builtin == UNST)
		return (TRUE);
	return (FALSE);
}

int	ft_nonenv_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "ECHO"))
		return (ECHO);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "PWD"))
		return (PWD);
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "ENV"))
		return (ENV);
	if (!ft_strcmp(str, "exit") || !ft_strcmp(str, "EXIT"))
		return (EXIT);
	return (FALSE);
}
