#include "../includes/philo_one.h"

void destroy_mutex(t_philosopher *pilosophers)
{
    int count;

    count = 0;
    while (count < settings.philo_nb)
    {
        pthread_mutex_destroy(&(pilosophers[count].l_fork->fork_mutex));
        count++;
    }
    if (settings.philo_nb == 1)
        pthread_mutex_destroy(&(pilosophers[0].r_fork->fork_mutex));
    pthread_mutex_destroy(&settings.msg_mutex);
    pthread_mutex_destroy(&settings.full_mutex);
}

void free_philosophers(t_philosopher *pilosophers)
{
    int count;

    count = 0;
    if (pilosophers)
    {
        while (count < settings.philo_nb)
        {
            free(pilosophers[count].l_fork);
            count++;
        }
        if (settings.philo_nb == 1)
            free(pilosophers[count].r_fork);
        free(pilosophers);
    }
}