/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evelina <evelina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 12:04:26 by evelina           #+#    #+#             */
/*   Updated: 2021/07/28 15:57:43 by evelina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_philo(t_philo *ph)
{
	static int	count_meals = 1;

	if (!ph->end &&\
	((get_time_now() - ph->last_time_eat)) >= \
			(unsigned long long)ph->data->die * 1000)
	{
		ph->number_of_meals = 0;
		print_action((ph->data->time_start), ph, "died\n");
		ph->data->time_start = 0;
		return (1);
	}
	if (ph->number_of_meals == 0 && !ph->end)
	{
		ph->end = 1;
		count_meals += 1;
		if (count_meals == ph->data->num)
		{
			printf("%lli %d times every philosopher has eaten!\n", \
			((get_time_now() - ph->data->time_start) / 1000), \
				ph->data->count_eat);
			ph->data->time_start = 0;
			return (1);
		}
	}
	return (0);
}

void	*check_die(void *info)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)info;
	while (1)
	{
		if (i == data->num)
			i = 0;
		if (check_philo(&data->philo[i]))
			break ;
		usleep(300);
		i++;
	}
	pthread_mutex_unlock(&data->exit);
	return (NULL);
}

static void	eating(t_philo *ph)
{
	print_action(ph->data->time_start, ph, "is eating\n");
	usleep(ph->data->eat * 1000);
	ph->last_time_eat = get_time_now();
	if (ph->data->count_eat != -1 || ph->number_of_meals != 0)
		ph->number_of_meals--;
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	*life_of_philosopher(void *philo)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)philo;
	data = ph->data;
	if (ph->i % 2 == 0 && ph->data->num != 1)
		usleep(data->eat * 1000);
	while (1)
	{
		pthread_mutex_lock(ph->right_fork);
		print_action(data->time_start, ph, "has taken a fork\n");
		pthread_mutex_lock(ph->left_fork);
		print_action(data->time_start, ph, "has taken a fork\n");
		eating(ph);
		if (ph->number_of_meals == 0)
			break ;
		print_action(data->time_start, ph, "is sleeping\n");
		usleep(data->sleep * 1000);
		print_action(data->time_start, ph, "is thinking\n");
		usleep ((data->die - data->eat - data->sleep) / 2);
	}
	return (NULL);
}
