/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:03:46 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/15 14:04:48 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_AMOUNT_OF_PHILOS 1000

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_attributes
{
    size_t      start_time;
    int         number_of_philos;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         number_of_meals;
} t_attributes;

typedef struct s_philo
{
    int             id;
    int             is_dead;
    int             times_eaten;
    pthread_t       thread;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *death;
    pthread_mutex_t *print;
    size_t          last_meal;
    t_attributes    *attributes;
} t_philo;

typedef struct s_mutex
{
    pthread_mutex_t *forks;
    pthread_mutex_t death;
    pthread_mutex_t print;
} t_mutex;

//prototypes
int     set_attributes(t_attributes *attributes, int argc, char **argv);
void    *run_philo(void *this);
void    initialize_philos(t_philo *philos, t_attributes *attributes, t_mutex *mutex);
void    spawn_philos(t_philo *philos);
void    join_philos(t_philo *philos);
void    god(t_philo *philos, t_attributes *attributes);
void    eat(t_philo *philo);
void    ft_sleep(t_philo *philo);
void    think(t_philo *philo);
int     initialize_mutex(int number_of_philos, t_mutex *mutex);
int     destroy_mutex(int number_of_philos, t_mutex *mutex);
size_t  get_time_ms(void);
void    ft_usleep(size_t time_to_sleep);
void    error_handler(char *str);
int     check_death(t_philo *philo);
int     ft_atoi(char *str);
void    print_state(t_philo *philo, char *str);

#endif