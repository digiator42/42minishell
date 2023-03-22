/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:21:21 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/22 12:06:13 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i < start || i >= len)
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
}

int	red_count(char *str)
{
	int		i;
	int		num;
	char	quote;

	i = 0;
	num = 0;
	quote = 0;
	while (str[i])
	{
		is_quote(str[i], &quote);
		if (!quote && (str[i] == '>' || str[i] == '<'))
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			num++;
		}
		i++;
	}
	return (num);
}

int	get_file(char *str, char **file_name, int i)
{
	int		start;
	char	quote;

	start = i;
	quote = 0;
	while (str[i])
	{
		is_quote(str[i], &quote);
		if ((str[i] == ' ' || str[i] == '\t') && !quote)
			break ;
		i++;
	}
	(*file_name) = ft_substr(str, start, i - start);
	return (i);
}

void	get_flags(t_cmd *cmds, int *j, int *x, int *y)
{
	cmds->start = *x - 1;
	if (cmds->tmp_cmd[*j][*x + 1] == '>' \
		|| cmds->tmp_cmd[*j][*x + 1] == '<')
	{
		if (cmds->tmp_cmd[*j][*x + 1] == '>')
			cmds[*j].red[*y].flag = APPEND;
		else if (cmds->tmp_cmd[*j][*x + 1] == '<')
			cmds[*j].red[*y].flag = HERE_DOC;
		*x += 2;
	}
	else if (cmds->tmp_cmd[*j][*x] == '>')
	{
		cmds[*j].red[*y].flag = TRUNCATE;
		(*x)++;
	}
	else if (cmds->tmp_cmd[*j][*x] == '<')
	{
		cmds[*j].red[*y].flag = IN_FILE;
		(*x)++;
	}
}

void	init_infra(t_infra *shell, t_cmd *cmds, int j)
{
	int		y;
	int		x;
	int		len;
	char	quote;

	y = 0;
	x = -1;
	quote = 0;
	while (shell->cmds[j][++x])
	{
		if (shell->cmds[j][x] == '"' || shell->cmds[j][x] == '\'')
		{
			if (quote == 0)
				quote = shell->cmds[j][x];
			else if (quote == shell->cmds[j][x])
				quote = 0;
		}
		if ((shell->cmds[j][x] == '>' || shell->cmds[j][x] == '<') && !quote)
		{
			get_flags(cmds, &j, &x, &y);
			len = get_file(shell->cmds[j], &cmds[j].red[y].file, x + 1);
			clean_quotes(cmds[j].red[y].file);
			get_cmd(shell->cmds[j], cmds->start, len);
			x = cmds->start - 1;
			printf("file name : %s\n", cmds[j].red[y].file);
			printf("flag	  : %d\n", cmds[j].red[y].flag);
			y++;
		}
	}
}

void	infra_shell(t_infra *shell, t_cmd **tmp, int len)
{
	t_cmd	*cmds;
	int		h;
	int		j;

	h = 0;
	j = -1;
	*tmp = malloc(sizeof(t_cmd) * (len));
	cmds = *tmp;
	cmds->start = 0;
	cmds->tmp_cmd = shell->cmds;
	while (++j < len)
	{		
		cmds[j].red_len = red_count(shell->cmds[j]);
		if (cmds[j].red_len)
			cmds[j].red = malloc(sizeof(t_red) * cmds[j].red_len);
		init_infra(shell, cmds, j);
		cmds[j].cmd = ft_split_quote(shell->cmds[j], ' ');
		h = 0;
		while (cmds[j].cmd[h])
			clean_quotes(cmds[j].cmd[h++]);
		cmds[j].main = ft_strdup("");
		cmds[j].cmd_id = 0;
		h = 0;
		while (cmds[j].cmd[h])
		{
			if (h == 0)
			{
				free(cmds[j].main);
				cmds[j].main = cmds[j].cmd[h];
			}
			printf("in loop main[%d]->{%s}\n", j, cmds[j].main);
			printf("in loop CMD [%d]-> %s\n", j, cmds[j].cmd[h]);
			h++;
			cmds[j].cmd_id = j + 1;
		}
		cmds[j].cmd_len = h;
	}
}
