import zmq

def main():
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind("tcp://*:5555")

    print("Server started on port 5555")
    while True:
        message = socket.recv_string()
        print(f"Received request: {message}")
        socket.send_string(f"Echo: {message}")

if __name__ == "__main__":
    main()
