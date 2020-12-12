/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:42:38 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/11 13:43:42 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_dollar(char *str, size_t *insted)
{
	char		*buf;
	char		*ret;
	size_t		count;
	t_dl_list	*tmp;

	if (!str || !*str)
		return (ft_strdup(""));
	count = 0;
	if (str[count + 1] == '?')
	{
		*insted = *insted + 2;
		return (ft_itoa(g_exit));
	}
	while (str[++count])
		if (!(ft_isalnum(str[count])))
			break ;
	if (count <= 1)
		return (NULL);
	buf = ft_strncut(str + 1, count - 1);
	*insted = count;
	if (!(tmp = find_env(buf)) || !(((t_env *)tmp->content)->val))
		return (ft_strdup(""));
	ret = ft_strdup(((t_env *)tmp->content)->val);
	free(buf);
	return (ret);
}

void		ms_dollar(char **str)
{
	char	*buff;
	char	*new;
	size_t	insted;
	ssize_t	i;

	i = -1;
	insted = 0;
	while ((*str)[++i])
	{
		if (((*str)[i] == '\''))
			insted = insted == -1ul ? 0 : -1;
		if (!insted)
			if ((*str)[i] == '$')
			{
				insted = 0;
				if (!(buff = make_dollar(&((*str)[i]), &insted)))
					continue ;
				if (!(new = ft_strreplace(*str, buff, i, insted)))
					error_exit(EXIT_FAILURE, ERROR_MALLOC);
				i += ft_strlen(buff) - 1;
				ft_strdel(&buff);
				ft_strdel(str);
				*str = new;
			}
	}
}

void		ft_freestrs(char **str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}
