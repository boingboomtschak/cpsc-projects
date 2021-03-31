#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "FileSys.h"
using namespace std;

struct Command {
    string name;		// name of command
    string file_name;   // name of file
    string append_data;	// append data (append only)
};

Command parse_command(string command_str);
void call_command(FileSys *fs, Command cmd);
int sendall(int sock, char *buf, int buf_len);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./nfsserver port#\n";
        return -1;
    }
    int port = atoi(argv[1]);
    int sock, cli_len, accept_sock, e, b; 
    char buf[1024];
    string cmd_str;
    struct sockaddr_in srv_addr, cli_addr;
    FileSys fs;

    // Creating socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error opening socket");
        return -1;
    }

    // Setting up server address struct
    memset((char *)&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    srv_addr.sin_port = htons(port);

    // Binding to host address
    if (bind(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr)) < 0) {
        perror("error binding to host address");
        return -1;
    }

    // Listening for client connections
    listen(sock, 1); 
    cli_len = sizeof(cli_addr);

    // Accepting client connection
    accept_sock = accept(sock, (struct sockaddr *) &cli_addr, (socklen_t *)&cli_len);
    if (accept_sock < 0) {
        perror("error accepting client connection");
        return -1;
    }

    // Close listening socket
    close(sock);


    fs.mount(accept_sock); //assume that sock is the new socket created 
                    //for a TCP connection between the client and the server.   
 
    //loop: get the command from the client and invoke the file
    //system operation which returns the results or error messages back to the clinet
    //until the client closes the TCP connection.

    cout << "Client connected!" << endl; 

    while(1) {
        // Clear command input buffer
        memset(&buf, 0, sizeof(buf));

        // Receive from accepted client socket
        b = recv(accept_sock, buf, sizeof(buf) - 1, 0);
        
        // Check for client disconnection or read error
        if (b == 0) {
            // 0 bytes read, client disconnected
            fprintf(stderr, "Client disconnected!\n");
            break;
        } else if (b < 0) {
            // Error reading from socket!
            fprintf(stderr, "Error reading from socket\n");
            break;
        }
        
        struct Command cmd; 
        cmd_str = buf;
        cmd = parse_command(cmd_str);
        call_command(&fs, cmd);

        printf("Client called command '%s' with argument '%s' and data '%s'\n", cmd.name.c_str(), cmd.file_name.c_str(), cmd.append_data.c_str());
    }

    // Close the listening socket
    close(accept_sock);

    // Unmount the file system
    fs.unmount();

    return 0;
}


// Parses a command line into a command struct. Returned name is blank
// for invalid command lines.
Command parse_command(string command_str) {
  // empty command struct returned for errors
  struct Command empty = {"", "", ""};

    // grab each of the tokens (if they exist)
    struct Command command;
    istringstream ss(command_str);
    int num_tokens = 0;
    if (ss >> command.name) {
        num_tokens++;
        if (ss >> command.file_name) {
            num_tokens++;
            if (ss >> command.append_data) {
                num_tokens++;
                string junk;
                if (ss >> junk) {
                    num_tokens++;
                }
            }
        }
    }

    // Check for empty command line
    if (num_tokens == 0) {
        return empty;
    }
    
    // Check for invalid command lines
    if (command.name == "ls" ||
        command.name == "home" ||
        command.name == "quit")
    {
        if (num_tokens != 1) {
            cerr << "Invalid command line: " << command.name;
            cerr << " has improper number of arguments" << endl;
            return empty;
        }
    }
    else if (command.name == "mkdir" ||
        command.name == "cd"    ||
        command.name == "rmdir" ||
        command.name == "create"||
        command.name == "cat"   ||
        command.name == "rm"    ||
        command.name == "stat")
    {
        if (num_tokens != 2) {
            cerr << "Invalid command line: " << command.name;
            cerr << " has improper number of arguments" << endl;
            return empty;
        }
    } else if (command.name == "append" || command.name == "head") {
        if (num_tokens != 3) {
            cerr << "Invalid command line: " << command.name;
            cerr << " has improper number of arguments" << endl;
            return empty;
        }
    } else {
        cerr << "Invalid command line: " << command.name;
        cerr << " is not a command" << endl; 
        return empty;
    } 

    return command;
}

void call_command(FileSys *fs, Command cmd) {
    if (cmd.name == "mkdir") {
        fs->mkdir(cmd.file_name.c_str());
    } else if (cmd.name == "cd") {
        fs->cd(cmd.file_name.c_str());
    } else if (cmd.name == "home") {
        fs->home();
    } else if (cmd.name == "rmdir") {
        fs->rmdir(cmd.file_name.c_str());
    } else if (cmd.name == "ls") {
        fs->ls();
    } else if (cmd.name == "create") {
        fs->create(cmd.file_name.c_str());
    } else if (cmd.name == "append") {
        fs->append(cmd.file_name.c_str(), cmd.append_data.c_str());
    } else if (cmd.name == "cat") {
        fs->cat(cmd.file_name.c_str());
    } else if (cmd.name == "head") {
        fs->head(cmd.file_name.c_str(), stoi(cmd.append_data));
    } else if (cmd.name == "rm") {
        fs->rm(cmd.file_name.c_str());
    } else if (cmd.name == "stat") {
        fs->stat(cmd.file_name.c_str());
    } 
}

// sendall adapted from the versions in Beej's network programming guide
int sendall(int sock, char *buf, int buf_len) {
    int total = 0;
    int b = buf_len;
    int e;
    while (total < buf_len) {
        e = send(sock, buf + total, b, 0);
        if (e == -1) {
            break;
        }
        total += e;
        b -= e;
    }
    buf_len = total;
    if (e == -1) {
        return -1;
    } else {
        return 0;
    }
}