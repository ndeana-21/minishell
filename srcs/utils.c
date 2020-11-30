/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:42:38 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/30 23:26:07 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_pwd(char *argv)
{
	t_dl_list	*tmp;

	if (!(tmp = find_env("PWD")))
		return (NULL);
	free(((t_env *)tmp->content)->val);
	((t_env *)tmp->content)->val = argv;
	return (((t_env *)tmp->content)->val);
}

void		print_error(size_t error_code, char *error_text)
{
	if (error_text)
		ft_putendl_fd(error_text, 2);
	g_exit = error_code;
}

void	error_exit(size_t error_code, char *error_text)
{
	print_error(error_code, error_text);
	exit(error_code);
}

char	*make_dollar(char *str, size_t *insted)
{
	char	*buf;
	char	*ret;
	size_t	count;
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
	if (!(tmp = find_env(buf)))
		return (ft_strdup(""));
	ret = ft_strdup(((t_env *)tmp->content)->val);
	free (buf);
	return (ret);
}

void	ms_dollar(char **str)
{
	char	*chr;
	char	*buff;
	char	*new;
	size_t	insted;
	ssize_t	i;
	
	i = -1;
	while ((*str)[++i])
	{
		insted = 0;
		if ((*str)[i] == '$')
		{
			if (!(buff = make_dollar(&((*str)[i]), &insted)))
				continue ;
			if (!(new = ft_strreplace(*str, buff, i, insted)))
				error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
			i += ft_strlen(buff) - 1;
			ft_strdel(&buff);
			ft_strdel(str);
			*str = new;
		}
	}
	g_exit = 0;
}
//echo $test $USER $ $ $? test