# Minishell (The Almighty!)

> A simple Unix shell built from scratch — part of the 42 School core curriculum.

![Shell](https://img.shields.io/badge/42%20Project-Minishell-1E1E1E?style=flat&logo=shell&logoColor=white)
![Language](https://img.shields.io/badge/C-100%25-blue)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

---

## 📚 Overview

Minishell is a minimal Unix shell that interprets and executes commands entered by the user. It supports features like pipes, redirections, environment variables, and built-in commands — all implemented in C.

This project develops a deep understanding of:
- Process and file descriptor management
- Signals
- Parsing and lexing
- Built-in commands and command execution
- Memory management in C

---

## ⚙️ Features

- 🧠 **Parsing:** Tokenization with quote and escape character handling
- 🔁 **Pipes & Redirections:** `|`, `>`, `<`, `>>`, heredoc (`<<`)
- 🏗️ **Built-in Commands:** `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- 🌎 **Environment Variable Handling**
- 🔔 **Signal Handling:** Proper behavior on `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- 🔧 **Executable Search & Execution:** Binary lookup via `PATH`
- 🧼 **Memory Management:** No leaks, full `valgrind` compliance

---

## 🛠️ Installation & Usage

```bash
git clone https://github.com/42-Minishell-Team-D/42-Minishell.git
cd 42-Minishell
make
./minishell
