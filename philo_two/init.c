/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:33:05 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/16 01:37:52 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	init_phils(t_phils *phils, t_phil *phil)
{
	int i;

	i = 0;
	while (i++ < phils->n_of_philo)
	{
		phil->feeded = 0;
		phil->n_of_eats = 0;
		phil->num = i;
		phil->status = THINK;
		phil->phils = phils;
		phil->time_of_eat = get_time();
		pthread_mutex_init(&phil->mutex, NULL);
		pthread_mutex_init(&phil->mutex_f, NULL);
		if (i < phils->n_of_philo)
		{
			if (!(phil->next = (t_phil *)malloc(sizeof(struct s_phil))))
				return (1);
			phil->next->prev = phil;
			phil = phil->next;
		}
	}
	phil->next = phils->first;
	phils->first->prev = phil;
	return (0);
}

static int	check_args(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (!argv[i][j])
			return (1);
		while (argv[i][j])
		{
			if (j > 8)
			{
				printf("Philos dont eats/sleeps/starves so long. \n");
				return (1);
			}
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			init_all(t_phils *phils, char **argv)
{
	struct s_phil *phil;

	if (check_args(argv))
		return (1);
	phils->n_of_philo = ft_atoi(argv[1]);
	phils->time_to_die = ft_atoi(argv[2]);
	phils->time_to_eat = ft_atoi(argv[3]);
	phils->time_to_sleep = ft_atoi(argv[4]);
	phils->n_of_eats = (argv[5]) ? ft_atoi(argv[5]) : -1;
	pthread_mutex_init(&phils->mutex, NULL);
	pthread_mutex_init(&g_time_mutex, NULL);
	phils->dead = 0;
	phils->feeded = 0;
	if (!(phil = (t_phil *)malloc(sizeof(struct s_phil))))
		return (1);
	phils->first = phil;
	if (init_phils(phils, phil))
		return (1);
	return (0);
}
