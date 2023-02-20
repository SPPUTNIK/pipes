/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:32:33 by abel-bou          #+#    #+#             */
/*   Updated: 2022/05/29 15:40:29 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_wait(t_var *var)
{
	int	i;

	i = 0;
	close(var->fd[0]);
	close(var->fd[1]);
	close(var->pi[0]);
	close(var->pi[1]);
	waitpid(var->pid[0], NULL, 0);
	waitpid(var->pid[1], NULL, 0);
	while (var->paths[i])
	{
		free(var->paths[i]);
		i++;
	}
}

void	ft_open_fd(t_var *var, char **av)
{
	var->fd[0] = open(av[1], O_RDONLY);
	if (var->fd[0] == -1)
		ft_err("No such file or directory");
	if (access(av[1], R_OK))
		ft_err("Permission denied");
}
