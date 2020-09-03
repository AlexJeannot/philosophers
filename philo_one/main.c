#include "philo_one.h"

int main(int argc, char **argv)
{
    t_philosopher *philosophers;

    if (setup_settings(argc, &argv[1])
        || setup_philosophers(&philosophers)
        || exec_threads(philosophers))
        return (1);
    destroy_mutex(philosophers);
    free_philosophers(philosophers);
    return (0);
}