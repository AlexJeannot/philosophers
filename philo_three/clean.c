#include "philo_three.h"

void close_sem(sem_t *semaphore, char *str)
{
    sem_unlink(str);
    (void)semaphore;
   // sem_close(semaphore);
}

void free_philosophers(t_philosopher *pilosophers)
{
    if (pilosophers)
        free(pilosophers);
}