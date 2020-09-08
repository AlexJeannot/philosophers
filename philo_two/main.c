#include "philo_two.h"

int main(int argc, char **argv)
{
    t_philosopher *philosophers;

    if (setup_settings(argc, &argv[1])
        || setup_philosophers(&philosophers)
        || exec_threads(philosophers))
        return (1);
    sem_unlink("/full_sem");
    sem_unlink("/fork_sem");
    sem_unlink("/msg_sem");
    free_philosophers(philosophers);
    return (0);
}