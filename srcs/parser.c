/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:22 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/13 18:09:38 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		find_quotes(char line, char flag)
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

char	*ft_sep(char *c)
{
	if (*c == ';')
		return (";");
	if (*c == '|')
		return ("|");
	if (*c == '<')
	{
		if (*(c + 1) == '<')
			return ("<<");
		return ("<");
	}
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (">>");
		return (">");
	}
	return (0);
}

// ssize_t		parsing_sep(t_dl_list	*lst, char *line)
// {
// 	size_t		count_end;
// 	char		*sep_res;
// 	char		flag;

// 	flag = 0;
// 	count_end = -1;
// 	while (line[++count_end])
// 	{
// 		flag = find_quotes(line[count_end], flag);
// 		if (!flag)
// 			if ((sep_res = ft_sep(&line[count_end])))
// 			{
// 				lst = ft_dl_lstlast(lst);
// 				lst->content = ft_strncut(line, count_end - 1);
// 				if (count_end > 0)
// 					ft_dl_lstadd_back(&lst, ft_dl_lstnew(sep_res));
// 				return (count_end);
// 			}
// 	}
// 	return (-1);
// }

t_dl_list	*parsing(char *line)
{
	t_dl_list	*lst;
	ssize_t		count_end;
	char		*sep_res;
	char		flag;

	if (!line)
		return (NULL);
	lst = NULL;
	while (*line)
	{
		line = ft_strpass(line, " ");
		flag = 0;
		count_end = -1;
		while (line[++count_end])
			if (!(flag = find_quotes(line[count_end], flag)))
				if ((sep_res = ft_sep(&line[count_end])))
				{
					if (count_end <= 0)
						return (NULL);
					if (!ft_dl_lstadd_back(&lst,
							ft_dl_lstnew(ft_strncut(line, count_end - 1))) ||
						!ft_dl_lstadd_back(&lst, ft_dl_lstnew(sep_res)))
						error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
					lst = ft_dl_lstlast(lst);
					break ;
				}
		if (!line[count_end + 1])
			break ;
		line += count_end + 1;
	}
	if (!ft_dl_lstadd_back(&lst, ft_dl_lstnew(ft_strdup(line))))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	return (ft_dl_lstfirst(lst));
}
