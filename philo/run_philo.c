/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:20:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/17 15:31:38 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *run_philo(void *this)
{
    t_philo *philo;
    int     kill_switch;

    kill_switch = 0;
    //printf("run philo beginning\n");
    philo = (t_philo *)this;
    while (1)
    {
        
        pthread_mutex_lock(philo->death);
       // printf("before eating\n");
        if (philo->is_dead == 1)
            kill_switch = 1;
        pthread_mutex_unlock(philo->death);
        if (kill_switch == 1)
            return (NULL);
        eat(philo);
        pthread_mutex_lock(philo->death);
        if (philo->is_dead)
            kill_switch = 1;
        pthread_mutex_unlock(philo->death);
        if (kill_switch == 1)
            return (NULL);
        ft_sleep(philo);
        pthread_mutex_lock(philo->death);
        if (philo->is_dead)
            kill_switch = 1;
        pthread_mutex_unlock(philo->death);
        if (kill_switch == 1)
            return (NULL);
        think(philo);
    }
}

void    eat(t_philo *philo)
{
    if (philo->attributes->number_of_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        ft_usleep(philo->attributes->time_to_die + 1);
        philo->is_dead = 1;
        print_state(philo, "died");
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
    }
    print_state(philo, "has taken a fork");
    print_state(philo, "is eating");
    philo->last_meal = get_time_ms();
    ft_usleep(philo->attributes->time_to_eat);
    philo->times_eaten++;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
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
