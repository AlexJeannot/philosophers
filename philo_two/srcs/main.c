#include "../includes/philo_two.h"

int main(int argc, char **argv)
{
    t_philosopher *philosophers;

    if (setup_settings(argc, &argv[1])
        || setup_philosophers(&philosophers)
        || exec_threads(philosophers))
        return (1);
    clean_sem();
    free_philosophers(philosophers);
    return (0);
}