/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:49:40 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 18:46:49 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_operator(char ch)
{
	if (ch == PIPE || ch == LESS || ch == GREATER)
		return (1);
	return (0);		
}

int	ft_space(char ch)
{
	if (ch == DSPACE || ch == DTAB || ch == NL)
		return (1);
	return (0);
}

int cmd_split(t_string cmd, t_string token, int condition)
{
	char	ch;

	ch = *(cmd + 1);
	if (ch == 0)
		return (1);
	if (*cmd == PIPE && *(cmd + 1) == PIPE)
		return (1);
	if (ft_space(ch) && condition == 0)
		return (1);
	if (!(ft_operator(*cmd)) && ft_operator(ch) && condition == 0)
		return (1);
	if (ft_operator(*cmd) && !(ft_operator(ch) && condition == 0))
		return (1);
	if ((ft_operator(*cmd) && (ch != *token || ft_strlen(token) >= 2)) && condition == 0)
		return (1);
	else
		return (0);
}

int ft_io(int modifier)
{
	if (modifier == GREATER || modifier == LESS
		|| modifier == GREATER_GREATER || modifier == LESS_LESS)
		return (1);
	return (0);
}

t_string	ft_strtok(t_string str)
{
	t_string	tok;

	tok = NULL;
	while (*str)
	{
		if ((ft_space(*str)) == 0)
		{
			tok = append_chr(tok, *str);
			if (ft_space(*(str + 1)))
				tok = append_chr(tok, DSPACE);
		}
		str++;
	}
	return (tok);
}
