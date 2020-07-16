#include "main.h"
#include "utilities.h"

int main(int argc, char *argv[])
{
    // command to send
    //unsigned char data[] = {  };

    signal(SIGINT, termination_handler);
    read_controller();
}