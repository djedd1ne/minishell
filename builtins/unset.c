/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:59 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 23:56:14 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
int	ft_unset(t_string_array av)
{
	t_env	*env_var;
	t_env	*tmp;
	int		i;

	i = 1;
	env_var = g_command.env_var;
	if (av[1] == NULL)
	{
		print_err(2, "unset", av[i]);
		g_command.exit_status = 1;
	}
	while (av[i])
	{
		if (!(valid_var_name(av[i])))
		{
			print_err(2, "unset", av[i]);
			g_command.exit_status = 1;
		}
		if (!(ft_strcmp(av[i], env_var->name)))
			g_command.env_var = env_var->next;
		while (env_var != NULL)
		{
			tmp = env_var->next;
			if (tmp != NULL && !(ft_strcmp(av[i], tmp->name)))
				env_var->next = tmp->next;
			env_var = env_var->next;
		}
		i++;
	}
	return (g_command.exit_status);
}
*/

void	func1(t_env **env_var, char *var_name)
{
	t_env	*tmp;

	if (!ft_strcmp((*env_var)->name, var_name))
		*env_var = (*env_var)->next;
	else
	{
		tmp = *env_var;
		while (tmp->next != NULL)
		{
			if (!ft_strcmp(tmp->next->name, var_name))
			{
				tmp->next = tmp->next->next;
				return ;
			}
			tmp = tmp->next;
		}
	}
}

void	func2(t_string_array av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!valid_var_name(av[i]))
		{
			print_err(2, "unset", av[i]);
			g_command.exit_status = 1;
			return ;
		}
		i++;
	}
}

int	ft_unset(t_string_array av)
{
	t_env	*env_var;
	int		i;

	env_var = g_command.env_var;
	if (av[1] == NULL)
	{
		print_err(2, "unset", av[0]);
		g_command.exit_status = 1;
		return (g_command.exit_status);
	}
	func2(av);
	i = 1;
	while (av[i])
	{
		func1(&env_var, av[i]);
		i++;
	}
	g_command.env_var = env_var;
	return (g_command.exit_status);
}
