#define DEVICE_INDEX 0
#define SERIAL_PORT Serial1
#define INT16_TO_UINT10(x) ((x) / (1 << 6) + (1 << 9))

enum CommandId {
	CONNECTION_START = 0x00,
	CONNECTION_END   = 0x01,
	CONTROLLER_STATE = 0x80
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
	uint16_t reserved;
} JoystickState_t;

/* ============= Global Variables ============= */
JoystickState_t current_state;

/* ============= Local Functions ============= */

/*
 * Send the current gamepad state as USB HID report
 */
void send_gamepad_update() {
	// Need to convert joystick values from
	// 16b signed [−32768, 32767] to 10b unsigned [0, 1023]
	Joystick.X(INT16_TO_UINT10(current_state.joystick1_x));
	Joystick.Y(INT16_TO_UINT10(current_state.joystick1_y));

	Joystick.Zrotate(INT16_TO_UINT10(current_state.joystick2_x));
	Joystick.Z(INT16_TO_UINT10(current_state.joystick2_y));

	for (uint8_t i = 0; i < 16; i++) {
		Joystick.button(i + 1, current_state.button_state & (1 << i));
	}

	Joystick.send_now();
}

/*
 * Validate a received command header. Returns true if header is valid and
 * matches this device's ID, false otherwise.
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
			return header->length == sizeof(JoystickState_t);
			break;

		default:
			// Invalid/unknown CID
			break;
	}
	return false;
}

/*
 * Parse and handle command contained in the given buffer
 */
void handle_command(uint8_t *buf) {
	CommandHeader_t *header = (CommandHeader_t *)buf;
	switch (header->cid) {
		case CONNECTION_START:
			break;

		case CONNECTION_END:
			// Reset state
			memset(&current_state, 0, sizeof(JoystickState_t));
			send_gamepad_update();
			break;

		case CONTROLLER_STATE:
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
	memset(&current_state, 0, sizeof(JoystickState_t));
	
	Joystick.useManualSend(true);
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
			SERIAL_PORT.clear();
			return;
		}
		
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
