
# Linux Chat Project

## Overview
The **Linux Chat Project** is a simple client-server chat application developed in **C** using socket programming. The project demonstrates how to build a multi-client chat system where multiple clients can connect to a server, send messages, and receive responses. The server utilizes the `select()` function to handle multiple clients concurrently without blocking.

This project is designed to help understand basic networking concepts, including the use of **sockets**, **binding**, **listening**, and **select** for multiplexing I/O operations in a server environment.

## Features
- **Multiple Client Support**: The server can handle multiple client connections at the same time.
- **Simple Communication**: Clients can send messages to the server, which are then displayed on the server-side.
- **Non-blocking I/O**: The server uses `select()` to monitor multiple sockets for incoming data, allowing it to serve multiple clients simultaneously.
- **Standard Libraries**: The implementation uses only standard C libraries, ensuring compatibility across Linux systems.

## Requirements
To run this project, you need:
- A Linux-based operating system (Ubuntu or any other distribution)
- **GCC** (GNU Compiler Collection) to compile the C code
- Basic knowledge of Linux commands and socket programming in C

## Installation and Execution

### 1. Clone the repository
If you haven't already, clone the repository to your local machine:
```bash
git clone https://github.com/yourusername/linux-chat-project.git
cd linux-chat-project
```

### 2. Compile the server and client
Use `gcc` to compile both the server and client code:
```bash
gcc server.c -o server
gcc client.c -o client
```

### 3. Start the server
Open a terminal window and run the server:
```bash
./server
```
The server will begin listening for incoming connections on port **8080**.

### 4. Start the client
In another terminal window, run the client application:
```bash
./client
```
You can now type messages in the client terminal, which will be sent to the server.

### 5. Multiple Clients
To simulate multiple clients, simply open more terminals and run the `./client` program in each. All clients will be able to send messages to the server.

## How It Works

### Server (`server.c`)
1. **Socket Creation**: The server creates a TCP socket and binds it to **port 8080** on the local machine.
2. **Listening**: The server listens for incoming client connections using the `listen()` system call.
3. **Handling Multiple Clients**: The server uses the `select()` system call to monitor multiple client sockets. This allows it to handle multiple clients at the same time without blocking.
4. **Receiving and Printing Messages**: When a client sends a message, the server reads the data from the client's socket and prints it to the console.

### Client (`client.c`)
1. **Socket Creation**: The client creates a TCP socket and connects to the server at `127.0.0.1` (localhost).
2. **Sending Messages**: The client continuously reads user input and sends it to the server.
3. **Communication Loop**: The client runs in a loop, allowing the user to type and send messages until the client is terminated.

## Example Usage

### Starting the Server:
```bash
$ ./server
Server listening on port 8080...
New client connected: 127.0.0.1:34567
```

### Starting the Client:
```bash
$ ./client
Connected to server. Type your messages below:
Hello Server!
```

### Server Displays the Client's Message:
```bash
Client: Hello Server!
```

### Multiple Clients:
You can open multiple terminal windows and start the client in each. Each client can send messages, and the server will handle all connections concurrently.

## Possible Improvements
While this project provides a basic framework for a multi-client chat application, there are several areas where it can be improved:
- **Message Broadcasting**: Currently, the server prints the messages to the terminal, but it does not send them to other clients. You can implement message broadcasting so that all connected clients receive messages.
- **User Authentication**: Implement a simple login system to allow users to authenticate before chatting.
- **Message Encryption**: To enhance privacy, you can add message encryption between the server and clients.
- **Graphical User Interface**: The client is currently command-line-based. You could implement a GUI using libraries like GTK or Qt for a more user-friendly interface.

## Directory Structure

```
/linux-chat-project
    ├── server.c         # Server-side code
    ├── client.c         # Client-side code
    └── README.md        # Project documentation
```

## Troubleshooting
- **Connection Issues**: If the client cannot connect to the server, ensure that the server is running and listening on port **8080**. Also, verify that no firewall is blocking the connection.
- **Compilation Errors**: If you encounter compilation issues, ensure that you have the necessary C development tools installed (e.g., `gcc`, `make`).


