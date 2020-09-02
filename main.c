#include "philo_one.h"

int verify_args(int argc, char **params)
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
        if (ft_atoi(params[4], "number_of_time_each_philosophers_must_eat", &settings.eat_number))
            return (1);  
    }
    else
        settings.eat_number = INT_MAX;
    pthread_mutex_init(&settings.msg_mutex, NULL);
    return (0);
}

int setup_philosophers(t_philosopher **philosophers)
{
    t_philosopher *philosopher_array;
    t_fork *new_fork;
    int count;

    count = 0;
    if (!(philosopher_array = (t_philosopher *)malloc(sizeof(t_philosopher) * settings.philo_nb)))
        return (ft_error("memory allocation problem"));
    while (count < settings.philo_nb)
    {
        philosopher_array[count].id = (count + 1);
        philosopher_array[count].is_alive = 1;
        philosopher_array[count].eat_counter = 0;
        if (!(new_fork = (t_fork *)malloc(sizeof(t_fork))))
            return (ft_error("memory allocation problem"));
        new_fork->is_use = 0;
        pthread_mutex_init(&new_fork->fork_mutex, NULL);
        philosopher_array[count].l_fork = new_fork;
        if (count > 0)
            philosopher_array[count].r_fork = philosopher_array[count - 1].l_fork;
        count++;
    }
    philosopher_array[0].r_fork = philosopher_array[count - 1].l_fork;
    *philosophers = philosopher_array;
    return (0);
}

int main(int argc, char **argv)
{
    t_philosopher *philosopher_array;

    if (verify_args(argc, &argv[1]))
        return (1);

    display_settings();

    if (setup_philosophers(&philosopher_array))
        return (1);

    display_philosophers(philosopher_array);


    if (exec_philosophers(&philosopher_array))
        return (1);

    pthread_mutex_destroy(&settings.msg_mutex);
    return (0);
}