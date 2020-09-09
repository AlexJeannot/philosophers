#include "../includes/philo_one.h"

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
    pthread_mutex_init(&settings.msg_mutex, NULL);
    pthread_mutex_init(&settings.full_mutex, NULL);
    return (0);
}

int create_fork(t_fork **input_fork)
{
    if (!(*input_fork = (t_fork *)malloc(sizeof(t_fork))))
        return (ft_error("memory allocation problem"));
    pthread_mutex_init(&((*input_fork)->fork_mutex), NULL); 
    return (0);
}

int create_philosopher(t_philosopher *philo, t_philosopher *prev_philo, int count)
{
    t_fork *new_fork;

    new_fork = NULL;
    philo->id = (count + 1);
    philo->meal_counter = 0;
    philo->is_full = 0;
    if (create_fork(&new_fork))
        return (1);
    philo->l_fork = new_fork;
    if (count > 0)
        philo->r_fork = prev_philo->l_fork;
    return (0);
}

int setup_last_fork(t_philosopher *first_philo, t_philosopher *last_philo)
{
    t_fork *new_fork;

    new_fork = NULL;
    if (settings.philo_nb == 1)
    {
        if (create_fork(&new_fork))
            return (1);
        first_philo->r_fork = new_fork;
    }
    else if (settings.philo_nb > 1)
        first_philo->r_fork = last_philo->l_fork;
    return (0);
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
        if (create_philosopher(&philosopher_array[count], &philosopher_array[count - 1], count))
            return (1);
        count++;
    }
    if (setup_last_fork(&philosopher_array[0], &philosopher_array[count - 1]))
        return (1);
    *philosophers = philosopher_array;
    return (0);
}