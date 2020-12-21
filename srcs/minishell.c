/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/21 21:24:32 by gselyse          ###   ########.fr       */
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

size_t	sizeof_content(char *content)
{
	char	flag;
	size_t	size;

	flag = 0;
	size = 0;
	while (*content)
	{
		if (!flag)
			if ((*content) == ' ')
				size++;
		flag = find_quotes(*content, flag);
		content++;
	}
	return (size);
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
	if (!(cmd = ft_calloc(sizeof(char *), sizeof_content(content) + 2)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	while (content[count])
	{
		if (!flag)
			if (ft_strchr(" ", content[count]))
			{
				if (!(cmd[size++] = ft_strncut(content, count)))
					error_exit(EXIT_FAILURE, ERROR_MALLOC);
				content = ft_strpass((content += count), " ");
				count = -1;
			}
		if (flag_placer(&(content[count > 0 ? count : 0]), &flag))
			count--;
		count++;
	}
	if (*content)
		if (!(cmd[size] = ft_strdup(content)))
			error_exit(EXIT_FAILURE, ERROR_MALLOC);
	return (cmd);
}

int		check_shell_cmd(char **cmd, char *cmd_check, void (func)(char **))
{
	if (ft_strlen(cmd_check) == (size_t)ft_strcmp_reg(cmd[0], cmd_check))
		{
			func(&(cmd[1]));
			ft_freestrs(cmd);
			return (TRUE);
		}
	return (FALSE);
}
/*
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
*/
void	shell_brach_red(t_dl_list *param)
{
	t_dl_list *tmp;

	tmp = param;
	while (tmp)
	{	
		if (ft_strsame(tmp->content, "<"))
       		ms_redir(tmp, O_RDONLY, 0644, 0);
    	else if (ft_strsame(tmp->content, ">"))
        	ms_redir(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744, 1);
    	else if (ft_strsame(tmp->content, ">>"))
        	ms_redir(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744, 1);
    	tmp = (t_dl_list *)tmp->next;
	}
}

void    shell_branch_sep(t_dl_list *param, int *fd_count)
{
    if (ft_strsame(param->content, ";"))
        ms_sep(param);
    else if (ft_strsame(param->content, "|"))
        ms_pipe(param, fd_count);
    //else if (ft_strsame(param->content, "<"))
     //   ms_redir(param, O_RDONLY, 0644, 0);
    //else if (ft_strsame(param->content, ">"))
    //    ms_redir(param, O_WRONLY | O_CREAT | O_TRUNC, 0744, 1);
    //else if (ft_strsame(param->content, ">>"))
    //    ms_redir(param, O_WRONLY | O_CREAT | O_APPEND, 0744, 1);
    param = param->next;
}

void		shell_brach_cmd(char *content)
{
	char **cmd;

	cmd = prepere_cmd(content);
	if (!cmd || !*cmd || !**cmd)
		ft_puterr(NULL, NULL, ERROR_SYNTAX, 127);
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

void    minishell(char **line)
{
    t_dl_list   *param;
    int         fd_count;
	
    param = parsing(*line);
    ft_strdel(line);
    if (!param)
        return ;
	shell_brach_red(param);
	shell_brach_cmd((char *)param->content);
	dup2(0, 1);
	//shell_branch_sep(param, &fd_count);
    while (param->next)
    {
		shell_branch_sep(param, &fd_count);
		//shell_brach_cmd((char *)param->content);
        param = (t_dl_list *)param->next;
    }
    ft_dl_lstclear(param, free);
}
