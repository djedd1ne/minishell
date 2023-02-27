/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:22:46 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/24 21:16:42 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(int ac)
{
	if (ac == 1)
	{
		display_env("env");
		return (0);
	}
	return (1);
}
/*
int main(int ac, t_string_array av, t_string_array envp)
{
	split_env(envp);
	if (av == NULL)
		return 0;
	ft_env(ac);
	return (0);
}*/