/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 19:23:05 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_shell_command(char *content, char *command, void (*func)(char *))
{
	char	*buff;

	if (ft_strlen(command) == (size_t)ft_strcmp_reg(content, command))
		if (content[ft_strlen(command)] == '\0' ||
			content[ft_strlen(command)] == ' ')
		{
			buff = ft_strreplace(content, "", 0, ft_strlen(command));
			buff = ft_strpass_rev(buff, " ");
			ft_erasechr(buff, "\"\'");
			func(ft_strpass(buff, " "));
			free(buff);
			return (TRUE);
		}
	return (FALSE);
}

void	shell_brach_command(char *content)
{
	if (check_shell_command(content, MS_CD, ms_cd))
		return ;
	else if (check_shell_command(content, MS_ECHO, ms_echo))
		return ;
	else if (check_shell_command(content, MS_PWD, ms_pwd))
		return ;
	else if (check_shell_command(content, MS_UNSET, ms_unset))
		return ;
	else if (check_shell_command(content, MS_ENV, ms_env))
		return ;
	else if (check_shell_command(content, MS_EXPORT, ms_export))
		return ;
	else if (check_shell_command(content, MS_EXIT, ms_exit))
		return ;
	else
		ms_exec(content);
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

	param = parsing(*line);
	if (!(param->next))
		shell_brach_command((char *)param->content);
	while (param)
	{
		shell_branch_sep(param);
		param = (t_dl_list *)param->next;
	}
	param = ft_dl_lstclear(param, free);
	ft_strdel(line);
}
