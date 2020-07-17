import asyncio
import websockets
from pathlib import Path

class WSServer:
    def __init__(self, queue):
        self.message_queue = queue

    async def on_receive(self, websocket, path):
        async for message in websocket:
            server_port = websocket.local_address[1]
            print(server_port, "received", message, "from", websocket.remote_address[0])

            response = "Received " + message

            # Append the received message to the queue
            await self.message_queue.put((server_port, message))

            await websocket.send(response)

    def start(self, num_controllers, base_port):
        for i in range(num_controllers):
            print("Starting server on port", i + args.base_port)
            asyncio.get_event_loop().run_until_complete(websockets.serve(self.on_receive, "localhost", i + base_port))
            print("Server started")

# Consumes arriving messages queue. This serializes message handling independent
# of the server threads, to avoid races over the serial output
async def queue_handler(queue, outfilepath):
    print("queue_handler started")
    with open(outfilepath, 'w') as outfile:
        while True:
            index, message = await queue.get()
            print("Dequeued message", message, "for index", index)
            outfile.write(message)
            queue.task_done()

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Run server for Remote USB Gamepad bridge')
    parser.add_argument('--num-controllers', type=int, default=2, help='Number of controllers to listen for')
    parser.add_argument('--base-port', '-p', type=int, default=8000, help='Base port number for 0th controller. Other controllers will have servers attached to port base+id')
    parser.add_argument('outfile', type=Path, help="Output file to log incomming messages")

    args = parser.parse_args()

    queue = asyncio.Queue()
    
    server = WSServer(queue)
    server.start(args.num_controllers, args.base_port)

    asyncio.get_event_loop().run_until_complete(queue_handler(queue, args.outfile))
    asyncio.get_event_loop().run_forever()
