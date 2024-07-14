/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:19:38 by lorenzo           #+#    #+#             */
/*   Updated: 2024/07/14 16:20:44 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	input_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (error("Invalid argument", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

void	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->tid)
		error("malloc failed", NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		error("malloc failed", NULL);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		error("malloc failed", NULL);
}

void	init_data(t_data *data, char **argv, int argc)
{
	int	i;

	i = 0;
	data->n_philo = (int) atol(argv[1]);
	data->death_time = (u_int64_t) ft_atol(argv[2]);
	data->eat_time = (u_int64_t) ft_atol(argv[3]);
	data->sleep_time = (u_int64_t) ft_atol(argv[4]);
	if (argc == 6)
		data->n_meals = (int) ft_atol(argv[5]);
	else
		data->n_meals = -1;
	data->exit = 0;
	data->satiated = 0;
	alloc(data);
	while (i < data->n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].time_to_die = data->death_time;
		data->philo[i].eat_cont = 0;
		data->philo[i].eating = 0;
		data->philo[i].status = 0;
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	while (i < data->n_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	data->philo[0].r_fork = &data->forks[0];
	data->philo[0].l_fork = &data->forks[data->n_philo - 1];
	i++;
	while (i < data->n_philo)
	{
		data->philo[i].r_fork = &data->forks[i];
		data->philo[i].l_fork = &data->forks[i - 1];
		i++;
	}
}

void	init(t_data *data, char **argv, int argc)
{
	input_check(argv);
	init_data(data, argv, argc);
	init_mutex(data);
}
