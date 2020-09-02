#include "philo_one.h"



void *manage_threads(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    while (philo->eat_number < settings->eat_number)
    {
        if ((!(philo_eat(philo))) || (!(philo_sleep(philo))) || (!(philo_think(philo))))
            return (announce_dead(philo));
    }
    return (0);
}

int exec_philosophers(t_settings *settings, t_philosopher **philosophers)
{
    pthread_t threads[settings->philo_nb];
    int count;

    count = 0;
    while (count < settings->philo_nb)
    {
        pthread_create(&threads[count], NULL, manage_threads, (void *)(&(*philosophers)[count]));
        usleep(10);
        count++;
    }
    count = 0;
    while (count < settings->philo_nb)
    {
        pthread_join(threads[count], NULL);
        count++;
    }
    return (0);
}