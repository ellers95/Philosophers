/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:57:17 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 18:43:13 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroyforks(int i, t_philo *philos, t_mutex *mutex)
{
	while (i-- > 0)
	{
		pthread_mutex_destroy(&mutex->forks[i]);
		pthread_mutex_destroy(&philos[i].times_eaten_mutex);
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
	}
	free(mutex->forks);
}

int	initialize_forks_and_times_eaten_mutex(int number_of_philos, \
	t_mutex *mutex, t_philo *philos)
{
	int	i;

	i = 0;
	mutex->forks = malloc(sizeof(pthread_mutex_t) * number_of_philos);
	if (!mutex->forks)
		return (0);
	while (i < number_of_philos)
	{
		if (pthread_mutex_init(&mutex->forks[i], NULL) != 0 \
			|| pthread_mutex_init(&philos[i].times_eaten_mutex, NULL) != 0 \
			|| pthread_mutex_init(&philos[i].last_meal_mutex, NULL) != 0)
		{
			destroyforks(i, philos, mutex);
			return (0);
		}
		i++;
	}
	return (1);
}

int	initialize_death_and_print_mutex(t_mutex *mutex, t_philo *philos)
{
	if (pthread_mutex_init(&mutex->death, NULL) != 0)
	{
		destroyforks(philos->attributes->number_of_philos, philos, mutex);
		return (0);
	}
	if (pthread_mutex_init(&mutex->print, NULL) != 0)
	{
		pthread_mutex_destroy(&mutex->death);
		destroyforks(philos->attributes->number_of_philos, philos, mutex);
		return (0);
	}
	return (1);
}

int	initialize_mutex(int number_of_philos, t_mutex *mutex, t_philo *philos)
{
	if (!initialize_forks_and_times_eaten_mutex(number_of_philos, \
		mutex, philos))
		return (0);
	if (!initialize_death_and_print_mutex(mutex, philos))
		return (0);
	return (1);
}

int	destroy_mutex(int number_of_philos, t_mutex *mutex, t_philo *philos)
{
	destroyforks(number_of_philos, philos, mutex);
	pthread_mutex_destroy(&mutex->death);
	pthread_mutex_destroy(&mutex->print);
	return (1);
}
