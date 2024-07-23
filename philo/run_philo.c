/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:20:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/23 16:43:54 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function runs the behavior of each philosopher.
void    *run_philo(void *this)
{
    t_philo *philo;
    int     kill_switch;

    kill_switch = 0;
    //printf("run philo beginning\n"); << DEBUGGING
    philo = (t_philo *)this;
    // If the philosopher's ID is odd, they wait a bit to prevent deadlock
    if (philo->id % 2)
        ft_usleep(philo->attributes->time_to_eat - 10);
    while (1)
    {
        // Check if the philosopher is dead
        pthread_mutex_lock(philo->death);
       // printf("before eating\n"); << DEBUGGING
        if (philo->is_dead == 1)
            kill_switch = 1;
        pthread_mutex_unlock(philo->death);
        // Exit the loop if the philosopher is dead
        if (kill_switch == 1)
            return (NULL);
        // The philosopher tries to eat
        eat(philo);
        // Check if the philosopher is dead again after eating
        pthread_mutex_lock(philo->death);
        if (philo->is_dead)
            kill_switch = 1;
        pthread_mutex_unlock(philo->death);
        if (kill_switch == 1)
            return (NULL);
        // The philosopher goes to sleep
        ft_sleep(philo);
        // Check if the philosopher is dead after sleeping
        pthread_mutex_lock(philo->death);
        if (philo->is_dead)
            kill_switch = 1;
        pthread_mutex_unlock(philo->death);
        if (kill_switch == 1)
            return (NULL);
         // The philosopher thinks
        think(philo);
    }
}

// This function handles the eating behavior of a philosopher.
void    eat(t_philo *philo)
{
    if (philo->attributes->number_of_philos == 1)
    {
        // If there's only one philosopher, they can never eat and will eventually die.
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        ft_usleep(philo->attributes->time_to_die + 1);
        philo->is_dead = 1;
        print_state(philo, "died");
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    else if (philo->id % 2 == 0)
    {
        // Even ID philosophers pick up the right fork first.
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
    }
    else
    {
        // Odd ID philosophers pick up the left fork first.
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
    }
    print_state(philo, "has taken a fork");
    print_state(philo, "is eating");
    // Update last meal time and increment the eat counter.
    philo->last_meal = get_time_ms();
    ft_usleep(philo->attributes->time_to_eat);
    philo->times_eaten++;
    // Release the forks after eating.
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

// This function handles the sleeping behavior of a philosopher.
void    ft_sleep(t_philo *philo)
{
    print_state(philo, "is sleeping");
    ft_usleep(philo->attributes->time_to_sleep);
}


// This function handles the thinking behavior of a philosopher.
void    think(t_philo *philo)
{
    print_state(philo, "is thinking");
}
