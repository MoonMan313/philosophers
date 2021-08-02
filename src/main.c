/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evelina <evelina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:41:58 by cdionna           #+#    #+#             */
/*   Updated: 2021/07/28 15:57:39 by evelina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clearing_memory(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		pthread_detach(data->threads[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philo);
	free(data->threads);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->exit);
	free(data);
}

static	int	error_exit(int error)
{
	if (error == 1)
		printf("Error: memory allocation\n");
	if (error == 2)
		printf("Error: failed to create mutexes\n");
	if (error == 3)
		printf("Error: failed to create the required number of threads\n");
	if (error == 4)
		printf("Enter: ./philo [number_of_philosophers] [time_to_die] %s %s\n", \
		"[time_to_eat] [time_to_sleep]", \
		"([number_of_times_each_philosopher_must_eat])");
	if (error == 5)
		printf("Enter: invalid parameter(s)\n");
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (error_exit(1));
	if ((argc != 5 && argc != 6))
		return (error_exit(4));
	if (check_and_init_param(data, (argc - 1), argv))
		return (error_exit(5));
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->num);
	if (!data->philo)
		return (error_exit(1));
	if (init_fork(data))
		return (error_exit(2));
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num);
	if (!data->threads)
		return (error_exit(1));
	if (start_of_threads(data))
		return (error_exit(3));
	pthread_mutex_lock(&data->exit);
	pthread_mutex_unlock(&data->exit);
	clearing_memory(data);
	return (0);
}
