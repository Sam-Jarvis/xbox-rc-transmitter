#include "utilities.h"

libusb_device_handle *h;
bool wasOpened = false;

unsigned char read_data[512];
int transferred;
//void *t = memset(read_data, 0, 5);

int open_controller()
{

    /*
        General method:
        1) check device handle (not null)
        2) detach kernel driver
        3) claim interface
    */

    libusb_init(NULL);

    // attach handle
    h = libusb_open_device_with_vid_pid(NULL, 0x24c6, 0x581b);

    // 1
    if (h == NULL)
    {
        //fprintf(stderr, "Failed to open device\n");
        perror("failed to open device: ");
        return 1;
    }
    else
    {
        printf("%s\n", "successfully opened device");
    }

    // 2
    int dt_crm = libusb_detach_kernel_driver(h, 0);
    if (dt_crm != 0)
    {
        //printf("%s\n", "device detach: failed");
        perror("kernel detach failed: ");
        return 1;
    }
    else
    {
        printf("%s\n", "successfully detached kernel");
    }

    // 3
    int cl_crm = libusb_claim_interface(h, 0);
    if (cl_crm != 0)
    {
        //printf("%s\n", "device claim: failed");
        perror("device claim failed: ");
        return 1;
    }
    else
    {
        printf("%s\n", "successfully claimed interface");
    }
    wasOpened = true;
    return 0;
}

int close_controller()
{
    if (wasOpened)
    {
        int rls_crm = libusb_release_interface(h, 0);
        if (rls_crm != 0)
        {
            perror("device release failed");
            return 1;
        }
        else
        {
            printf("\n%s\n", "successfully released device");
        }

        int at_crm = libusb_attach_kernel_driver(h, 0);
        if (at_crm != 0)
        {
            perror("kernel attach failed");
            return 1;
        }
        else
        {
            printf("%s\n", "successfully attached kernel driver");
        }
    }
    libusb_close(h);
    return 0;
}

void user_input(unsigned char* read_data, int *transferred)
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
                buff = test(read_data, transferred);
                while(1){
                    print_controller_state(true, buff, transferred);
                }
                //read_controller(true);
                break;
            }
        }
    }
}

void print_controller_state(bool debug, unsigned char *read_data, int *transferred)
{
    if (debug)
    {
        for (int x = 0; x < transferred; x++)
        {
            printf("%02x ", read_data[x]);
        }
    }
    else
    {
        printf("D-Pad: %02x \n", read_data[5]);
        printf("Buttons: %02x \n", read_data[4]);
        printf("R-Trig: %02x \n", read_data[8]);
        printf("L-Trig: %02x \n", read_data[6]);
        printf("L-Stick X: %02x \n", read_data[10]);
        printf("L-stick Y: %02x \n", read_data[12]);
        printf("R-Stick X: %02x \n", read_data[14]);
        printf("R-stick Y: %02x \n", read_data[16]);
    }
    printf("\n");
}

unsigned char *test(unsigned char* read_data, int *transferred)
{
    int endpoint = 0x81;
    int timeout = 2000;

    open_controller();
    memset(read_data, 0, 5);

    libusb_interrupt_transfer(h, endpoint, read_data, sizeof(read_data), &transferred, timeout);

    return read_data;
}

void read_controller(bool debug)
{
    unsigned char read_data[512];
    memset(read_data, 0, 5);
    int transferred;
    int endpoint = 0x81;
    int timeout = 2000;

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
    open_controller();

    printf("%s\n", "Reading controller state ...");

    while (1)
    {
        libusb_interrupt_transfer(h, endpoint, read_data, sizeof(read_data), &transferred, timeout);

        if (debug)
        {
            print_controller_state(true, read_data, transferred);
        }
        else
        {
            print_controller_state(false, read_data, transferred);
        }

        /*
        struct XboxOneButtonData data;

        data.type = read_data[0];
        data.stick_left_x = read_data[10];
        data.stick_left_y = read_data[12];
        data.stick_right_x = read_data[14];
        data.stick_right_y = read_data[16];

        printf("Message type: %02x \n", data.type);
        */
    }
}

/*
if ((error = libusb_interrupt_transfer(h, 0x01, data_rumble, sizeof(data_rumble), &transferred, 2000)) != 0) {
    printf("Transfer failed: %d\n", error);
}
*/