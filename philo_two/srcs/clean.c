#include "../includes/philo_two.h"

void clean_sem(char *str)
{
    sem_unlink(str);
}

void free_philosophers(t_philosopher *pilosophers)
{
    if (pilosophers)
        free(pilosophers);
}