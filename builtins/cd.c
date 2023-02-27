/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:44:26 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ch_dir(int dir, t_string path, t_string old_pwd)
{
	dir = chdir(path);
	if (dir == -1)
	{
		print_err(3, "cd", path);
		g_command.exit_status = 1;
	}
	else
		add_var("OLDPWD", ft_strdup(old_pwd));
}

int	ft_cd(int ac, t_string_array av)
{
	t_string	path;
	t_string	old_pwd;
	int			dir;

	dir = 0;
	path = av[1];
	old_pwd = getcwd(NULL, 0);
	if (ac == 1)
		path = "~";
	if (!(ft_strncmp(path, "~", 2)))
		path = get_var("HOME");
	if (!(ft_strncmp(path, "-", 2)) || !(ft_strncmp(path, "--", 3)))
	{
		path = get_var("OLDPWD");
		if (path != NULL)
			printf("%s\n", path);
	}
	if (path != NULL && *path != 0)
		ch_dir(dir, path, old_pwd);
	free(old_pwd);
	return (1);
}
