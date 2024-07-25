/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:03:46 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 17:31:24 by etaattol         ###   ########.fr       */
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

// Struct to hold the simulation attributes.
typedef struct s_attributes
{
    size_t      start_time;
    int         number_of_philos;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         number_of_meals;
} t_attributes;

// Struct to hold the philosopher's state.
typedef struct s_philo
{
    int             id;             // Philosopher's ID
    int             *death_flag;    // Flag to indicate if the philosopher is dead
    int             times_eaten;
    pthread_t       thread;         // Thread ID
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *death;
    pthread_mutex_t *print;
    pthread_mutex_t times_eaten_mutex;    // Mutex for meals eaten
    pthread_mutex_t last_meal_mutex;      
    size_t          last_meal;      // Timestamp of the last meal
    t_attributes    *attributes;    // Pointer to the simulation attributes
    
} t_philo;

// Struct to hold all mutexes.
typedef struct s_mutex
{
    pthread_mutex_t *forks;         // Array of fork mutexes
    pthread_mutex_t death;          // Mutex for handling death state
    pthread_mutex_t print;          // Mutex for printing output
} t_mutex;

// Function prototypes
int     validate_arguments(int argc, char **argv, t_attributes *attributes);
int     set_attributes(t_attributes *attributes, int argc, char **argv);
void    *run_philo(void *this);
void    run_philo_loop(t_philo *philo);
int     run_check_death(t_philo *philo);
void    initialize_philos(t_philo *philos, t_attributes *attributes, t_mutex *mutex);
void    create_philo_threads(t_philo *philos);
void    join_philos(t_philo *philos);
void    god(t_philo *philos, t_attributes *attributes);
void    eat(t_philo *philo);
void    update_last_meal(t_philo *philo);
size_t  get_last_meal(t_philo *philo);
void    ft_sleep(t_philo *philo);
void    think(t_philo *philo);
int     initialize_forks_and_times_eaten_mutex(int number_of_philos, t_mutex *mutex, t_philo *philos);
int     initialize_death_and_print_mutex(t_mutex *mutex, t_philo *philos);
int     initialize_mutex(int number_of_philos, t_mutex *mutex, t_philo *philos);
int     destroy_mutex(int number_of_philos, t_mutex *mutex, t_philo *philos);
size_t  get_time_ms(void);
void    ft_usleep(size_t time_to_sleep);
void    error_handler(char *str);
int     check_death(t_philo *philo);
int     ft_atoi(char *str);
int     is_digit(const char *str);
void    print_state(t_philo *philo, char *str);

#endif