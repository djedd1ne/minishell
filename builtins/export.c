/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:51 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 02:41:50 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_string	assign_env_part1(t_string arg, t_string *value)
{
	t_string	name;
	t_string	equals;

	equals = ft_strchr(arg, '=');
	if (equals != 0)
	{
		name = ft_substr(arg, 0, equals - arg);
		*value = ft_substr(arg, ft_strlen(arg) - ft_strlen(equals) + 1,
				ft_strlen(equals + 1));
	}
	else
		name = arg;
	if (!(ft_strncmp (*value, "(null)", 7)))
		*value = NULL;
	return (name);
}

void	assign_env_part2(t_string_array av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!valid_var_name(assign_env_part1(av[i], NULL)))
		{
			print_err(2, "export", assign_env_part1(av[i], NULL));
			g_command.exit_status = 1;
			return ;
		}
		i++;
	}
}

int	assign_env(t_string_array av)
{
	t_string	name;
	t_string	value;

	value = NULL;
	assign_env_part2(av);
	while (++av && *av)
	{
		if (**av)
		{
			name = assign_env_part1(*av, &value);
			add_var(name, value);
		}
	}
	return (g_command.exit_status);
}

void	export_envp(t_string_array envp)
{
	sort_env(&envp);
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

int	ft_export(int ac, t_string_array av)
{
	t_string_array	envp_arr;

	if (ac > 1)
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
