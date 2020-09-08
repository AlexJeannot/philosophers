#include "philo_three.h"

int main(int argc, char **argv)
{
    setup_settings(argc, &argv[1]);
    exec_processes();
    close_sem(settings.msg_sem, "/msg_sem");
    close_sem(settings.full_sem, "/full_sem");
    close_sem(settings.fork_sem, "/fork_sem");
    //free_philosophers(philosophers);
    return (0);
}