/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:51 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	assign_env(t_string_array av)
{
	t_string	argument;
	t_string	name;
	t_string	value;

	value = NULL;
	while (++av && *av)
	{
		if (**av)
		{
			argument = ft_strchr(*av, '=');
			if (argument != 0)
			{
				name = ft_substr(*av, 0, argument - *av);
				value = ft_substr(*av, ft_strlen(*av) - ft_strlen(argument) + 1,
						ft_strlen(argument + 1));
			}
			else
				name = *av;
			if (!(ft_strncmp (value, "(null)", 7)))
					value = NULL;
			if (!(valid_var_name(name)))
				print_err(2, "export", name);
			else
				add_var(name, value);
		}
	}
	return (0);
}


void	export_envp(t_string_array envp)
{
	sort_env(&envp);
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

int		ft_export(int ac, t_string_array av)
{
	t_string_array	envp_arr;

	if  (ac > 1)
	{
		assign_env(av);
		av++;
		while (*av)
		{
			if (!(valid_var_name(*av)))
				return (1);
			av++;
		}
	}
	else
	{
		envp_arr = list_to_array();
		export_envp(envp_arr);
	}
	return (0);
}
