/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_libft_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:39:42 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/16 16:59:59 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int is_digit(const char *str)
{
    int i;

    i = 0;
    if (!str || *str == '\0')
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
