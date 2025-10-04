Simple HTTP Server
This project implements a simple HTTP server and client in C. The server listens for incoming messages on port 8080, prints the received messages, and sends a confirmation response to the client. The client sends a message to a specified host (e.g., 127.0.0.1) and displays the server's response.
Project Structure
```
httpServer/
├── src/
│   ├── build/          # Directory for compiled binaries
│   ├── client.c       # Client source code
│   └── server.c       # Server source code
└── README.md          # Project documentation
```
### Prerequisites

- GCC: Ensure the GNU Compiler Collection (GCC) is installed on your system.gcc --version


- Operating System: Tested on Linux (e.g., Fedora). Should work on other Unix-like systems or Windows with a compatible environment (e.g., WSL, MinGW).

### Setup
1 Clone the Repository:
```
git clone https://github.com/AlexandrinoVM/simple-http-server.git
cd simple-http-server
```

2 Create the Build Directory:Create a build directory inside src to store compiled binaries:
```
mkdir -p src/build
```

3 Compile the Project:Compile the server and client source files using GCC:
```
gcc -o ./src/build/server ./src/server.c
gcc -o ./src/build/client ./src/client.c
```


### Usage

1 Run the Server:Start the server, which listens on port 8080:
```
./src/build/server
```
The server will print received messages and send a confirmation response.

2 Run the Client:Run the client with the host (e.g., `127.0.0.1`) and a message as arguments:
```
./src/build/client 127.0.0.1 "Hello, Server!"
```

- The client sends the message to the server and displays the server's response.
- Example output on the server:
```
Hello, Server!
```
- Example response on the client:Server received the message
```
Server received the message
```

### Notes

Port: The server listens on port 8080 by default.
Host: Use 127.0.0.1 for local testing. Ensure the server is running before starting the client.
Build Directory: The build directory is placed inside src to keep compiled binaries organized and separate from the project root.
.gitignore: Includes common C build artifacts:
```
src/build/
*.o
*.exe
```



