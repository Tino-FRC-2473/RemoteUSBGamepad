#define DEVICE_INDEX 0
#define SERIAL_PORT Serial1
#define PIN_LED 13
#define INT16_TO_UINT10(x) ((x) / (1 << 6) + (1 << 9))

#ifdef XINPUT_INTERFACE
#include <XInput.h>

// Lookup table to translate from raw button indices to XInput button ID
XInputControl XINPUT_BUTTON_MAP[] = {
	BUTTON_LOGO,
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LB,
	BUTTON_RB,
	BUTTON_BACK,
	BUTTON_START,
	BUTTON_L3,
	BUTTON_R3,
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,
	TRIGGER_LEFT,
	TRIGGER_RIGHT
};
#endif /* ifdef XINPUT_INTERFACE */

enum CommandId {
	CONNECTION_START = 0x00,
	CONNECTION_END   = 0x01,
	CONTROLLER_STATE = 0x80,
	XINPUT_STATE = 0x81
};

typedef struct {
	uint8_t index;
	uint8_t cid;
	uint16_t length;
} CommandHeader_t;

typedef struct {
	int16_t joystick1_x;
	int16_t joystick1_y;
	int16_t joystick2_x;
	int16_t joystick2_y;
	uint16_t button_state;
	uint8_t trigger_left;
	uint8_t trigger_right;
} JoystickState_t;

/* ============= Global Variables ============= */
JoystickState_t current_state;

/* ============= Local Functions ============= */

/*
 * Send the current gamepad state as USB HID report
 */
void send_gamepad_update() {
#ifdef XINPUT_INTERFACE
	// Use Arduino XInput library (https://github.com/dmadison/ArduinoXInput)

	XInput.setJoystick(JOY_LEFT, current_state.joystick1_x, current_state.joystick1_y);
	XInput.setJoystick(JOY_RIGHT, current_state.joystick2_x, current_state.joystick2_y);

	XInput.setTrigger(TRIGGER_LEFT, current_state.trigger_left);
	XInput.setTrigger(TRIGGER_RIGHT, current_state.trigger_right);

	for (uint8_t i = 0; i < 16; i++) {
		XInput.setButton(XINPUT_BUTTON_MAP[i], current_state.button_state & (1 << i));
	}

	// Send values to PC
	XInput.send();

#elif defined JOYSTICK_INTERFACE
	// Use Teensyduino Joystick (https://www.pjrc.com/teensy/td_joystick.html)
	
	// Need to convert joystick values from
	// 16b signed [−32768, 32767] to 10b unsigned [0, 1023]
	Joystick.X(INT16_TO_UINT10(current_state.joystick1_x));
	Joystick.Y(INT16_TO_UINT10(current_state.joystick1_y));

	Joystick.Zrotate(INT16_TO_UINT10(current_state.joystick2_x));
	Joystick.Z(INT16_TO_UINT10(current_state.joystick2_y));

	Serial.print("Joystick1 X: ");
	Serial.println(INT16_TO_UINT10(current_state.joystick1_x));
	Serial.print("Joystick1 Y: ");
	Serial.println(INT16_TO_UINT10(current_state.joystick1_y));
	Serial.print("Joystick2 X: ");
	Serial.println(INT16_TO_UINT10(current_state.joystick2_x));
	Serial.print("Joystick2 Y: ");
	Serial.println(INT16_TO_UINT10(current_state.joystick2_y));

	Joystick.sliderLeft(4 * current_state.trigger_left);
	Joystick.sliderRight(4 * current_state.trigger_right);

	for (uint8_t i = 0; i < 16; i++) {
		Joystick.button(i + 1, current_state.button_state & (1 << i));
		Serial.print("Button ");
		Serial.print(i);
		Serial.print(" = ");
		Serial.println((current_state.button_state & (1 << i)) ? "true" : "false");
	}

	Joystick.send_now();
#endif /* ifdef XINPUT_INTERFACE */
}

/*
 * Validate a received command header. Returns true if header is valid,
 * false otherwise.
 */
bool is_header_valid(CommandHeader_t *header) {
	// Verify command length matches with command ID
	switch (header->cid) {
		case CONNECTION_START:
			return header->length == 0;
			break;

		case CONNECTION_END:
			return header->length == 0;
			break;

		case CONTROLLER_STATE:
		case XINPUT_STATE:
			return header->length == sizeof(JoystickState_t);
			break;

		default:
			// Invalid/unknown CID
			break;
	}
	return false;
}

/*
 * Parse and handle command contained in the given buffer. Assumes command
 * has already been validated.
 */
void handle_command(uint8_t *buf) {
	CommandHeader_t *header = (CommandHeader_t *)buf;
	switch (header->cid) {
		case CONNECTION_START:
			digitalWrite(PIN_LED, HIGH);
			break;

		case CONNECTION_END:
			// Reset state
			memset(&current_state, 0, sizeof(JoystickState_t));
			send_gamepad_update();
			digitalWrite(PIN_LED, LOW);
			break;

		case CONTROLLER_STATE:
		case XINPUT_STATE:
			memcpy((void *)&current_state, &header[1], sizeof(JoystickState_t));
			send_gamepad_update();
			break;

		default:
			// Invalid/unknown CID
			break;
	}
}

/* ============= Entrypoint Functions ============= */
void setup() {
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, LOW);
	Serial.begin(115200);
	
	memset(&current_state, 0, sizeof(JoystickState_t));
	
#ifdef JOYSTICK_INTERFACE
	Joystick.useManualSend(true);
#endif /* ifdef JOYSTICK_INTERFACE */

#ifdef XINPUT_INTERFACE
	XInput.setJoystickRange(INT16_MIN, INT16_MAX);
	XInput.setTriggerRange(0, UINT8_MAX);
#endif /* ifdef XINPUT_INTERFACE */

	send_gamepad_update();

	SERIAL_PORT.begin(115200);
}

void loop() {
	int in_byte;
	uint8_t recv_buf[64];
	CommandHeader_t *header;

	if ((uint8_t)SERIAL_PORT.available() >= sizeof(CommandHeader_t)) {
		// Read in command header
		for (uint8_t i = 0; i < sizeof(CommandHeader_t); i++) {
			in_byte = SERIAL_PORT.read();
			if (in_byte == -1) {
				// Read error, available() should guard against this
				return;
			}
			recv_buf[i] = (uint8_t)in_byte;
		}

		header = (CommandHeader_t *)recv_buf;
		if (!is_header_valid(header)) {
			// Likely corrupted message or garbage data
			Serial.println("Invalid header!");
			SERIAL_PORT.clear();
			return;
		}
		Serial.println("Valid header");
		
		// Read in command body
		while (SERIAL_PORT.available() < header->length) {
			delay(1);
		}
		for (uint8_t i = sizeof(CommandHeader_t); i < header->length + sizeof(CommandHeader_t); i++) {
			in_byte = SERIAL_PORT.read();
			if (in_byte == -1) {
				// Read error, available() should guard against this
				return;
			}
			recv_buf[i] = (uint8_t)in_byte;
		}

		handle_command(recv_buf);
	}

	// Update approx once every 10ms
	delay(10);
}
