/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:53:38 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 00:17:28 by mokoucha         ###   ########.fr       */
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
				break ;
			free(str);
		}
	}
	return (0);
}
