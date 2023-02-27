/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:49:52 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 19:22:51 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_tok(t_string cmd, t_string val, int state)
{
	t_token	**toks;
	int		sp;
	int		tok_type;

	if (ft_operator(*cmd) && state == 0)
		tok_type = OPERATOR;
	else
		tok_type = TOKEN;
	if (state == DQUOTE)
		sp = 0;
	else
		sp = 1;
	toks = &g_command.token;
	while (*toks != NULL)
		toks = &((*toks)->next);
	*toks = check_malloc(sizeof(t_token));
	(*toks)->type = tok_type;
	(*toks)->val = val;
	(*toks)->split = sp;
	(*toks)->expanded = 0;
	(*toks)->error = 0;
	(*toks)->next = NULL;
	return (0);
}

int	tokenizer(t_string cmd)
{
	t_string	tok_val;
	int			state;

	tok_val = NULL;
	while (*cmd != 0)
	{
		state = chck_quote(*cmd);
		if (*cmd == DOLLAR && state == QUOTE)
			*cmd = GS;
		if (!ft_space(*cmd) || state != 0)
		{
			tok_val = append_chr(tok_val, *cmd);
			if (cmd_split(cmd, tok_val, state))
			{
				init_tok(cmd, tok_val, state);
				tok_val = NULL;
			}
		}
		cmd++;
	}
	return (0);
}

int	manage_quotes(void)
{
	t_token		*tok;
	t_string	managed;
	t_string	quote;
	int			state;

	tok = g_command.token;
	g_command.terminated = 0;
	while (tok)
	{
		managed = NULL;
		quote = tok->val;
		if (!(ft_strcmp(quote, "\"\"")))
			quote = " ";
		while (quote != 0 && *quote != 0)
		{
			state = chck_quote(*quote);
			if ((*quote != QUOTE && *quote != DQUOTE)
				|| (state != *quote && state != 0))
				managed = append_chr(managed, *quote);
			quote++;
		}
		tok->val = managed;
		tok = tok->next;
	}
	return (1);
}

int	tok_oper(void)
{
	t_token	*tok;

	tok = g_command.token;
	while (tok)
	{
		if (tok && tok->val && tok->type == OPERATOR)
		{
			if (!(ft_strncmp(tok->val, "|", 2)))
				tok->type = PIPE;
			else if (!(ft_strncmp(tok->val, "<", 2)))
				tok->type = LESS;
			else if (!(ft_strncmp(tok->val, "<<", 3)))
				tok->type = LESS_LESS;
			else if (!(ft_strncmp(tok->val, ">", 2)))
				tok->type = GREATER;
			else if (!(ft_strncmp(tok->val, ">>", 3)))
				tok->type = GREATER_GREATER;
			if (ft_redirection(tok) && tok->next && tok->next->type == TOKEN)
				tok->next->type = REDIR;
		}
		else if (tok->type != REDIR)
			tok->type = WORD;
		tok = tok->next;
	}
	return (0);
}
