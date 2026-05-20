import zmq

def main():
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5555")

    message = "Hello World!"
    print(f"Sending request: {message}")
    socket.send_string(message)

    reply = socket.recv_string()
    print(f"Received reply: {reply}")

if __name__ == "__main__":
    main()
