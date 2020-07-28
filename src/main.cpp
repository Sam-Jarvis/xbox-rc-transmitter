#include "utilities.hpp"

libusb_device_handle *h;
struct XboxOneButtonData data = {0};

void termination_handler(int signum)
{
    close_controller(h);
    printf("\n%s\n", "killed.");
    exit(0);
}

int main(int argc, char *argv[])
{
    open_controller(h);
    signal(SIGINT, termination_handler);
    
    unsigned char read_data[512];
    memset(read_data, 0, 5);

    int transferred;
    int endpoint = 0x81;
    int timeout = 2000;

    printf("%s\n", "Reading controller state ...");

    while (1)
    {
        libusb_interrupt_transfer(h, endpoint, read_data, sizeof(read_data), &transferred, timeout);

        print_controller_state(true, read_data, transferred);

        store_data(read_data, &data);

    }

    return 0;
}

// Useful code blocks

/*
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  //Send message to receiver
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  
  delay(1000);
}
*/

/*
void user_input(unsigned char* read_data, int transferred)
{
    char line[16];
    char c = ' ';

    unsigned char *buff;

    printf("\n%s\n", "What would you like me to do?: \n");
    printf("%s\n", "q --> quit");
    printf("%s\n", "r --> read");
    printf("%s\n", "d --> debug read\n");

    if (fgets(line, sizeof(line), stdin))
    {
        if (1 == sscanf(line, "%s", &c))
        {
            switch (c)
            {
            case 'q':
                close_controller();
                exit(0);

            case 'r':
                read_controller(false);
                break;

            case 'd':
            memset(read_data, 0, 5);
            while(1){
                    buff = test(read_data, transferred);
                    print_controller_state(true, buff, 16);
                }
                //read_controller(true);
                break;
            }
        }
    }
}
*/

/*
int opt;
while((opt = getopt(argc, argv, ":if:rls")) != -1)
{
	switch(opt)
	{
		case 'r':

		break;

        default:
        printf("%s\n", "");
*/

/*
if ((error = libusb_interrupt_transfer(h, 0x01, data_rumble, sizeof(data_rumble), &transferred, 2000)) != 0) {
    printf("Transfer failed: %d\n", error);
}
*/

/*
    if(read_data[4] > 0x40)
    {
        controller_state->y = true;
    }
    else if(read_data[4] > 0x20)
    {
        controller_state->x = true;
    }
    else if(read_data[4] > 0x10)
    {
        controller_state->b = true;
    }
    else
    {
        controller_state->a = true;
    }
*/