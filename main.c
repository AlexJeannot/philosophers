#include "philo_one.h"

int verify_args(int argc, char **params, t_settings *settings)
{
    if ((argc < 5 || argc > 6))
        return (ft_error("wrong number of arguments"));
    if (ft_atoui(params[0], "number_of_philosopher", &settings->philo_nb)
        || ft_atoui(params[1], "time_to_die", &settings->die_timer)
        || ft_atoui(params[2], "time_to_eat", &settings->eat_timer)
        || ft_atoui(params[3], "time_to_sleep", &settings->sleep_timer))
        return (1);
    if (argc == 6)
    {
        if (ft_atoui(params[4], "number_of_time_each_philosophers_must_eat", &settings->eat_number))
            return (1);  
    }
    else
        settings->eat_number = -1;
    return (0);
}

int setup_philosophers(t_settings *settings, t_philosopher **philosophers)
{
    t_philosopher *philosopher_array;
    t_fork *new_fork;
    int count;

    count = 0;
    if (!(philosopher_array = (t_philosopher *)malloc(sizeof(t_philosopher) * settings->philo_nb)))
        return (ft_error("memory allocation problem"));
    while (count < settings->philo_nb)
    {
        philosopher_array[count].id = (count + 1);
        philosopher_array[count].is_alive = 1;
        philosopher_array[count].eat_counter = 0;
        if (!(new_fork = (t_fork *)malloc(sizeof(t_fork))))
            return (ft_error("memory allocation problem"));
        new_fork->is_use = 0;
        philosopher_array[count].l_fork = new_fork;
        if (count > 0)
            philosopher_array[count].r_fork = philosopher_array[count - 1].l_fork;
        count++;
    }
    philosopher_array[0].r_fork = philosopher_array[count - 1].l_fork;
    *philosophers = philosopher_array;
    return (0);
}

/*
void *announce(void *philo)
{
    t_philosopher *test;
    test = (t_philosopher *)philo;
    printf("\n----------------\n");
    printf("test->id = %d\n", test->id);
    printf("test->eat_counter = %d\n", test->eat_counter);
    printf("test->r_fork = %p\n", test->r_fork);
    printf("test->l_fork = %p\n", test->l_fork);
    printf("test = %p\n", &(*test));

    return (0);
}
*/

int main(int argc, char **argv)
{
    t_settings settings;
    t_philosopher *philosopher_array;

    if (verify_args(argc, &argv[1], &settings))
        return (1);

    display_settings(&settings);

    if (setup_philosophers(&settings, &philosopher_array))
        return (1);

    display_philosophers(&settings, philosopher_array);


    if (exec_philosophers(&settings, &philosopher_array))
        return (1);
    return (0);
}