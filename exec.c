/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:26:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/21 17:23:24 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**alloc_pipe_fds(int pipe_amt)
{
	int	i;
	int	**p_fd;

	i = 0;
	//error message when reached the limit....but what is the limit??
	p_fd = malloc(sizeof(int *) * pipe_amt);
	while (i < pipe_amt)
	{
		p_fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (p_fd);
}

int	pipex(t_infra *shell, t_cmd *cmds, t_env **env_list)
{
	int	i;
	int	pid;

	i = 0;
	// printf("id of command in the beginning = %d\n", (*cmds)->cmd_id);
	//printf("pipe_len = %d\n", shell->pipe_len);
	if (shell->pipe_len > 0) //make sure what pipe_len is
		pipe(shell->pfd[0]);
	while (i < (shell->pipe_len + 1))
	{
		if ((i + 1) < shell->pipe_len)
		{
			printf("i = %d\n", i);
			printf("i + 1 = %d\n", i + 1);
			pipe(shell->pfd[i + 1]);
		}
		pid = process(cmds, i, shell, env_list);
		i++;
	}
	if (heredoc_exist(shell, cmds))
		unlink("temp");
	return (pid);
}
