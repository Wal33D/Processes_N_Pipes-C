# 🔄 Processes-N-Pipes: Enhanced IPC Demo with Delays

Welcome to **Processes-N-Pipes**, an advanced exploration into the realms of inter-process communication (IPC) using pipes. It now features a user-friendly terminal menu and customizable communication delays. This toolkit extends our initial case inversion example to include a variety of operations and demonstrates the effect of delays in IPC, making it a comprehensive educational tool for learners and educators alike.

## 🎯 Core Functionality

- **Extended IPC Operations**: Engage with a broader range of operations beyond case inversion, including uppercase transformation, palindrome creation, and random math operations on numbers.
- **Terminal Menu**: Navigate through the options easily with a simple-to-use terminal menu, enhancing user interaction.
- **Communication Delays**: Experience the impact of timing in IPC with deliberate delays introduced between parent and child processes, simulating real-world scenarios where processes operate at different speeds.
- **Educational Tool**: With these new features, delve deeper into IPC mechanics in a clear, engaging manner, perfect for those looking to enhance their understanding of process communication.

## 🛠 Getting Started

### Prerequisites

Prepare for this IPC journey with:

- A GCC compiler or any standard C compiler.
- Basic terminal operations.

### Installation & Compilation

Ensure your project directory is structured properly with `main.c` and `utilities.c` inside the `/src` folder and `utilities.h` inside the `/include` folder.

1. **Clone this repository:**
   ```bash
   git clone https://github.com/your-username/Processes-N-Pipes.git
   ```

2. **Navigate to the project directory:**
   ```bash
   cd Processes-N-Pipes
   ```

3. **Compile the project using the Makefile:**
   ```bash
   make
   ```

This will compile the source files from the `/src` directory and place the executable in the `/build` directory as defined in the Makefile.

## 📘 How to Play

After compiling, run the executable to access the terminal menu. You may optionally specify the delay (in seconds) as the first argument:

```bash
./build/processes-n-pipes [delay]
```

Follow the on-screen prompts to choose between various IPC demonstrations. When prompted, enter a message or a number based on your selection. Explore different functionalities and observe the impact of communication delays firsthand.

## 🌟 New Demonstrations & Features

This version introduces a terminal menu that allows users to select between different demonstrations:

- **Toggle and Return a Message**: Inverts the case of each character in a string.
- **Uppercase and Return a Message**: Converts a string to uppercase.
- **Palindrome and Return a Message**: Creates a palindrome from the input string.
- **Perform a Random Math Operation on a Number**: Executes a random math operation on a provided number.

Additionally, communications are delayed by default to better highlight process interaction. You can override the default 3‑second pause by providing a delay value on the command line when starting the program.

## 💡 Contribute & Learn

Dive into the Processes-N-Pipes project! Your contributions—whether new features, bug fixes, or documentation improvements—are a fantastic way to deepen your understanding of IPC and contribute to the learning community.

## 📜 License

Distributed under the MIT License. See `LICENSE` for more information.

## 🤝 Support & Questions

Encountered a challenge? Have a question? Open an issue on our GitHub issue tracker for support and guidance.

**Embark on your IPC learning journey with Processes-N-Pipes and enjoy the advanced adventure of communication between processes!**
