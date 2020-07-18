# RemoteUSBGamepad
Bridge USB gamepad over IP to enable FTC remote operation

## Setup
This project uses pipenv to manage dependencies. Run server script with `pipenv run python3 server/gamepad_bridge_server.py test.txt`, open client HTML in a browser.

## Protocol
The same binary message format will be used over the Websocket and serial connection. We shall use little-endian byte order to match the Arduino/ARM processor convention. All messages start with the following header:

Field | Size (bytes) | Description 
------------ | ------------- | -------------
Index | 1 | ID of destination controller
Command ID | 1 | Numeric identifier signfying message type
Length | 2 | Length of the message body in bytes. Note this does not include this header, only the contents following.

### Connection Start Command (CID=0x00)
Signify that a client has connected to the given controller index. No message body (length = 0).

### Connection End Command (CID=0x01)
Signify that a client has disconnected from the given controller index. No message body (length = 0).

### Controller State Report (CID=0x80)
Report the controller state from client to server/device. Message body:

Field | Size (bytes) | Description 
------------ | ------------- | -------------
Joystick1_X | 2 | Joystick 1 X Axis value. Format as 16 bit signed integer.
Joystick1_Y | 2 | Joystick 1 Y Axis value
Joystick2_X | 2 | Joystick 2 X Axis value
Joystick2_Y | 2 | Joystick 2 Y Axis value
Button_state | 2 | Bitfield indicating status of controller buttons. Bit(x) = 1 if pressed, 0 if unpressed. Bits counted from LSB.
RESERVED | 2 | Unused, space reserved for padding to 4b alignment.
