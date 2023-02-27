/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:53:38 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 21:09:59 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, t_string_array av, t_string_array envp)
{
	t_string	str;

	str = 0;
	if (ac == 1 && av[0])
	{
		session_init(envp);
		while (1)
		{
			session_refresh(envp);
			str = ft_prompt();
			if (str != NULL)
			{
				if (*str)
					add_history(str);
				if (ft_lex(str) != 6 && !ft_parser())
					executor();
				g_command.terminated = 0;
			}
			else
				break;
			free(str);
		}
	}
	return (0);
}
