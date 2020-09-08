#include "philo_two.h"

int main(int argc, char **argv)
{
    t_philosopher *philosophers;

    if (setup_settings(argc, &argv[1])
        || setup_philosophers(&philosophers)
        || exec_threads(philosophers))
        return (1);
    close_sem(settings.msg_sem, "/msg_sem");
    close_sem(settings.full_sem, "/full_sem");
    close_sem(settings.fork_sem, "/fork_sem");
    free_philosophers(philosophers);
    return (0);
}