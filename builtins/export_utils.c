/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:11:23 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 21:05:02 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*get_env(t_string name)
{
	t_env	*env_var;
	int		len;

	len = ft_strlen(name) + 1;
	env_var = g_command.env_var;
	while (env_var != NULL)
	{
		if (!(ft_strncmp(env_var->name, name, len)))
			return (env_var);
		env_var = env_var->next;
	}
	return (NULL);
}

void	name_is_set(t_string name, t_string val)
{
	t_env	*current_env;

	current_env = get_env(name);
	if (current_env && val)
		current_env->val = val;
}

int	add_var(t_string name, t_string val)
{
	t_env	*element;

	if (get_env(name) != NULL)
		name_is_set(name, val);
	else
	{
		element = g_command.env_var;
		while (element && element->next)
			element = element->next;
		element->next = check_malloc(sizeof(t_env));
		element = element->next;
		element->name = name;
		element->val = val;
		element->next = NULL;
	}
	return (0);
}

t_string_array	list_to_array(void)
{
	t_env			*env_var;
	t_string_array	envp;
	int				i;
	int				len;

	i = 0;
	len = 0;
	env_var = g_command.env_var;
	while (env_var && ++len)
		env_var = env_var->next;
	env_var = g_command.env_var;
	envp = check_malloc(sizeof(char *) * (len + 1));
	envp[len] = NULL;
	while (i < len)
	{
		if (env_var->val)
			envp[i] = ft_strjoin(ft_strjoin(env_var->name, "="), env_var->val);
		else
			envp[i] = ft_strdup(env_var->name);
		env_var = env_var->next;
		i++;
	}
	return (envp);
}

void	sort_env(t_string_array *envp)
{
	t_string	tmp;
	int			i;
	int			j;

	i = 0;
	while ((*envp)[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			if (ft_strcmp((*envp)[i], (*envp)[j]) < 0)
			{
				tmp = (*envp)[i];
				(*envp)[i] = (*envp)[j];
				(*envp)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
