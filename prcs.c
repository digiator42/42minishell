/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/17 06:38:56 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	process(t_cmd *cmd, int i, t_exec *exec)
{
	int		pid;
	char	**env_arr;

	if (ft_strcmp(cmd->main, "exit") == 0 || ft_strcmp(cmd->main, "cd") == 0
		|| ft_strcmp(cmd->main, "export") || ft_strcmp(cmd->main, "unset") == 0)
		ft_built_in(cmd->main, cmd->cmd_args, &(exec->env_list));
	else
	{
		pid = fork();
		if (pid_error(pid) == 0)
		{
			env_arr = list_to_array(&(exec->env_list));
			if (ft_strrchr(cmd->main, '/'))
				cmd->path = cmd->main;
			else
				cmd->path = check_path(exec->path_array, ft_strjoin("/", cmd->main));
			ft_dup2(cmd->rds);
			if (file_rd_exist(cmd->rds, 0, 1) == 0)
				dup2(exec->pfd[i][0], STDIN_FILENO);
			if (file_rd_exist(cmd->rds, 2, 3) == 0)
				dup2(exec->pfd[i + 1][1], STDOUT_FILENO);
			close_fds(exec->pfd[i][0], exec->pfd[i][0],
				exec->pfd[i + 1][0], exec->pfd[i + 1][1]);
			mt_arg_error(cmd, env_arr, exec);
			if (cmd_is_built_in(cmd->main))
				ft_built_in(cmd->main, cmd->cmd_args, &(exec->env_list));
			else if (cmd->path == NULL || execve(cmd->path, cmd->cmd_args, env_arr) == -1)
				execve_error(exec, cmd);
		}
	}
	close_fds(exec->pfd[i][0], exec->pfd[i][0], -1, -1);
	return (pid);
}

int	ft_heredoc(char *delimeter)
{
	int		fd;
	char	*line;

	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(delimeter, line) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (fd);
}
