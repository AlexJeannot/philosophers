#include "../includes/philo_three.h"

void clean_sem(sem_t *semaphore, char *str)
{
    sem_close(semaphore);
    sem_unlink(str);
}

void free_philosophers(t_philosopher *pilosophers)
{
    if (pilosophers)
        free(pilosophers);
}