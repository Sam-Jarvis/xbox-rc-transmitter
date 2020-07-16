#include "utilities.h"

libusb_device_handle *h;

int grab_controller(){

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
    return 0;
}

void read_controller()
{

    char read_data[512];
    int error, transferred, received;

    int endpoint = 0x01;
    int timeout = 2000;
    
    int opt;

    /*
    while((opt = getopt(argc, argv, ":if:rls")) != -1)
	{
		switch(opt)
		{
			case 'r':

			break;

            default:
            printf("%s\n", "");
    */

    grab_controller();

    memset(read_data, 0, 3);
    endpoint = 0x81;

    printf("%s\n", "Reading controller state ...");

    while (1)
    {
        libusb_interrupt_transfer(h, endpoint, read_data, sizeof(read_data), &transferred, timeout);

        /*
        for (int x = 0; x < transferred; x++)
        {
            printf("%02x ", read_data[x]);
        }
        printf("\n");
        */

        struct XboxOneButtonData data;

        data.type = read_data[0];
        data.stick_left_x = read_data[10];
        data.stick_left_y = read_data[12];
        data.stick_right_x = read_data[14];
        data.stick_right_y = read_data[16];

        uint8_t button = read_data[4];
        switch (button)
        {
        case 0x02:
            /* code */
            break;
        
        default:
            break;
        }

        /*
        printf("Message type: %02x \n", read_data[0]);
        printf("D-Pad: %02x \n", read_data[5]);
        printf("Buttons: %02x \n", read_data[4]);
        printf("R-Trig: %02x \n", read_data[8]);
        printf("L-Trig: %02x \n", read_data[6]);
        printf("L-Stick X: %02x \n", read_data[10]);
        printf("L-stick Y: %02x \n", read_data[12]);
        printf("R-Stick X: %02x \n", read_data[14]);
        printf("R-stick Y: %02x \n", read_data[16]);

        printf("\n");
        */
    }
}

void termination_handler(int signum)
{
    int rls_crm = libusb_release_interface(h, 0);
    if (rls_crm != 0)
    {
        perror("device release failed");
    }
    else
    {
        printf("\n%s\n", "successfully released device");
    }

    int at_crm = libusb_attach_kernel_driver(h, 0);
    if (at_crm != 0)
    {
        perror("kernel attach failed");
    }
    else
    {
        printf("%s\n", "successfully attached kernel driver");
    }

    libusb_close(h);

    printf("\n%s\n", "killed.");
    exit(0);
}


/*
if ((error = libusb_interrupt_transfer(h, 0x01, data_rumble, sizeof(data_rumble), &transferred, 2000)) != 0) {
    printf("Transfer failed: %d\n", error);
}
*/