/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:42:38 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 23:33:02 by ndeana           ###   ########.fr       */
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

void	error_exit(size_t error_code, char *error_text)
{
	if (error_text)
		ft_putendl_fd(error_text, 2);
	exit(error_code);
}

char	*make_dollar(char *str, size_t *insted)
{
	char	*buf;
	char	*ret;
	size_t	count;
	t_dl_list	*tmp;

	if (!str)
		return (ft_strdup(""));
	count = 0;
	if (str[count] == '?')
		return (ft_itoa(g_error));
	while (str[++count])
		if (!(ft_isalnum(str[count])))
			break ;
	buf = ft_strncut(str + 1, count - 1);
	*insted = count;
	if (!(tmp = find_env(buf)))
		return (ft_strdup(""));
	ret = ((t_env *)tmp->content)->val;
	free (buf);
	return (ret);
}

void	ms_dollar(char **str)
{
	char	*chr;
	char	*buff;
	char	*new;
	size_t	insted;

	while ((chr = ft_strchr(*str, '$')))
	{
		insted = 0;
		buff = make_dollar(chr, &insted);
		if (!(new = ft_strreplace(*str, buff, (chr - *str), insted)))
			error_exit (ERROR_NUM_MALLOC, ERROR_MALLOC);
		free (*str);
		*str = new;
	}
}
