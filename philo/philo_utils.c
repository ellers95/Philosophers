/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:34:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/23 18:20:30 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Get the current time in milliseconds.
size_t  get_time_ms(void)
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Custom usleep function to handle sleeping.
void    ft_usleep(size_t time_to_sleep)
{
    size_t  start;

    start = get_time_ms();
    while ((get_time_ms() - start) < time_to_sleep)
        usleep(100);
}

// Check if a philosopher has died.
int check_death(t_philo *philo)
{
    size_t  current_time;
    size_t  time_since_last_meal;
    size_t  time_to_die;

    current_time = get_time_ms();
    time_to_die = (size_t)(philo->attributes->time_to_die);
    time_since_last_meal = current_time - philo->last_meal;
    //printf("check death before if statement\n"); << DEBUGGING
    //printf("%zu\n", time_since_last_meal); << DEBUGGING
    //printf("%zu\n", time_to_die); << DEBUGGING
    // If the time since the last meal is greater than the time to die, the philosopher dies.
    if (time_since_last_meal > time_to_die)
    {
        print_state(philo, "died");
        pthread_mutex_lock(philo->death);
        *philo->is_dead = 1;
        pthread_mutex_unlock(philo->death);
        return (1);
    }
    return (0);
}

// This function simulates the god thread, which monitors the philosophers.
void    god(t_philo *philos, t_attributes *attributes)
{
    int i;
    int done_eating;
    
    ft_usleep(attributes->time_to_die);
    while (1)
    {
        done_eating = 0;
        i = 0;
        // Check each philosopher's status in a loop.
        while (i < attributes->number_of_philos)
        {
            if (check_death(&philos[i]))
            {
                //pthread_mutex_unlock(philos[i].death); DELETE?
                return ;
            }
            //printf("%d", philo[i].times_eaten) << DEBUGGING
            // If all philosophers have eaten the required number of meals, end the simulation.
            //pthread_mutex_lock(philos[i].meal); DELETE?
            if (attributes->number_of_meals != -1 && philos[i].times_eaten >= attributes->number_of_meals)
                done_eating++;
            //pthread_mutex_unlock(philos[i].meal); DELETE?
            i++;
        }
        if (done_eating == attributes->number_of_philos)
        {
            pthread_mutex_lock(philos->death);
            *philos->is_dead = 1;
            pthread_mutex_unlock(philos->death);
            return ;
        }
    }
}
