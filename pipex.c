/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:51:38 by abel-bou          #+#    #+#             */
/*   Updated: 2022/05/29 15:41:10 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4))
		i++;
    if (!env[i])
        return (NULL);
	path = &env[i][5];
	return (path);
}

char	*check_cmd(t_var *var, char *cmd)
{
	int		i;

	var->cmd = ft_split(cmd, ' ');
	i = 0;
	while (var->paths[i])
	{
		var->paths[i] = ft_strjoin(var->paths[i], "/");
		var->path_cmd = ft_strjoin(var->paths[i], var->cmd[0]);
		if (access(var->path_cmd, F_OK) == 0)
			return (var->path_cmd);
		i++;
	}
	cmd = var->cmd[0];
	if (access(cmd, F_OK) == 0)
		return (cmd);
	ft_err("command not found");
	return (0);
}

void	first_proccess(t_var *var, char **av)
{
	ft_open_fd(var, av);
	dup2(var->fd[0], 0);
	dup2(var->pi[1], 1);
	close(var->pi[0]);
	close(var->pi[1]);
	execve(check_cmd(var, av[2]), var->cmd, NULL);
}

void	second_proccess(t_var *var, char **av)
{
	var->fd[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0700);
	dup2(var->pi[0], 0);
	dup2(var->fd[1], 1);
	close(var->pi[1]);
	close(var->pi[0]);
	execve(check_cmd(var, av[3]), var->cmd, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_var	*var;

	if (ac != 5)
		ft_err("There is a problem in arguments");
	var = NULL;
	var = malloc(sizeof(t_var));
	if (!var)
		return (0);
	var->line_paths = find_path(env);
    if (!var->line_paths)
        return(0);
	var->paths = ft_split(var->line_paths, ':');
	if (pipe(var->pi))
		return (0);
	var->pid[0] = fork();
	if (var->pid[0] == 0)
		first_proccess(var, av);
	else
		var->pid[1] = fork();
	if (var->pid[1] == 0)
		second_proccess(var, av);
	ft_close_wait(var);
	return (1);
}
