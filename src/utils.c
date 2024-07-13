/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:59:37 by lorenzo           #+#    #+#             */
/*   Updated: 2024/07/13 14:10:50 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error(char *msg, t_data *data)
{
	printf("Error: %s\n", msg);
	ft_free(data);
	return (1);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday failed", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free(data->tid);
	free(data->philo);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

int	is_in_strings(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	while (is_in_strings(*(char *) str, "\t\n\v\f\r "))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (result * 10 < 0)
			return (-1);
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * sign);
}