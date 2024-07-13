/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:11:41 by lorenzo           #+#    #+#             */
/*   Updated: 2024/07/13 22:50:54 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print(char *str, t_philo *philo)
{
	u_int64_t	time;
	char	*color;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (str == EAT)
		color = GREEN;
	else if (str == THINK)
		color = YELLOW;
	else if (str == SLEEP)
		color = CYAN;
	else if (str == DIED)
		printf("%s%lu %d %s%s\n", RED, time, philo->id, str, RESET);
	else
		color = RESET;
	if (philo->data->exit == 0)
		printf("%s%lu %d %s%s\n", color, time, philo->id, str, RESET);
	pthread_mutex_unlock(&philo->data->write);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print(TAKEL, philo);
	pthread_mutex_lock(philo->r_fork);
	print(TAKER, philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	print(EAT, philo);
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->data->lock);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	//print(DROP, philo);
}

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	while (philo->data->exit == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->satiated >= philo->data->n_philo)
			philo->data->exit = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->exit == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0 && philo->data->exit == 0)
		{
			philo->data->exit = 1;
			print(DIED, philo);
		}
		else if (philo->eat_cont == philo->data->n_meals)
		{
			philo->data->satiated++;
			philo->eat_cont++;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->t, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->exit == 0)
	{
		eat(philo);
		print(SLEEP, philo);
		ft_usleep(philo->data->sleep_time);
		print(THINK, philo);
	}
	if (pthread_join(philo->t, NULL))
		return ((void *)1);
	return ((void *)0);
}
