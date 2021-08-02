/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evelina <evelina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:35:38 by cdionna           #+#    #+#             */
/*   Updated: 2021/07/28 15:21:38 by evelina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					i;
	int					end;
	int					number_of_meals;
	struct s_data		*data;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	unsigned long long	last_time_eat;
}		t_philo;

typedef struct s_data
{
	int					num;
	int					die;
	int					eat;
	int					sleep;
	int					count_eat;
	t_philo				*philo;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		exit;
	unsigned long long	time_start;
}			t_data;

int					start_of_threads(t_data *data);
int					init_fork(t_data *data);
int					check_and_init_param(t_data *data, int count, char **param);
int					check_param(char *str);
int					ft_atoi(const char *str);
void				print_action(unsigned long long time_start, \
t_philo *ph, const char *s);
void				*life_of_philosopher(void *philo);
void				*check_die(void *info);
unsigned long long	get_time_now(void);

#endif