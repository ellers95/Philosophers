/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:35:36 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 18:27:34 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->attributes->number_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		ft_usleep(philo->attributes->time_to_die + 1);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	update_last_meal(philo);
	ft_usleep(philo->attributes->time_to_eat);
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->attributes->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}
