#include <libusb-1.0/libusb.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	libusb_device_handle *h;
	unsigned char data[] = { 0x01, 0x03, 0x01 };
	unsigned char data_read[] = { 0x00, 0x03, 0x03 };

	int error, transferred, received;

	libusb_init(NULL);
	h = libusb_open_device_with_vid_pid(NULL, 0x045e, 0x028e);

	if (h == NULL) {
		fprintf(stderr, "Failed to open device\n");
		perror("failed to open device-cool");
		return (1);
	}

	int dt_crm = libusb_detach_kernel_driver(h, 0);
	if(dt_crm != 0){
		printf("%s\n", "device detach: failed");
		perror("failed ");
	}

	int cl_crm = libusb_claim_interface(h, 0);
	if(cl_crm != 0){
		printf("%s\n", "device claim: failed");
	}

	//printf("%s\n", "opening device: passed");
	
	if ((error = libusb_interrupt_transfer(h, 0x01, data, sizeof(data), &transferred, 2000)) != 0) {
		fprintf(stderr, "Transfer failed: %d\n", error);
		perror("trans failed");
		return (1);
	}

	received = libusb_bulk_transfer(h, 0x81, data_read, sizeof(data_read), &received, 2000);
	if(received != 0){
		perror("failed to read");
	}

	printf("transferred: %d bytes\n", transferred);
	printf("%s\n", "returning");
	return (0);
}

//check
//detach
//claim