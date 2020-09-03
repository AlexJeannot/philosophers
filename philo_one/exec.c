#include "philo_one.h"

int philo_sleep(t_philosopher *philo)
{
    if (display_action(philo->id, "\033[38;5;38mis sleeping\033[0m", 0))
        return (1);
    usleep(settings.sleep_timer * 1000);
    return (0);
}

int philo_think(t_philosopher *philo)
{
    if (display_action(philo->id, "\033[38;5;208mis thinking\033[0m", 0))
        return (1);
    return (0);
}

void *manage_thread(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    philo->eat_ts = get_time();
    while (1)
    {
        if ((philo_eat(philo)) || (philo_sleep(philo)) || (philo_think(philo)))
        {
            philo->mutex_error = 1;
            return ((void *)&(philo->mutex_error));
        }
    }
    return ((void *)0);
}

int monitor_threads(t_philosopher *philosophers)
{
    int count;
    
    while (1)
    {
        count = 0;
        while (count < settings.philo_nb)
        {
            if (!(is_alive(&philosophers[count])))
            {
                if (display_action(philosophers[count].id, "\033[38;5;160mdied\033[0m", 1))
                    philosophers[count].mutex_error = 1;
                else
                    return (0);
            }
            if (philosophers[count].mutex_error)
                return (ft_error("mutex lock/unlock has fail"));
        }
        if (reach_eat_minimun())
            return (0);
    }
}

int exec_threads(t_philosopher *philosophers)
{
    pthread_t threads[settings.philo_nb];
    int count;

    count = 0;
    while (count < settings.philo_nb)
    {
        if (pthread_create(&threads[count], NULL, manage_thread, (void *)(&philosophers[count])))
            return (ft_error(" thread creation has failed"));
        if (pthread_detach(threads[count]))
            return (ft_error(" thread attachment has failed"));
        usleep(10);
        count++;
    }
    return (monitor_threads(philosophers));
}