/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:35:36 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/31 17:56:40 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	update_last_meal(philo);
	ft_usleep(philo->attributes->time_to_eat, philo);
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->attributes->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}


// void	eat(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
//     {
//         // Even ID philosophers pick up the right fork first.
//         pthread_mutex_lock(philo->right_fork);
//         print_state(philo, "has taken a fork");
//         pthread_mutex_lock(philo->left_fork);
//     }
//     else
//     {
//         // Odd ID philosophers pick up the left fork first.
//         pthread_mutex_lock(philo->left_fork);
//         print_state(philo, "has taken a fork");
//         pthread_mutex_lock(philo->right_fork);
//     }
//     print_state(philo, "has taken a fork");
//     print_state(philo, "is eating");
//     // Update last meal time and increment the eat counter.
//     philo->last_meal = get_time_ms();
//     ft_usleep(philo->attributes->time_to_eat, philo);
//     pthread_mutex_lock(&philo->times_eaten_mutex);
//     philo->times_eaten++;
//     pthread_mutex_unlock(&philo->times_eaten_mutex);
//     // Release the forks after eating.
//     // pthread_mutex_unlock(philo->left_fork);
//     // pthread_mutex_unlock(philo->right_fork);
// 		if (philo->id % 2 == 0)
//     {
//         // Even ID philosophers pick up the right fork first.
//         pthread_mutex_unlock(philo->left_fork);
//         pthread_mutex_unlock(philo->right_fork);
//     }
//     else
//     {
//         // Odd ID philosophers pick up the left fork first.
// 		pthread_mutex_unlock(philo->right_fork);
//         pthread_mutex_unlock(philo->left_fork);

//     }
// }