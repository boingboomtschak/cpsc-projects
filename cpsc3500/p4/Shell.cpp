// CPSC 3500: Shell
// Implements a basic shell (command line interface) for the file system

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Shell.h"

static const string PROMPT_STRING = "NFS> ";	// shell prompt

// Mount the network file system with server name and port number in the format of server:port
void Shell::mountNFS(string fs_loc) {
	//create the socket cs_sock and connect it to the server and port specified in fs_loc
	//if all the above operations are completed successfully, set is_mounted to true  
  string addr_str = fs_loc.substr(0, fs_loc.find(":"));
  string port_str = fs_loc.substr(fs_loc.find(":") + 1);
  int sock, e;
  int port = atoi(port_str.c_str());
  struct sockaddr_in srv_addr;
  struct hostent *srv;
  char buf[1024];

  // Creating socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("error opening socket");
    exit(1);
  }

  // Looking up hostname
  srv = gethostbyname(addr_str.c_str());
  if (srv == NULL) {
    perror("no such host");
    exit(1);
  }

  // Setting up srv_addr
  bzero((char *) &srv_addr, sizeof(srv_addr));
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(port);
  bcopy((char *)srv->h_addr, (char *)&srv_addr.sin_addr.s_addr, srv->h_length);

  // Connect to server
  e = connect(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
  if (e < 0) {
    perror("error connecting to server");
    exit(1);
  }

  // Update socket variable, set mounted to true
  cs_sock = sock;
  is_mounted = true;
}

// Unmount the network file system if it was mounted
void Shell::unmountNFS() {
	// close the socket if it was mounted
  if (is_mounted) {
    close(cs_sock);
  }
}

// Remote procedure call on mkdir
void Shell::mkdir_rpc(string dname) {
  char buf[128];
  char read_buf[9];
  char code_str[4];
  int e, len;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);

  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "mkdir ");
  strcat(buf, dname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on cd
void Shell::cd_rpc(string dname) {
  char buf[128];
  char code_str[4];
  int e;
  
  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);

  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "cd ");
  strcat(buf, dname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on home
void Shell::home_rpc() {
  char buf[128];
  char code_str[4];
  int e;
  
  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);

  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "home");
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on rmdir
void Shell::rmdir_rpc(string dname) {
  char buf[128];
  char code_str[4];
  int e;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);
  
  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "rmdir ");
  strcat(buf, dname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }
  
  return;
}

// Remote procedure call on ls
void Shell::ls_rpc() {
  char buf[128];
  int e;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);

  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "ls");
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return; 
}

// Remote procedure call on create
void Shell::create_rpc(string fname) {
  char buf[128];
  char code_str[4];
  int e;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);
  
  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "create ");
  strcat(buf, fname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on append
void Shell::append_rpc(string fname, string data) {
  char buf[MAX_FILE_SIZE + 32];
  char code_str[4];
  int e;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);
  
  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "append ");
  strcat(buf, fname.c_str());
  strcat(buf, " ");
  strcat(buf, data.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procesure call on cat
void Shell::cat_rpc(string fname) {
  char buf[MAX_FILE_SIZE + 32];
  char code_str[4];
  int e;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);
  
  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "cat ");
  strcat(buf, fname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on head
void Shell::head_rpc(string fname, int n) {
  char buf[MAX_FILE_SIZE + 32];
  char code_str[4];
  char hbytes[6];
  int e;
  
  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);

  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "head ");
  strcat(buf, fname.c_str());
  strcat(buf, " ");
  snprintf(hbytes, sizeof(hbytes), "%u", n);
  strcat(buf, hbytes);
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on rm
void Shell::rm_rpc(string fname) {
  char buf[128];
  char code_str[4];
  int e;
  
  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);

  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "rm ");
  strcat(buf, fname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Remote procedure call on stat
void Shell::stat_rpc(string fname) {
  char buf[128];
  char code_str[4];
  int e;

  // Reading any extra bytes (may be an unnecessary fix)
  ioctl(cs_sock, FIONREAD, &e);
  read(cs_sock, &buf, e);
  
  // Set up command in buffer
  memset(buf, '\0', sizeof(buf));
  strcat(buf, "stat ");
  strcat(buf, fname.c_str());
  strcat(buf, "\r\n");
  
  // Use sendall() routine to send command to server
  e = sendall(cs_sock, buf, strlen(buf));
  if (e < 0) {
    cerr << "Failed to send to socket" << endl; 
    return;
  }

  // Parse response using parse_response() function
  e = parse_response(cs_sock);
  if (e < 0) {
    cerr << "Failed to parse command response" << endl;
  }

  return;
}

// Executes the shell until the user quits.
void Shell::run()
{
  // make sure that the file system is mounted
  if (!is_mounted) 
 	return; 
  
  // continue until the user quits
  bool user_quit = false;
  while (!user_quit) {

    // print prompt and get command line
    string command_str;
    cout << PROMPT_STRING;
    getline(cin, command_str);

    // execute the command
    user_quit = execute_command(command_str);
  }

  // unmount the file system
  unmountNFS();
}

// Execute a script.
void Shell::run_script(char *file_name)
{
  // make sure that the file system is mounted
  if (!is_mounted)
  	return;
  // open script file
  ifstream infile;
  infile.open(file_name);
  if (infile.fail()) {
    cerr << "Could not open script file" << endl;
    return;
  }


  // execute each line in the script
  bool user_quit = false;
  string command_str;
  getline(infile, command_str, '\n');
  while (!infile.eof() && !user_quit) {
    cout << PROMPT_STRING << command_str << endl;
    user_quit = execute_command(command_str);
    getline(infile, command_str);
  }

  // clean up
  unmountNFS();
  infile.close();
}


// Executes the command. Returns true for quit and false otherwise.
bool Shell::execute_command(string command_str)
{
  // parse the command line
  struct Command command = parse_command(command_str);

  // look for the matching command
  if (command.name == "") {
    return false;
  }
  else if (command.name == "mkdir") {
    mkdir_rpc(command.file_name);
  }
  else if (command.name == "cd") {
    cd_rpc(command.file_name);
  }
  else if (command.name == "home") {
    home_rpc();
  }
  else if (command.name == "rmdir") {
    rmdir_rpc(command.file_name);
  }
  else if (command.name == "ls") {
    ls_rpc();
  }
  else if (command.name == "create") {
    create_rpc(command.file_name);
  }
  else if (command.name == "append") {
    append_rpc(command.file_name, command.append_data);
  }
  else if (command.name == "cat") {
    cat_rpc(command.file_name);
  }
  else if (command.name == "head") {
    errno = 0;
    unsigned long n = strtoul(command.append_data.c_str(), NULL, 0);
    if (0 == errno) {
      head_rpc(command.file_name, n);
    } else {
      cerr << "Invalid command line: " << command.append_data;
      cerr << " is not a valid number of bytes" << endl;
      return false;
    }
  }
  else if (command.name == "rm") {
    rm_rpc(command.file_name);
  }
  else if (command.name == "stat") {
    stat_rpc(command.file_name);
  }
  else if (command.name == "quit") {
    return true;
  }

  return false;
}

// Parses a command line into a command struct. Returned name is blank
// for invalid command lines.
Shell::Command Shell::parse_command(string command_str)
{
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
  }
  else if (command.name == "append" || command.name == "head")
  {
    if (num_tokens != 3) {
      cerr << "Invalid command line: " << command.name;
      cerr << " has improper number of arguments" << endl;
      return empty;
    }
  }
  else {
    cerr << "Invalid command line: " << command.name;
    cerr << " is not a command" << endl; 
    return empty;
  } 

  return command;
}

// sendall adapted from the versions in Beej's network programming guide
int Shell::sendall(int sock, char *buf, int buf_len) {
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

int Shell::parse_response(int cs_sock) {
  char buf[64];
  char *tok_buf;
  char msg_buf[MAX_FILE_SIZE];
  char c;
  int e, i, buf_i, rn, code, len, msg_buf_i;

  // Reading until three newlines (past response status and length)
  memset(&buf, '\0', sizeof(buf));
  buf_i = 0;
  rn = 0;
  while (rn < 3) {
    e = read(cs_sock, &c, 1);
    if (e <= 0) {
      cerr << "Error reading from socket" << endl;
      return -1;
    }
    if (c == '\n') {
      rn++;
    } 
    if (c != '\r') {
      buf[buf_i] = c;
      buf_i++;
    }
  }
  
  // Parsing resp. code and length
  tok_buf = strtok(buf, "\n");
  sscanf(tok_buf, "%d", &code);
  tok_buf = strtok(NULL, "\n");
  sscanf(tok_buf, "Length:%d", &len);

  // Checking if response code 200
  if (code != 200) {
    cout << buf << endl;
    return 0;
  }

  // If not, read length number of characters and output
  if (len > 0) {
    memset(&msg_buf, '\0', sizeof(msg_buf));
    msg_buf_i = 0;
    for (i = 0; i < len; i++) {
      e = read(cs_sock, &c, 1);
      if (e <= 0) {
        cerr << "Error reading from socket" << endl;
        return -1;
      }
      msg_buf[msg_buf_i] = c;
      msg_buf_i++;
    }
    cout << msg_buf << endl;
  }
  cout << "SUCCESS" << endl;
   
  return 0;
}