/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:33:00 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/17 18:55:53 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*feed_check(void *phils1)
{
	t_phils	*phils;
	t_phil	*phil;
	int		feeded;

	feeded = 0;
	phils = (t_phils *)phils1;
	phil = phils->first;
	while (feeded < phils->n_of_philo)
	{
		sem_wait(phil->sem_feed);
		feeded++;
		phil = phil->next;
	}
	phils->feeded = 1;
	printf("%d ms Feeded\n", get_time() - phils->start);
	sem_post(phils->sem_end);
	return (NULL);
}

int		start_threads(t_phils *phils)
{
	pthread_t	tid;
	int			i;
	t_phil		*phil;

	i = 0;
	phils->start = get_time();
	printf("0 ms Program started.\n");
	phil = phils->first;
	while (i++ < phils->n_of_philo)
	{
		phil->pid = fork();
		if (phil->pid == 0)
		{
			if (pthread_create(&tid, NULL, &eat_check, phil))
				return (1);
			pthread_detach(tid);
			phil_life((void *)phil);
		}
		phil = phil->next;
	}
	if (pthread_create(&tid, NULL, &feed_check, phils))
		return (1);
	pthread_detach(tid);
	return (0);
}

int		main(int argc, char **argv)
{
	t_phils	phils;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number of args.\n");
		return (0);
	}
	if (init_all(&phils, argv))
	{
		printf("Error: incorrect arguments.\n");
		return (0);
	}
	start_threads(&phils);
	sem_wait(phils.sem_end);
	ft_clear(&phils);
	return (0);
}

void	ft_clear(t_phils *phils)
{
	int		i;
	t_phil	*phil;
	t_phil	*temp;
	char	*str;

	i = 0;
	phil = phils->first;
	while (phil && i++ < phils->n_of_philo)
	{
		temp = phil->next;
		str = get_sem_name("PHIL_SEM_", i);
		sem_unlink(str);
		free(str);
		str = get_sem_name("FEED_SEM_", i);
		sem_unlink(str);
		free(str);
		kill(phil->pid, SIGKILL);
		free(phil);
		phil = NULL;
		phil = temp;
	}
	sem_unlink("END_SEM");
	sem_unlink("WRITE_SEM");
	sem_unlink("FORKS_SEM");
}

char	*get_sem_name(char *name, int i)
{
	char *str;
	char *res;

	str = ft_itoa(i);
	res = ft_strjoin(name, str);
	free(str);
	return (res);
}
