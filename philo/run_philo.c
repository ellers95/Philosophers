/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:20:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/16 15:32:20 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *run_philo(void *this)
{
    t_philo *philo;

    philo = (t_philo *)this;
    while (!philo->is_dead)
    {
        eat(philo);
        ft_sleep(philo);
        think(philo);
    }
    return (NULL);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    print_state(philo, "is eating");
    philo->last_meal = get_time_ms();
    ft_usleep(philo->attributes->time_to_eat);
    philo->times_eaten++;
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    ft_sleep(t_philo *philo)
{
    print_state(philo, "is sleeping");
    ft_usleep(philo->attributes->time_to_sleep);
}

void    think(t_philo *philo)
{
    print_state(philo, "is thinking");
}
