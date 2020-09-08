#include "philo_three.h"

int main(int argc, char **argv)
{
    t_philosopher *philosophers;

    setup_settings(argc, &argv[1]);
    setup_philosophers(&philosophers);
    exec_threads(philosophers);
    close_sem(settings.msg_sem, "/msg_sem30");
    close_sem(settings.full_sem, "/full_sem30");
    close_sem(settings.fork_sem, "/fork_sem30");
    free_philosophers(philosophers);
    return (0);
}