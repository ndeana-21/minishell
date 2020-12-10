/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 18:50:19 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/30 15:24:17 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strflip(char *s)
{
	unsigned int	i;
	unsigned int	j;
	char			buff;

	if (!*s)
		return ;
	i = 0;
	j = ft_strlen(s);
	while (i < --j)
	{
		buff = s[i];
		s[i] = s[j];
		s[j] = buff;
		i++;
	}
}

int		count_lenofnum(int num)
{
	if (num == -2147483648)
		return (11);
	else if (num < 0)
		return (count_lenofnum(num * -1) + 1);
	else if (num >= 10)
		return (count_lenofnum(num / 10) + 1);
	else
		return (1);
}

void	num_to_str(char *str, int num)
{
	unsigned int	sign;
	unsigned int	ui_num;
	unsigned int	i;

	sign = 0;
	i = 0;
	ui_num = (unsigned int)num;
	if (num < 0)
	{
		str[i++] = '-';
		sign++;
		ui_num = (unsigned int)(num * -1);
	}
	str[i] = '0';
	while (ui_num != 0)
	{
		str[i++] = (ui_num % 10) + '0';
		ui_num /= 10;
	}
	if (num == 0)
		str[i + 1] = '\0';
	else
		str[i] = '\0';
	ft_strflip(&str[sign]);
}

char	*ft_itoa(int num)
{
	char			*ret;

	if (!(ret = (char *)malloc(sizeof(char) * count_lenofnum(num) + 1)))
		return (NULL);
	num_to_str(ret, num);
	return (ret);
}
