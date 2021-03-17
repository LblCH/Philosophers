/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:33:05 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/17 20:54:48 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			init_phils2(t_phil *phil, int i)
{
	char *str;

	str = get_sem_name("PHIL_SEM_", i);
	if ((phil->sem = open_sem(str, 1)) == SEM_FAILED)
	{
		free(str);
		return (1);
	}
	free(str);
	str = get_sem_name("FEED_SEM_", i);
	if ((phil->sem_feed = open_sem(str, 0)) == SEM_FAILED)
	{
		free(str);
		return (1);
	}
	free(str);
	phil->feeded = 0;
	phil->n_of_eats = 0;
	phil->num = i;
	phil->time_of_eat = get_time();
	return (0);
}

static int	init_phils(t_phils *phils, t_phil *phil)
{
	int	i;

	i = 0;
	while (i++ < phils->n_of_philo)
	{
		if (init_phils2(phil, i))
			return (1);
		phil->phils = phils;
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
	if ((phils->sem_end = open_sem("END_SEM", 0)) == SEM_FAILED ||
	(phils->sem_forks = open_sem("FORK_SEM", phils->n_of_philo)) == SEM_FAILED \
	|| (phils->sem_write = open_sem("WRITE_SEM", 1)) == SEM_FAILED)
		return (1);
	phils->dead = 0;
	phils->feeded = 0;
	if (!(phil = (t_phil *)malloc(sizeof(struct s_phil))))
		return (1);
	phils->first = phil;
	if (init_phils(phils, phil))
		return (1);
	return (0);
}

sem_t		*open_sem(char const *name, int n)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, n));
}
