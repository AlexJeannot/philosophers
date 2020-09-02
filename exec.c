#include "philo_one.h"

int philo_eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->r_fork->fork_mutex);
    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m");
    pthread_mutex_lock(&philo->l_fork->fork_mutex);
    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m");
    display_action(philo->id, "\033[38;5;40mis eating\033[0m");
    usleep(settings.eat_timer);
    pthread_mutex_unlock(&philo->r_fork->fork_mutex);
    pthread_mutex_unlock(&philo->l_fork->fork_mutex);

    return (1);
}

int philo_sleep(t_philosopher *philo)
{
    display_action(philo->id, "\033[38;5;38mis sleeping\033[0m");
    usleep(settings.sleep_timer);
    return (1);
}

int philo_think(t_philosopher *philo)
{
    display_action(philo->id, "\033[38;5;208mis thinking\033[0m");
    return (1);
}

void announce_dead(t_philosopher *philo)
{
    display_action(philo->id, "\033[38;5;160dead\033[0m");
}

void *manage_thread(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    while (philo->eat_counter < settings.eat_number)
    {
        if ((!(philo_eat(philo))) || (!(philo_sleep(philo))) || (!(philo_think(philo))))
        {
            announce_dead(philo);
            return ((void *)1);
        }
            //return ((void *)(announce_dead(philo)));
    }
    return ((void *)0);
}

int exec_philosophers(t_philosopher **philosophers)
{
    pthread_t threads[settings.philo_nb];
    int count;
    int ret;

    count = 0;
    while (count < settings.philo_nb)
    {
        pthread_create(&threads[count], NULL, manage_thread, (void *)(&(*philosophers)[count]));
        usleep(10);
        count++;
    }
    count = 0;
    while (count < settings.philo_nb)
    {
        pthread_join(threads[count], (void *)&ret);
        count++;
    }
    return (0);
}