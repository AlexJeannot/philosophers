#include "philo_one.h"

int main(int argc, char **argv)
{
    t_philosopher *philosopher_array;

    if (setup_settings(argc, &argv[1]))
        return (1);
    printf("AFTER SETUP SETTINGS\n");
    if (setup_philosophers(&philosopher_array))
        return (1);
    printf("AFTER setup_philosophers\n");
    //display_philosophers(philosopher_array, settings.philo_nb);

    if (exec_threads(philosopher_array))
        return (1);
    pthread_mutex_destroy(&settings.msg_mutex);

    return (0);
}