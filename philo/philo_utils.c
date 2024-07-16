/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:34:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/16 15:36:08 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t  get_time_ms(void)
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    ft_usleep(size_t time_to_sleep)
{
    size_t  start;

    start = get_time_ms();
    while ((get_time_ms() - start) < time_to_sleep)
        usleep(100);
}

int check_death(t_philo *philo)
{
    size_t  current_time;
    size_t  time_since_last_meal;
    size_t  time_to_die;

    current_time = get_time_ms();
    time_to_die = (size_t)(philo->attributes->time_to_die * 1000);
    time_since_last_meal = current_time - philo->last_meal;

    if (time_since_last_meal > time_to_die)
    {
        pthread_mutex_lock(philo->death);
        philo->is_dead = 1;
        print_state(philo, "died");
        pthread_mutex_unlock(philo->death);
        return (1);
    }
    return (0);
}

void    god(t_philo *philos, t_attributes *attributes)
{
    int i;
    int everyone_ate;
    
    i = 0;
    everyone_ate = 0;
    printf("Entering outer loop\n");
    while (!everyone_ate)
    {
        printf("=== Beginning of outer loop iteration ===\n");  // Debug
        everyone_ate = 1;
        i = 0;
        while (i < attributes->number_of_philos)
        {
            printf("Checking philosopher %d\n", i);  // Debug
            if (check_death(&philos[i]))
            {
                printf("Philosopher %d is dead\n", i);  // Debug
                return ;
            }
            printf("Times eaten by philosopher %d: %d\n", i, philos[i].times_eaten);  // Debug
            printf("Number of meals allowed: %d\n", attributes->number_of_meals);  // Debug
            if (attributes->number_of_meals == -1 || philos[i]. times_eaten < attributes->number_of_meals)
            {
                printf("Philosopher %d needs to eat more\n", i);  // Debug
                everyone_ate = 0;
            }
            i++;
        }
        i = 0;
        printf("=== End of outer loop iteration ===\n");  // Debug
        usleep(1000);
    }
}

int ft_atoi(char *str)
{
    int sign;
    int sum;
    int i;

    sign = 1;
    sum = 0;
    i = 0;
    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
                    || str[i] == '\f' || str[i] == '\r')
            i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        sum = sum * 10 + (str[i] - '0');
        i++;
    }
    return (sum * sign);
}
