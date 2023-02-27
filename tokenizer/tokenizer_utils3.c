/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:27:35 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirection(t_token *tok)
{
	int	tok_type;

	if (tok)
	{
		tok_type = tok->type;
		if (tok_type == GREATER || tok_type == GREATER_GREATER
				|| tok_type == LESS || tok_type == LESS_LESS)
				return (1);
	}
	return (0);
}

int	chck_str(void)
{
	int		n;
	t_token	*tok;

	n = 0;
	tok = g_command.token;
	while (tok && ++n)
	{
		if ((n == 1 && tok->type != WORD && !ft_redirection(tok))
			|| ((n == 1 && !tok->next && tok->type != WORD)))
		{
			tok->error = 1;
			return (print_err(6, "", tok->val));
		}
		else if (tok->type == PIPE && tok->next &&
			tok->next->type == PIPE)
			return (print_err(6, "", tok->val));
		tok = tok->next;
	}
	return (0);
}

int	chck_error(void)
{
	t_token	*tok;

	tok = g_command.token;
	chck_str();
	while (tok)
	{
		if (ft_redirection(tok) && tok->next && tok->next->type != REDIR)
		{
			tok->error = 1;
			return (print_err(6, "", tok->val));
		}
		else if (ft_redirection(tok) && (tok->next && ft_redirection(tok->next)))
		{
			tok->error = 1;
			return (print_err(4, "", tok->val));
		}
		tok = tok->next;
	}
	return (0);
}

t_string	ft_strndup(const t_string str, int n)
{
	t_string	p_str;
	int			len;

	p_str = NULL;
	len = ft_strlen(str);
	if (n < len)
		len = n;
	p_str = check_malloc(sizeof(char) * len + 1);
	ft_strlcpy(p_str, str, (len + 1));
	return (p_str);
}
