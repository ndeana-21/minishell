/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:42:38 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/15 16:10:53 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_pwd(char *argv)
{
	int i;
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

t_dl_list	*find_env(char *name)
{
	t_dl_list	*tmp_env;

	tmp_env = g_envlst;
	while (tmp_env)
	{
		if (ft_strsame(((t_env *)tmp_env->content)->name, name))
			return (tmp_env);
		tmp_env = (t_dl_list *)tmp_env->next;
	}
	return (NULL);
}

t_env		*create_env(char *str)
{
	size_t	count;
	t_env	*data;

	count = -1;
	if (!(data = malloc(sizeof(t_env))))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	while (str[++count])
		if (ft_strchr("=", str[count]))
		{
			str[count] = 0;
			if (!(data->val = ft_strdup(&(str[count + 1]))) ||
				!(data->name = ft_strdup(str)))
				error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
			break ;
		}
	return (data);
}

/*
** NEW
*/


/*
**	where	- place where it will insert sample
**	insted	- count of letters that will erase after "where"
*/
char	*ft_strreplace(char *str, char *sample, size_t where, size_t insted)
{
	char	*new;
	ssize_t	count;

	if (!(new = ft_calloc(sizeof(char),
		ft_strlen(str) + ft_strlen(sample) - insted)))
		return (NULL);
	count = -1;
	while ((++count < where) && *str)
	{
		new[count] = *str;
		str++;
	}
	while (*sample)
	{
		new[count++] = *sample;
		sample++;
	}
	while (insted-- && *str)
		str++;
	while (*str)
	{
		new[count++] = *str;
		str++;
	}
	return (new);
}

char	*make_dollar(char *str, size_t *insted)//FIXME нужно протестить
{
	char	*buf;
	char	*ret;
	size_t	count;

	if (!str)
		return (NULL);
	count = 0;
	*insted = count;
	if (str[count] == '?')
		return (ft_itoa(g_error));
	while (str[++count])
		if (!(ft_isalnum(str[count])))
			break ;
	buf = ft_strncut(str + 1, count - 1);
	ret = ((t_env *)(find_env(buf)->content))->val;
	free (buf);
	*insted = count;
	return (ret);
}

void	ms_dollar(char **str)
{
	char	*chr;
	char	*buff;
	char	*new;
	size_t	insted;

	while (chr = ft_strchr(*str, '$'))
	{
		insted = 0;
		buff = make_dollar(chr, &insted);
		if (!(new = ft_strreplace(*str, buff, (chr - *str), insted)))
			error_exit (ERROR_NUM_MALLOC, ERROR_MALLOC);
		free (*str);
		*str = new;
	}
}
