import asyncio
import websockets
import serial
from pathlib import Path

class WSServer:
    def __init__(self, queue, base_port):
        self.message_queue = queue
        self.base_port = base_port

    async def on_receive(self, websocket, path):
        server_port = websocket.local_address[1]
        try:
            async for message in websocket:
                print(server_port, "received", message, "from", websocket.remote_address[0])

                # Append the received message to the queue
                await self.message_queue.put((server_port, message))

                await websocket.send(message)
        except Exception as e:
            print("Unexpected connection close on port", server_port)
        print("Issuing disconnect for port", server_port)
        await self.message_queue.put((server_port, (server_port - self.base_port).to_bytes(1, 'little') + b"\x01\x00\x00"))

    def start(self, num_controllers):
        for i in range(num_controllers):
            print("Starting server on port", i + self.base_port)
            asyncio.get_event_loop().run_until_complete(websockets.serve(self.on_receive, "", i + self.base_port))
            print("Server started")

# Consumes arriving messages queue. This serializes message handling independent
# of the server threads, to avoid races over the serial output
async def queue_handler(queue, serial_port, baud=115200):
    print("queue_handler started")
    with serial.Serial(serial_port, 115200, timeout=1) as ser:
        while True:
            index, message = await queue.get()
            print("Dequeued message", message, "for index", index)
            ser.write(message)
            queue.task_done()

async def dummy_queue_handler(queue):
    print("queue_handler started")
    while True:
        index, message = await queue.get()
        print("Dequeued message", message, "for index", index)
        queue.task_done()

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Run server for Remote USB Gamepad bridge')
    parser.add_argument('--num-controllers', type=int, default=2, help='Number of controllers to listen for')
    parser.add_argument('--base-port', '-p', type=int, default=8000, help='Base port number for 0th controller. Other controllers will have servers attached to port base+id')
    parser.add_argument('--baud', type=int, default=115200, help='Serial port baud rate')
    parser.add_argument('--dummy-serial', action="store_true", help='Use dummy handler instead of real serial port')
    parser.add_argument('serial_port', help="Serial port to output commands")

    args = parser.parse_args()

    queue = asyncio.Queue()
    
    server = WSServer(queue, args.base_port)
    server.start(args.num_controllers)

    if args.dummy_serial:
        asyncio.get_event_loop().run_until_complete(dummy_queue_handler(queue))
    else:
        asyncio.get_event_loop().run_until_complete(queue_handler(queue, args.serial_port, args.baud))
    asyncio.get_event_loop().run_forever()
