/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:59 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_unset(t_string_array av)
{
	t_env	*env_var;
	t_env	*tmp;
	int		i;

	i = 1;
	env_var = g_command.env_var;
	if (av[1] == NULL)
	{
		print_err(2, "unset", av[i]); //not enough arguments
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
