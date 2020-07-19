#include "utilities.h"

void termination_handler(int signum)
{
    user_input();
    //close_controller();
    //printf("\n%s\n", "killed.");
    //exit(0);
}

int main(int argc, char *argv[])
{
    // command to send
    //unsigned char data[] = {  };

    signal(SIGINT, termination_handler);
    user_input();
    //read_controller();

    return 0;
}