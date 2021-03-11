#include "philo_one.h"

int 	main(int argc, char **argv)
{
	t_phils	phils;
	t_phil *phil;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number of args.\n");
		return (0);
	}
	init_all(&phils, argv);
	start_treads(&phils);
//	phil = phils.first;
//	for (int i = 0; i < phils.n_of_philo; i++)
//	{
//		printf("# of phil - %d\n phil status - %d\n phil fork - %d\n", \
//			phil->num, phil->status, phil->fork);
//		phil = phil->next;
//		(phil == phils.first) ? phil = NULL : 0;
//	}
	return (0);
}

int		start_threads(t_phils *phils)
{
	pthread_t	tid;
	int			i;
	t_phil		*phil;

	i = 0;
	phils->start = get_time();
	if (phils->n_of_eats > 0)
	{
		if (pthread_create(&tid, NULL, &eats_check, (void*)phils))
			return (1);
		pthread_detach(tid);
	}
	phil = phils->first;
	while (i++ < phils->n_of_philo)
	{
		if (pthread_create(&tid, NULL, &phil_life, (void*)phil))
			return (1);
		pthread_detach(tid);
		phil = phil->next;
	}
	return (0);
}

void 	init_all(t_phils *phils, char **argv)
{
	int i;
	struct s_phil *phil;

	i = 0;
	phils->n_of_philo = ft_atoi(argv[1]);
	phils->time_to_die = ft_atoi(argv[2]);
	phils->time_to_eat = ft_atoi(argv[3]);
	phils->time_to_sleep = ft_atoi(argv[4]);
	phils->n_of_eats = (argv[5]) ? ft_atoi(argv[5]) : 0;
	if (!(phil = (t_phil *)malloc(sizeof (struct s_phil))))
		exit(11);
	phils->first = phil;
	while (i++ < phils->n_of_philo)
	{
		phil->fork = 0;
		phil->num = i;
		phil->status = THINK;
		pthread_mutex_init(phil->mutex);
		if (i < phils->n_of_philo)
		{
			(!(phil->next = (t_phil *) malloc(sizeof(struct s_phil)))) ? \
																exit(11) : 0;
			phil = phil->next;
		}
	}
	phil->next = phils->first;
}