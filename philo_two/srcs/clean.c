#include "../includes/philo_two.h"

void clean_sem(void)
{
    sem_unlink("/msg_sem");
    sem_close(settings.msg_sem);
    sem_unlink("/fork_sem");
    sem_close(settings.fork_sem);
    sem_unlink("/full_sem");
    sem_close(settings.full_sem);

}

void free_philosophers(t_philosopher *pilosophers)
{
    if (pilosophers)
        free(pilosophers);
}