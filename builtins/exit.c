/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:49 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(int ac, t_string_array av)
{
	int	i;

	i = 0;
	if (ac > 2)
		print_err(5, "exit", "too many arguments");
	if (ac == 2)
	{
		while (av[1][i])
		{
			if (ft_isdigit(av[1][i] == 0))
			{
				print_err(5, "exit", "numeric argument required");
				exit (255);
			}
			i++;
		}
		exit(ft_atoi(av[1]) % 256);
	}
	else
		exit(g_command.exit_status);
	return (convert_exit());
}
