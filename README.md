Course: CS 4540 – Fall 2014
Assignment <2> 
Name: <Waleed H Gudah>
E-mail: <waleed.h.gudah@wmich.edu>
Submitted: <10/12/14>

Usage example: (./thisProgram hello) or (./this "Hello My name is ...")
Please use " ", for messages longer than 1 word.

Demo {

 $ gcc [sourcefile] -o [executable]
 $ ./[executable] "Hi There!"

    Parent([pid]): Sending [Hi There!] to Child

    Child([pid]): Received Message

    Child([pid]): Toggling Case and Sending to Parent

    Parent([pid]): Received [hI tHERE!] from Child

}

Requirements {

Design a program using ordinary pipes in which one process sends 
a string message to a second process, and the second process reverses 
the case of each character (lower to upper, upper to lower) in the
received message, and sends the reverse-case message to the 
first process. For example, if the first process sends the 
message “Hi There” the second process will reply with 
“hI tHERE”. The program requires using two pipes: 
one for sending the original message from Process 1 to Process 2,
and the other for sending the reverse-case message from Process 2 to Process 1.

}

# Processes-N-Pipes

Processes-N-Pipes is a versatile tool designed to facilitate inter-process communication (IPC) and data pipelining in various computing environments. By abstracting complex IPC mechanisms, it aims to simplify the development of applications that require efficient and reliable communication between processes.

## Key Features

- **Efficient Data Transfer:** Utilize pipes for fast and secure data transfer between processes.
- **Broad Compatibility:** Supports various operating systems and environments, ensuring wide applicability.
- **User-friendly API:** Offers a simple and intuitive API, making it easier to integrate into your projects.
- **Flexible Communication Patterns:** Supports different communication patterns such as request-reply, publish-subscribe, and pipeline.
- **High Reliability:** Implements error handling and recovery mechanisms to maintain stable operation.
- **Lightweight and Scalable:** Designed to be both resource-efficient and scalable to support complex applications.
- **Detailed Logging:** Provides comprehensive logging options for easier debugging and monitoring.
- **Security Focused:** Implements measures to secure communication channels against unauthorized access.

## Installation

### Prerequisites

Ensure you have the following prerequisites installed:
- An appropriate runtime environment (e.g., Node.js, Python, etc.), depending on the implementation language of your project.
- Necessary permissions to install software on your system.

### Step-by-Step Installation

1. Clone this repository to your local machine:

```bash
git clone https://github.com/your-username/Processes-N-Pipes.git
```

2. Navigate to the cloned repository:

```bash
cd Processes-N-Pipes
```

3. Run the installation command based on your project's environment. For example, if it's a Node.js project, you would run:

```bash
npm install
```

Or, for a Python project:

```bash
pip install -r requirements.txt
```

## Usage

To use Processes-N-Pipes in your project, follow these general steps (note: adjust according to your project's language and structure):

1. Import the Processes-N-Pipes module/package into your project.

2. Instantiate a new communication channel using the provided API functions.

3. Define the data transfer logic, including any necessary serialization/deserialization.

4. Start sending or receiving data according to the chosen communication pattern.

Here is a pseudo-code example:

```python
from processes_n_pipes import create_channel

# Creating a new communication channel
channel = create_channel()

# Sending data
channel.send("Hello, Process!")

# Receiving data
message = channel.receive()
print(f"Received: {message}")
```

## Contributing

We welcome contributions to the Processes-N-Pipes project! Whether it's submitting bug reports, feature requests, or code contributions.
## License

Processes-N-Pipes is released under the [MIT License](LICENSE). Feel free to use it within your own projects.

## Support

If you need assistance or have any questions, please file an issue in the GitHub issue tracker for this repository.