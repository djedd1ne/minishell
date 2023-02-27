/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 00:38:46 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 20:53:57 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	split_env(t_string_array envp)
{
	t_string_array	mat;
	t_env			*env_var;

	g_command.env_var = check_malloc(sizeof(t_env));
	env_var = g_command.env_var;
	while (*envp)
	{
		mat = ft_split(*envp, '=');
		env_var->name = mat[0];
		env_var->val = mat[1];
		env_var->next = check_malloc(sizeof(t_env));
		if (*(envp + 1) == NULL)
			env_var->next = NULL;
		else
			env_var = env_var->next;
		envp++;
	}
	return (0);
}

void	display_env(t_string str)
{
	t_env	*env_var;

	env_var = g_command.env_var;
	if (!(ft_strncmp(str, "env", 4)))
	{
		while (env_var)
		{
			printf("%s=%s\n", env_var->name, env_var->val);
			env_var = env_var->next;
		}
	}
}

t_string	get_var(t_string name)
{
	t_env	*env_var;

	env_var = g_command.env_var;
	while (env_var)
	{
		if (!(ft_strcmp(env_var->name, name)))
			return (env_var->val);
		env_var = env_var->next;
	}
	return (NULL);
}
