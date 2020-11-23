/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:47 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 23:46:14 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char *str)
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

void	ms_export(char *param)
{
	t_env	*buf;

	if ((buf = create_env(param)))
		if (!(ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(buf))))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
}
