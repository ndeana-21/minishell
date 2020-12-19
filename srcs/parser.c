/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:22 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/19 21:55:47 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			find_quotes(char line, char flag)
{
	if (!flag)
	{
		if (line == '\'')
			flag = '\'';
		else if (line == '"')
			flag = '"';
	}
	else if (line == flag)
		flag = 0;
	return (flag);
}

static char		*ft_sep(char *c)
{
	if (!c || !(*c))
		return (0);
	if (*c == ';')
		return (ft_strchr(";|<>", *(c + 1)) ? "-" : ";");
	else if (*c == '|')
		return (ft_strchr(";|<>", *(c + 1)) ? "-" : "|");
	else if (*c == '<')
		return (ft_strchr(";|>", *(c + 1)) ? "-" : "<");
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (ft_strchr(";|<>", *(c + 2)) ? "-" : ">>");
		return (ft_strchr(";|<", *(c + 1)) ? "-" : ">");
	}
	return (0);
}

static int		parsing_utilit_to_lst(char *line, t_dl_list **lst,
								ssize_t *count_end, char *sep_res)
{
	if ((*sep_res == '-') || (*count_end <= 0))
		return (0);
	if (!ft_dl_lstadd_back(lst, ft_dl_lstnew(ft_strncut(line, *count_end))))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	*count_end += ft_strlen(sep_res) - 1;
	if (!ft_dl_lstadd_back(lst, ft_dl_lstnew(ft_strdup(sep_res))))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	*lst = ft_dl_lstlast(*lst);
	return (1);
}

static ssize_t	parsing_utilit(char *line, t_dl_list **lst)
{
	ssize_t		count_end;
	char		*sep_res;
	char		flag;

	flag = 0;
	count_end = -1;
	while (line[++count_end])
		if (!(flag = find_quotes(line[count_end], flag)))
			if ((sep_res = ft_sep(&line[count_end])))
			{
				if (!(parsing_utilit_to_lst(line, lst, &count_end, sep_res)))
				{
					ft_putendl_fd(ERROR_SYNTAX, 2);
					*lst = ft_dl_lstclear(*lst, free);
					return (-1);
				}
				break ;
			}
	return (count_end);
}

static int		check_sep(char *str)
{
	if (ft_strsame(str, ";") || ft_strsame(str, "<") || ft_strsame(str, ">") ||
			ft_strsame(str, ">>") || ft_strsame(str, "|"))
		return (1);
	return (0);
}

t_dl_list		*parsing(char *line)
{
	t_dl_list	*lst;
	ssize_t		count_end;

	if (!line)
		return (NULL);
	lst = NULL;
	while (*line)
	{
		line = ft_strpass(line, " ");
		if (0 > (count_end = parsing_utilit(line, &lst)))
			return (lst);
		if (!line[count_end])
			break ;
		line += count_end + 1;
	}
	if (lst && check_sep((char *)lst->content) && !(*line))
	{
		ft_putendl_fd(ERROR_SYNTAX, 2);
		lst = ft_dl_lstclear(lst, free);
		return (lst);
	}
	if (!ft_dl_lstadd_back(&lst, ft_dl_lstnew(ft_strdup(line))))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	return (ft_dl_lstfirst(lst));
}
