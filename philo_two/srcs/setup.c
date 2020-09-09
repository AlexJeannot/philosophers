#include "../includes/philo_two.h"

int setup_settings(int argc, char **params)
{
    if ((argc < 5 || argc > 6))
        return (ft_error("wrong number of arguments"));
    if (ft_atoi(params[0], "number_of_philosopher", &settings.philo_nb)
        || ft_atoi(params[1], "time_to_die", &settings.die_timer)
        || ft_atoi(params[2], "time_to_eat", &settings.eat_timer)
        || ft_atoi(params[3], "time_to_sleep", &settings.sleep_timer))
        return (1);
    if (argc == 6)
    {
        if (ft_atoi(params[4], "number_of_time_each_philosophers_must_eat", &settings.meal_nb))
            return (1);
    }
    else
        settings.meal_nb = -1;
    settings.init_ts = get_time();
    settings.full_nb = 0;
    sem_unlink("/msg_sem");
    sem_unlink("/full_sem");
    sem_unlink("/fork_sem");
    if ((settings.msg_sem = sem_open("/msg_sem", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
        return (ft_error("message semaphore initilialization has failed"));
    if ((settings.full_sem = sem_open("/full_sem", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
        return (ft_error("full counter semaphore initilialization has failed"));
    if ((settings.fork_sem = sem_open("/fork_sem", O_CREAT | O_EXCL, 0644, settings.philo_nb)) == SEM_FAILED)
        return (ft_error("fork semaphore initilialization has failed"));
    return (0);
}

void create_philosopher(t_philosopher *philo, int count)
{
    philo->id = (count + 1);
    philo->meal_counter = 0;
    philo->is_full = 0;
}

int setup_philosophers(t_philosopher **philosophers)
{
    t_philosopher *philosopher_array;
    int count;

    count = 0;
    if (!(philosopher_array = (t_philosopher *)malloc(sizeof(t_philosopher) * settings.philo_nb)))
        return (ft_error("memory allocation problem"));
    while (count < settings.philo_nb)
    {
        create_philosopher(&philosopher_array[count], count);
        count++;
    }
    *philosophers = philosopher_array;
    return (0);
}