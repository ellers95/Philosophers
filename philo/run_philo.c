/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:20:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/31 14:48:44 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_philo(void *this)
{
	t_philo	*philo;

	philo = (t_philo *)this;
	if (philo->id % 2 && philo->attributes->number_of_philos != 1)
		ft_usleep(philo->attributes->time_to_eat / 2, philo);
	run_philo_loop(philo);
	return (NULL);
}

void	run_philo_loop(t_philo *philo)
{
	if (philo->attributes->number_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		ft_usleep(philo->attributes->time_to_die + 1, philo);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	while (1)
	{
		if (run_check_death(philo))
			return ;
		eat(philo);
		if (run_check_death(philo))
			return ;
		ft_sleep(philo);
		if (run_check_death(philo))
			return ;
		think(philo);
	}
}

int	run_check_death(t_philo *philo)
{
	int	death_flag;

	pthread_mutex_lock(philo->death);
	death_flag = *philo->death_flag;
	pthread_mutex_unlock(philo->death);
	return (death_flag);
}
