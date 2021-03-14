#include "philo_one.h"

int		start_threads(t_phils *phils)
{
	pthread_t	tid;
	int			i;
	t_phil		*phil;

	i = 0;
	phils->start = get_time();
	printf("%dms Program started.\n", get_time());
	if (phils->n_of_eats > 0)
	{
		if (pthread_create(&tid, NULL, &eat_check, phils))
			return (1);
		pthread_detach(tid);
	}
	phil = phils->first;
	while (i++ < phils->n_of_philo)
	{
		if (pthread_create(&tid, NULL, &phil_life, phil))
			return (1);
		pthread_detach(tid);
		phil = phil->next;
	}
	return (0);
}

int 	main(int argc, char **argv)
{
	t_phils	phils;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number of args.\n");
		return (0);
	}
	init_all(&phils, argv);
//	t_phil *phil;
//	phil = phils.first;
//	for (int i = 0; i < phils.n_of_philo; i++)
//	{
//		printf("# of phil - %d\n phil status - %d\n n_of_eats - %d\n", \
//			phil->num, phil->status, phil->n_of_eats);
//		phil = phil->next;
//		(phil == phils.first) ? phil = NULL : 0;
//	}
	start_threads(&phils);
	pthread_mutex_lock(&phils.mutex);
	pthread_mutex_unlock(&phils.mutex);
	return (0);
}