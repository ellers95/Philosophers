/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:34:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/31 18:37:49 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time_to_sleep, t_philo *philo)
{
	size_t	start;
	size_t	dead;

	pthread_mutex_lock(&philo->last_meal_mutex);
	dead = philo->last_meal + philo->attributes->time_to_die;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	start = get_time_ms();
	while ((get_time_ms() - start) < time_to_sleep && get_time_ms() < dead)
		usleep(100);
}

int	check_death(t_philo *philo)
{
	size_t	current_time;
	size_t	time_since_last_meal;
	size_t	time_to_die;

	current_time = get_time_ms();
	time_to_die = (size_t)(philo->attributes->time_to_die);
	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_last_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (time_since_last_meal > time_to_die)
	{
		pthread_mutex_lock(philo->death);
		*philo->death_flag = 1;
		pthread_mutex_unlock(philo->death);
		pthread_mutex_lock(philo->print);
		printf("%zu %d %s\n", get_time_ms() - philo->attributes->start_time, \
			philo->id, "died");
		pthread_mutex_unlock(philo->print);
		return (1);
	}
	return (0);
}

int	get_meal_count(t_philo *philo)
{
	int	mealcount;

	pthread_mutex_lock(&philo->times_eaten_mutex);
	mealcount = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
	return (mealcount);
}

void	god(t_philo *philos, t_attributes *attributes)
{
	int	i;
	int	done_eating;

	ft_usleep(attributes->time_to_die, philos);
	while (1)
	{
		done_eating = 0;
		i = 0;
		while (i < attributes->number_of_philos)
		{
			if (check_death(&philos[i]))
				return ;
			if (attributes->number_of_meals != -1 && get_meal_count(&philos[i]) \
				>= attributes->number_of_meals)
				done_eating++;
			i++;
		}
		if (done_eating == attributes->number_of_philos)
		{
			pthread_mutex_lock(philos->death);
			*philos->death_flag = 1;
			pthread_mutex_unlock(philos->death);
			return ;
		}
	}
}
