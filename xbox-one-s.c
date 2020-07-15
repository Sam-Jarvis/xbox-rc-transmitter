#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

static void* read_controller(){
    
    libusb_init(NULL);
    char read_data[512];
    int error, transferred, received;
    
    int endpoint = 0x01;
	int timeout = 2000;

    // attach handle
    libusb_device_handle *h;

    if (pthread_detach (pthread_self ()) != 0)
    {
        perror ("pthread_detach(read_controller)");
    }

	h = libusb_open_device_with_vid_pid(NULL, 0x24c6, 0x581b);

    /*
        General method:
        1) check device handle (not null)
        2) detach kernel driver
        3) claim interface
    */

    // 1
	if (h == NULL) {
		//fprintf(stderr, "Failed to open device\n");
		perror("failed to open device: ");
	}
    else
    {
        printf("%s\n", "sucessfully opened device");
    }
    

    // 2
	int dt_crm = libusb_detach_kernel_driver(h, 0);
	if(dt_crm != 0){
		//printf("%s\n", "device detach: failed");
		perror("kernel detach failed: ");
	}
    else
    {
        printf("%s\n", "sucessfully detached kernel");
    }

    // 3
	int cl_crm = libusb_claim_interface(h, 0);
	if(cl_crm != 0){
		//printf("%s\n", "device claim: failed");
        perror("device claim failed: ");
	}
    else
    {
        printf("%s\n", "sucessfully claimed interface");
    }

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

    memset(read_data, 0, 3);
	endpoint = 0x81;

	printf("%s\n", "Reading controller state ...");

	while(1) {
        libusb_interrupt_transfer(h, endpoint, read_data, sizeof(read_data), &transferred, timeout);
                
        for(int x=0; x < transferred; x++) {
        printf("%02x ", read_data[x]);
		}
        printf("\n");

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
        return(NULL);
}

void keyboard_watchdog(){
    char input[1];

    if (pthread_detach (pthread_self ()) != 0)
    {
        perror ("pthread_detach(watchdog)");
    }

    scanf("%s", input);
    printf("%s\n", input[0]);

}

int main(int argc, char *argv[])
{
	// command to send
    //unsigned char data[] = {  };
    pthread_t watchdog;
    pthread_t read;

    if (pthread_create (&watchdog, NULL, keyboard_watchdog, (void *) 300000) != 0)
    {
        perror ("watchdog");
    }

    if (pthread_create (&read, NULL, read_controller, (void *) 300000) != 0)
    {
        perror ("watchdog");
    }     
}
