/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evelina <evelina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:31:51 by cdionna           #+#    #+#             */
/*   Updated: 2021/07/28 15:57:46 by evelina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*ft_isspase(const char *s)
{
	while (*s && (*s == ' ' || *s == '\t' || *s == '\v'
			|| *s == '\r' || *s == '\n' || *s == '\f'))
		++s;
	return ((char *)s);
}

int	check_param(char *str)
{
	str = ft_isspase(str);
	while (*str && *str < 58 && *str > 47)
		str++;
	str = ft_isspase(str);
	if (*str != '\0')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long	value;
	int			n_p;

	n_p = 1;
	value = 0;
	str = ft_isspase(str);
	if (*str == '-')
		n_p = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str > 47 && *str < 58)
	{
		value = value * 10 + (long long)(*str - 48);
		++str;
		if ((value > 2147483648 && n_p == -1) || \
			(value > 2147483647 && n_p == 1))
			return (-1);
	}
	return ((int)(n_p * value));
}

unsigned long long	get_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long long)(tv.tv_sec * 1000000 + tv.tv_usec));
}

void	print_action(unsigned long long time_start, t_philo *ph, const char *s)
{
	pthread_mutex_lock(&ph->data->print);
	if (ph->data->time_start != 0)
		printf("%lli %d %s", ((get_time_now() - time_start) / 1000), \
			(ph->i + 1), s);
	pthread_mutex_unlock(&ph->data->print);
}
