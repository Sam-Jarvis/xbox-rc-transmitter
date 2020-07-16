#include "utilities.h"

void termination_handler(int signum)
{
    close_controller();

    printf("\n%s\n", "killed.");
    exit(0);
}

int main(int argc, char *argv[])
{
    // command to send
    //unsigned char data[] = {  };

    signal(SIGINT, termination_handler);
    read_controller();

    return 0;
}