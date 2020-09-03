#include "philo_one.h"

int is_alive(t_philosopher *philo)
{
    if ((get_time() - philo->eat_ts) > (unsigned long long)settings.die_timer)
        philo->is_alive = 0;
    return (philo->is_alive);
}

int min_eat_reach()
{
    return (settings.min_eat_counter == settings.philo_nb);
}

int philo_eat(t_philosopher *philo)
{
    if (!(is_alive(philo)))
        return (0);
    if (philo->id % 2 == 0)
        pthread_mutex_lock(&philo->r_fork->fork_mutex);
    else
        pthread_mutex_lock(&philo->l_fork->fork_mutex);
    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);
    if (philo->id % 2 == 0)
        pthread_mutex_lock(&philo->l_fork->fork_mutex);
    else
        pthread_mutex_lock(&philo->r_fork->fork_mutex);

    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);

    philo->eat_counter++;
    if (philo->eat_counter == settings.eat_number)
    {
        pthread_mutex_lock(&settings.min_eat_mutex);
        settings.min_eat_counter++;
        pthread_mutex_unlock(&settings.min_eat_mutex);
    }

    display_action(philo->id, "\033[38;5;40mis eating\033[0m", 0);
    usleep(settings.eat_timer * 1000);
    philo->eat_ts = get_time();
    pthread_mutex_unlock(&philo->r_fork->fork_mutex);
    pthread_mutex_unlock(&philo->l_fork->fork_mutex);

    return (1);
}

int philo_sleep(t_philosopher *philo)
{
    if (!(is_alive(philo)))
        return (0);
    display_action(philo->id, "\033[38;5;38mis sleeping\033[0m", 0);
    usleep(settings.sleep_timer * 1000);
    return (1);
}

int philo_think(t_philosopher *philo)
{
    if (!(is_alive(philo)))
        return (0);
    display_action(philo->id, "\033[38;5;208mis thinking\033[0m", 0);
    return (1);
}

void announce_dead(t_philosopher *philo)
{
    display_action(philo->id, "\033[38;5;160mdied\033[0m", 1);
}

void *manage_thread(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    philo->eat_ts = get_time();
    while (1)
    {
        if ((!(philo_eat(philo))) || (!(philo_sleep(philo))) || (!(philo_think(philo))))
        {
            announce_dead(philo);
            return ((void *)0);
        }
    }
    return ((void *)0);
}

int exec_philosophers(t_philosopher **philosophers)
{
    pthread_t threads[settings.philo_nb];
    int count;

    count = 0;
    while (count < settings.philo_nb)
    {
        if (pthread_create(&threads[count], NULL, manage_thread, (void *)(&(*philosophers)[count])))
            printf("EROOR\n");
        pthread_detach(threads[count]);
        usleep(10);
        count++;
    }
    while (1)
    {
        count = 0;
        while (count < settings.philo_nb)
        {
            if ((*philosophers)[count].is_alive == 0 && settings.dead_displayed == 1)
                return (0);
            count++;
        }
        if (min_eat_reach())
            return (0);
    }
    return (0);
}