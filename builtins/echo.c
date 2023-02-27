/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:42:31 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 20:45:42 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo_print(t_string_array argv, int n, int i)
{
	while (argv[i] != 0)
	{
		printf("%s", argv[i]);
		if (argv[++i])
			printf(" ");
	}
	if (!n)
		printf("\n");
}

int	ft_echo(t_string_array argv)
{
	int	argc;
	int	nflag;
	int	i;

	i = 1;
	argc = 0;
	nflag = 0;
	while (argv[argc] != 0)
		argc++;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	if (argv[1][0] == '-' && !(ft_strncmp("-", argv[1], 2)))
		i = 2;
	if (!(ft_strncmp("-n", argv[1], 3)))
	{
		nflag = 1;
		i = 2;
	}
	echo_print(argv, nflag, i);
	return (0);
}
