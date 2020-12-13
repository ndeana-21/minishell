/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/13 17:36:08 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		flag_placer(char *content, char *flag)
{
	if (!(*flag))
	{
		if ((*flag = find_quotes((*content), *flag)))
		{
			ft_strmoveleft(content);
			return (1);
		}
	}
	else if (*flag)
		if (!(*flag = find_quotes((*content), *flag)))
		{
			ft_strmoveleft(content);
			return (1);
		}
	return (0);
}

char	**prepere_cmd(char *content)
{
	char	**cmd;
	char	flag;
	ssize_t	count;
	size_t	size;

	flag = 0;
	size = 0;
	count = 0;
	cmd = NULL;
	while (content[count])
	{
		if (!flag)
			if (content[count] == ' ')
			{
				// printf("%ld |%s|\n", count, content);
				if (!(cmd = ft_realloc(cmd, sizeof(char *) * ((size++) + 1))))
					error_exit(EXIT_FAILURE, ERROR_MALLOC);
				if (!(cmd[size - 1] = ft_strncut(content, count)))
					error_exit(EXIT_FAILURE, ERROR_MALLOC);
				content = ft_strpass((content += count), " ");
				count = -1;
			}
		if (flag_placer(&(content[count]), &flag))
			count--;
		count++;
	}
	if (*content)
		if (!(cmd = ft_realloc(cmd, sizeof(char *) * (size + 1))) ||
			!(cmd[size] = ft_strdup(content)))
			error_exit(EXIT_FAILURE, ERROR_MALLOC);
	return (cmd);
}

int		check_shell_cmd(char **cmd, char *cmd_check, void (func)(char **))
{
	if (ft_strsame(cmd[0], cmd_check))
		{
			func(&(cmd[1]));
			return (TRUE);
		}
	return (FALSE);
}

void	shell_brach_cmd(char *content)
{
	char **cmd;

	cmd = prepere_cmd(content);
	if (check_shell_cmd(cmd, MS_CD, ms_cd))
		return ;
	else if (check_shell_cmd(cmd, MS_ECHO, ms_echo))
		return ;
	else if (check_shell_cmd(cmd, MS_PWD, ms_pwd))
		return ;
	else if (check_shell_cmd(cmd, MS_UNSET, ms_unset))
		return ;
	else if (check_shell_cmd(cmd, MS_ENV, ms_env))
		return ;
	else if (check_shell_cmd(cmd, MS_EXPORT, ms_export))
		return ;
	else if (check_shell_cmd(cmd, MS_EXIT, ms_exit))
		return ;
	else
		ms_exec(cmd);
	ft_freestrs(cmd);
}

void	shell_branch_sep(t_dl_list *param)
{
	if (ft_strsame(param->content, ";"))
		ms_sep(param);
	else if (ft_strsame(param->content, "|"))
		ms_pipe(param);
	else if (ft_strsame(param->content, "<"))
		ms_redir(param, O_RDONLY, 0644, 0);
	else if (ft_strsame(param->content, ">"))
		ms_redir(param, O_WRONLY | O_CREAT | O_TRUNC, 0744, 1);
	else if (ft_strsame(param->content, ">>"))
		ms_redir(param, O_WRONLY | O_CREAT | O_APPEND, 0744, 1);
}

void	minishell(char **line)
{
	t_dl_list	*param;

	if (!(param = parsing(*line)))
	{
		ft_strdel(line);
		return ;
	}
	if (!(param->next))
		shell_brach_cmd((char *)param->content);
	while (param)
	{
		shell_branch_sep(param);
		param = (t_dl_list *)param->next;
	}
	param = ft_dl_lstclear(ft_dl_lstfirst(param), free);
	ft_strdel(line);
}
