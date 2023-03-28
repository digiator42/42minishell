/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/28 17:51:54 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_int_array(int **int_array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(int_array[i]);
		i++;
	}
	free(int_array);
}

/* void	free_cmds(char **cmds)
{
	char	**tmp;

	tmp = cmds;
	while (*cmds)
		free(*cmds++);
	free(tmp);
} */

void	free_env_list(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while (*env_list != NULL)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free(temp->var);
		free(temp->value);
		free(temp);
	}
	free (*env_list);
}

void	free_shell_cmds_in_child(t_infra *shell, t_cmd *cmds)
{
	//int	j;

<<<<<<< HEAD
	//j = 0;
	/* while (j < (shell->pipe_len + 1))
	{
		//free(cmds[j].main);
=======
	j = 0;
	(void)cmds;
	while (j < (shell->pipe_len + 1))
	{
		// free(cmds[j].main);
>>>>>>> 67f64a37912ab9736f4371a6ac7d74eb52d2bfeb
		//free_char_array(cmds[j].tmp_cmd);
		//free_char_array(cmds[j].cmd);
		//free(cmds[j].p);
		//free(cmds[j].red->file);
		//free(cmds[j].red);
		j++;
<<<<<<< HEAD
	} */
	if (cmds)
		free(cmds);
	free(shell->rd);
	//free(shell->trim_rd);
=======
	}
	// free(cmds);
>>>>>>> 67f64a37912ab9736f4371a6ac7d74eb52d2bfeb
	// free_char_array(shell->cmds);
	free_char_array(shell->env_arr);
	free_env_list(&shell->env_list);
	if (shell->pfd)
		free_int_array(shell->pfd, shell->pipe_len);
	//free(shell);
}

void	free_structs(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd->cmd_cnt)
	{
		if(cmd[i].red_len)
		{
			j = -1;
			while (++j < cmd[i].red_len)
				free(cmd[i].red[j].file);
			free(cmd[i].red);
		}
		free_char_array(cmd[i].cmd);
		i++;
	}
	free(cmd);
}
