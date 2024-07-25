/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_meal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:15:51 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 18:43:31 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal);
}
