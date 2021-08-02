/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evelina <evelina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 11:09:14 by evelina           #+#    #+#             */
/*   Updated: 2021/07/28 15:57:35 by evelina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_of_threads(t_data *data)
{
	int			i;
	t_philo		*p;
	pthread_t	check;

	i = 0;
	p = data->philo;
	data->time_start = get_time_now();
	while (i < data->num)
	{
		p[i].last_time_eat = data->time_start;
		if (pthread_create(&data->threads[i], NULL, \
			life_of_philosopher, &data->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&check, NULL, check_die, data))
		return (1);
	pthread_detach(check);
	return (0);
}

int	init_fork(t_data *data)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = data->philo;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* data->num);
	if (!data->forks || pthread_mutex_init(&data->print, NULL) \
		|| pthread_mutex_init(&data->exit, NULL))
		return (1);
	pthread_mutex_lock(&data->exit);
	while (i < data->num)
	{
		p[i].i = i;
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		p[i].left_fork = &data->forks[(i + 1) % data->num];
		p[i].right_fork = &data->forks[i];
		p[i].data = data;
		p[i].number_of_meals = data->count_eat;
		p[i].end = 0;
		i++;
	}
	return (0);
}

int	check_and_init_param(t_data *data, int count, char **param)
{
	int	i;

	i = 1;
	while (i != count)
	{
		if (check_param(param[count]))
			return (1);
		if (ft_atoi(param[count]) < 1)
			return (1);
		i++;
	}
	if (ft_atoi(param[1]) < 1 || ft_atoi(param[2]) < 1 || ft_atoi(param[3]) < 1 \
		|| ft_atoi(param[4]) < 1 || (count == 5 && ft_atoi(param[5]) < 1))
		return (1);
	data->num = ft_atoi(param[1]);
	data->die = ft_atoi(param[2]);
	data->eat = ft_atoi(param[3]);
	data->sleep = ft_atoi(param[4]);
	if (count == 5)
		data->count_eat = ft_atoi(param[5]);
	else
		data->count_eat = -1;
	return (0);
}
