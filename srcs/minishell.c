/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/21 17:13:17 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_pipe	*pipe_init(void)
{
	t_pipe	*pipe;

	if (!(pipe = ft_calloc(sizeof(t_pipe), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
}

void    minishell(char **line)
{
	t_pipe		*pipe;
    t_dl_list   *param;
    int         fd_count;
	
    param = parsing(*line);
    ft_strdel(line);
    if (!param)
        return ;
	pipe = pipe_init();
	shell_brach_red(param);
	run_cmd((char *)param->content);
	//shell_branch_sep(param, &fd_count);
    while (param->next)
    {
		shell_branch_sep(param, &fd_count);
		//shell_brach_cmd((char *)param->content);
        param = (t_dl_list *)param->next;
    }
    ft_dl_lstclear(param, free);
}
