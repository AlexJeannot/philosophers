#include "../includes/philo_three.h"

int main(int argc, char **argv)
{
    int ret;

    setup_settings(argc, &argv[1]);
    ret = manage_processes();
    clean_sem(settings.msg_sem, "/msg_sem");
    clean_sem(settings.fork_sem, "/fork_sem");
    return (ret);
}