/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:02:47 by lorenzo           #+#    #+#             */
/*   Updated: 2024/07/01 12:42:59 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKER	"has taken right fork"
# define TAKEL	"has taken left fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIED	"died"
# define DROP	"dropped forks"

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define CYAN	"\033[0;36m"
# define RESET	"\033[0m"

typedef struct s_data
{
	struct s_philo	*philo;
	unsigned int	n_philo;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	int				n_meals;
	int				exit;
	int				satiated;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_t		*tid;
}	t_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	u_int64_t		time_to_die;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

int			main(int argc, char **argv);
int			error(char *msg, t_data *data);
int			is_in_strings(char c, char *str);
long		ft_atol(const char *str);
int			input_check(char **argv);
void		init_data(t_data *data, char **argv, int argc);
void		init_mutex(t_data *data);
int			init_thread(t_data *data);
void		init(t_data *data, char **argv, int argc);
u_int64_t	get_time(void);
int			ft_usleep(u_int64_t time);
void		ft_free(t_data *data);
int			ft_strcmp(char *s1, char *s2);

void		print(char *str, t_philo *philo);
void		eat(t_philo *philo);
void		*monitor(void *data_pointer);
void		*supervisor(void *philo_ptr);
void		*routine(void *philo_pointer);

#endif