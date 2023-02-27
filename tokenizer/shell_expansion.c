/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:41:07 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 19:09:51 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_string	expand(t_string tok, int pos, t_string var, int sp)
{
	t_string	bef;
	t_string	mid;
	t_string	aft;
	t_string	tmp;
	int			len;
	int			new_pos;

	len = param_len(var + 1);
	var = ft_substr(var, 1, len);
	if (*var == QMARK)
		tmp = ft_itoa(g_command.exit_status);
	else
		tmp = ft_strdup(get_var(var));
	if (tmp && sp)
		tmp = ft_strtok(tmp);
	var = tmp;
	bef = ft_substr(tok, 0, pos);
	new_pos = pos + len + 1; 
	aft = ft_substr(tok, new_pos, ft_strlen(tok));
	mid = ft_sjoin(bef, var);
	var = ft_sjoin(mid, aft);
	return (var);
}

void	replace_GS(void)
{
	t_token		*tok;

	tok = g_command.token;
	while (tok)
	{
		if (tok->type == TOKEN && ft_strchr(tok->val, GS))
			*(ft_strchr(tok->val, GS)) = DOLLAR;
		if (!(ft_strchr(tok->val, GS)))
			tok = tok->next;
	}
}

int		parameter_exp(void)
{
	t_token		*tok;
	t_string	var;
	t_string	exp;
	int			pos;

	tok = g_command.token;
	while (tok)
	{
		var = ft_strchr(tok->val, DOLLAR);
		pos = ft_pos(tok->val, DOLLAR);
		if (var && (param_len(var + 1) != 0 || *(var + 1) == QMARK))
		{
			exp = expand(tok->val, pos, var, tok->split);
			tok->val = exp;
		}
		if (!(ft_strchr(tok->val, DOLLAR))
			|| (param_len(ft_strchr(tok->val, DOLLAR) + 1) == 0))
			tok = tok->next;
	}
	replace_GS();
	return (0);
}
