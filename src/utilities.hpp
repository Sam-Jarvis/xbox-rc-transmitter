#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
//#include <RF24-master/SPI.h>
//#include <nRF24L01.h>
//#include <RF24/RF24.h>

struct XboxOneButtonData
{
	uint8_t type;
	uint16_t id;

	bool sync : 1;

	uint8_t button;
	/* 	read_data[4]
	bool a : 1; 0x10
	bool b : 1; 0x20
	bool x : 1; 0x40
	bool y : 1; 0x80
	bool start : 0x08;
	bool back : 0x04;
*/

	uint8_t dpad;
	/*	read_data[5]
	bool dpad_up : 1; 0x01
	bool dpad_down : 1; 0x02
	bool dpad_left : 1; 0x04
	bool dpad_right : 1; 0x08
	bool bumper_left : 1; 0x10
	bool bumper_right : 1; 0x20
	bool stick_left_click : 1; 0x40
	bool stick_right_click : 1; 0x80
*/

	uint16_t trigger_left;
	uint16_t trigger_right;

	int16_t stick_left_x;
	int16_t stick_left_y;
	int16_t stick_right_x;
	int16_t stick_right_y;
};

int open_controller(libusb_device_handle *);
int close_controller(libusb_device_handle *);
void print_controller_state(bool, unsigned char *, int);
struct XboxOneButtonData *store_data(unsigned char *, struct XboxOneButtonData *);
//void read_controller(bool);