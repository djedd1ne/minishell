/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:20:25 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 18:55:51 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	chck_quote(char occur)
{
	int	*condition;

	condition = &g_command.terminated;
	if (occur == QUOTE && *condition == QUOTE)
		*condition = 0;
	else if (occur == QUOTE && *condition == 0)
		*condition = QUOTE;
	if (occur == DQUOTE && *condition == DQUOTE)
		*condition = 0;
	else if (occur == DQUOTE && *condition == 0)
		*condition = DQUOTE;
	return (*condition);
}

int	chck_termination(t_string cmd)
{
	t_string	pipe_pos;

	pipe_pos = ft_strchr(cmd, PIPE);
	g_command.terminated = 0;
	while (*cmd)
	{
		chck_quote(*cmd);
		cmd++;
	}
	if (chck_quote(*cmd) != 0 || (pipe_pos && *(pipe_pos + 1) == 0
			&& ft_strlen(cmd) >= 2))
		return (0);
	else
		return (1);
}

void	del_tok(void)
{
	t_token	*tok;
	t_token	*n_tok;

	tok = g_command.token;
	while (tok)
	{
		n_tok = tok->next;
		if (n_tok && n_tok->val == NULL)
			tok->next = n_tok->next;
		else
			tok = tok->next;
	}
}

void	print_tok(void)
{
	t_token	*tok;

	tok = g_command.token;
	while (tok)
	{
		printf("token\t");
		printf("%d: %s\n", tok->type, tok->val);
		tok = tok->next;
	}
}

int		param_len(t_string str)
{
	int	len;

	len = 0;
	if (str[0] == QMARK)
		return (1);
	if (str[0] != '_' && !(ft_isalpha(str[0])))
		return (0);
	while (str[len] == '_' || ft_isalnum(str[len]))
		len++;
	return (len);
}
