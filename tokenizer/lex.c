/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:36:38 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 19:30:51 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lex(t_string cmd)
{
	t_string	str;
	t_string	quote;

	str = ft_strdup(cmd);
	g_command.terminated = 0;
	str = ft_strtrim(str, " \t\n");
	while (!chck_termination(str))
	{
		quote = readline("> ");
		if (quote)
			str = ft_strjoin(str, ft_strdup(quote));
		else
			break ;
		free(quote);
	}
	if (!*str)
		return (1);
	tokenizer(str);
	parameter_exp();
	manage_quotes();
	tok_oper();
	del_tok();
	return (chck_error());
}
