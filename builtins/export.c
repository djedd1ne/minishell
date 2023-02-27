/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:51 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 23:59:14 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
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
*/

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
		if (!valid_var_name(func1(av[i], NULL)))
		{
			print_err(2, "export", func1(av[i], NULL));
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
	if (av[1] == NULL)
	{
		print_sorted_env(g_command.env_var);
		return (0);
	}
	func2(av);
	while (++av && *av)
	{
		if (**av)
		{
			name = func1(*av, &value);
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
