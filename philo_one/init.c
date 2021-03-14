#include "philo_one.h"

static void 	init_phils(t_phils *phils, t_phil *phil)
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
			(!(phil->next = (t_phil *) malloc(sizeof(struct s_phil)))) ? \
																exit(11) : 0;
			phil->next->prev = phil;
			phil = phil->next;
		}
	}
	phil->next = phils->first;
	phils->first->prev = phil;
}

void 			init_all(t_phils *phils, char **argv)
{
	struct s_phil *phil;

	phils->n_of_philo = ft_atoi(argv[1]);
	phils->time_to_die = ft_atoi(argv[2]);
	phils->time_to_eat = ft_atoi(argv[3]);
	phils->time_to_sleep = ft_atoi(argv[4]);
	phils->n_of_eats = (argv[5]) ? ft_atoi(argv[5]) : 0;
	pthread_mutex_init(&phils->mutex, NULL);
	pthread_mutex_init(&time_mutex, NULL);
	phils->dead = 0;
	phils->feeded = 0;
	if (!(phil = (t_phil *)malloc(sizeof (struct s_phil))))
		exit(11);
	phils->first = phil;
	init_phils(phils, phil);
}
