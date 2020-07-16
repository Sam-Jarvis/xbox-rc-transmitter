#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

struct XboxOneButtonData {
	uint8_t type;
	uint8_t const_0;
	uint16_t id;

	bool sync : 1;
	bool dummy1 : 1;  // Always 0.
	bool start : 1;
	bool back : 1;

	bool a : 1;
	bool b : 1;
	bool x : 1;
	bool y : 1;

	bool dpad_up : 1;
	bool dpad_down : 1;
	bool dpad_left : 1;
	bool dpad_right : 1;

	bool bumper_left : 1;
	bool bumper_right : 1;
	bool stick_left_click : 1;
	bool stick_right_click : 1;

	uint16_t trigger_left;
	uint16_t trigger_right;

	int16_t stick_left_x;
	int16_t stick_left_y;
	int16_t stick_right_x;
	int16_t stick_right_y;
};

int grab_controller();
void read_controller();
void termination_handler(int);