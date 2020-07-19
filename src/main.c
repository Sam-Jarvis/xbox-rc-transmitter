#include "utilities.h"

unsigned char read_data[512];
int transferred;

void termination_handler(int signum)
{
    close_controller();
    user_input(read_data, &transferred);
    //printf("\n%s\n", "killed.");
    //exit(0);
}

int main(int argc, char *argv[])
{
    // command to send
    //unsigned char data[] = {  };
    signal(SIGINT, termination_handler);
    user_input(read_data, &transferred);

    return 0;
}