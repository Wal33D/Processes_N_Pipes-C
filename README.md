# 🔄 Processes-N-Pipes: Case Inversion IPC Demo

Welcome to **Processes-N-Pipes**, an educational and entertaining exploration into the realms of inter-process communication (IPC) using ordinary pipes. This specialized toolkit demonstrates a simple yet intriguing use case: sending a string message between two processes where the receiving process inverses the case of each character and sends it back. Perfect for learners and educators, this project simplifies understanding IPC through a fun, interactive example.

## 🎯 Core Functionality

- **Case Inversion via Pipes**: Discover the power of pipes in IPC by sending a message from one process to another, which then inversely cases each character and replies back.
- **Two-Way Communication**: Utilizes two pipes, one for each direction of communication, to showcase how messages can flow between processes efficiently.
- **Educational Tool**: Designed as a learning aid to demonstrate IPC mechanics in a clear, engaging manner.

## 🛠 Getting Started

### Prerequisites

Prepare for this IPC journey with:
- A GCC compiler or any standard C compiler.
- Basic terminal operations.

### Installation & Compilation

1. **Clone this repository**:
    \`\`\`bash
    git clone https://github.com/your-username/Processes-N-Pipes.git
    \`\`\`

2. **Navigate to the project directory**:
    \`\`\`bash
    cd Processes-N-Pipes
    \`\`\`

3. **Compile the project**:
    \`\`\`bash
    gcc -o ipc_demo main.c
    \`\`\`

## 📘 How to Play

After compiling, simply run the executable with a message as an argument to see the case inversion process in action:

\`\`\`bash
./ipc_demo "Hi There!"
\`\`\`

You'll observe that the message sent to the second process comes back with each of its character's case inverted, for example, "Hi There!" becomes "hI tHERE!".

## 🌟 Demonstration

This project illustrates the essential principles of IPC using a straightforward case inversion example:

- **Process 1 (Parent)** sends "Hi There!" to **Process 2 (Child)**.
- **Process 2 (Child)** receives the message, inverts the case, and sends "hI tHERE!" back to **Process 1 (Parent)**.

\`\`\`plaintext
$ gcc [sourcefile] -o [executable]
$ ./[executable] "Learning is fun!"

Parent([pid]): Shares "Learning is fun!" with Child
Child([pid]): Message received and transformed
Child([pid]): Case inversion complete, sending back
Parent([pid]): Receives "lEARNING IS FUN!" from Child
\`\`\`

### Dive Into the Mechanics

The program employs two pipes:
- One for transmitting the original message from Process 1 to Process 2.
- Another for delivering the case-inverted message from Process 2 back to Process 1.

## 💡 Contribute & Learn

Dive into the Processes-N-Pipes project! Your contributions, whether they're new features, bug fixes, or documentation improvements, are a fantastic way to deepen your understanding of IPC and contribute to the learning community.

## 📜 License

Distributed under the MIT License. See \`LICENSE\` for more information.

## 🤝 Support & Questions

Encountered a challenge? Have a question? Open an issue on our GitHub issue tracker for support and guidance.

**Embark on your IPC learning journey with Processes-N-Pipes and enjoy the adventure of communication between processes!**
