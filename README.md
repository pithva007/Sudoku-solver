# 🧩 Sudoku Solver & Player (C++)

A fully interactive **Sudoku Solver & Manual Gameplay Program** written in **C++**, featuring:

* ANSI **colored output** for beautifully formatted terminal UI
* **Backtracking algorithm** to auto‑solve Sudoku
* **Manual gameplay mode** for users to play step‑by‑step
* **User input validation**
* **Puzzle reset**, **custom puzzle input**, and **current grid display** options

This project is perfect for learning:

* Backtracking
* 2D array manipulation
* Input handling and validation in C++
* Creating interactive console applications

---

## 🚀 Features

### ✔️ Sudoku Solver (Backtracking)

Automatically solves any valid Sudoku puzzle using a depth‑first search and backtracking algorithm.

### ✔️ Manual Sudoku Gameplay

Allows users to fill the grid manually.

* Highlights original numbers in **bold white**
* Highlights user moves in **green**
* Blocks changes to original cells
* Checks for row/column/box rule violations

### ✔️ Colored UI Using ANSI Escape Codes

Colors used:

* **White Bold** → Original puzzle numbers
* **Green** → Player‑entered / solver‑filled numbers
* **Red** → Error messages
* **Blue** → Grid border

### ✔️ Easy Grid Management

* Reset puzzle
* Display puzzle
* Enter a brand‑new puzzle
* Solve the current puzzle
* Menu‑driven system

---

## 📌 How the Program Works

### Main Menu Options:

1. **Solution of the Puzzle** → Shows the AI‑solved grid
2. **Solve Puzzle Manually** → Play the Sudoku yourself
3. **Enter a New Puzzle** → Input your own 9×9 Sudoku
4. **Reset to Original Puzzle**
5. **Display Current Puzzle**
6. **Exit**

---

## 🔍 Code Structure

### Core Files / Functions

* `solveSudoku()` → Backtracking solver
* `isSafe()` → Checks Sudoku rules
* `printGrid()` → Colored UI Sudoku printer
* `playSudoku()` → Manual gameplay loop
* `inputGrid()` → Takes full puzzle input from user
* `copyGrid()` → Clones a grid
* `isGridFull()` → Detects if Sudoku is completed

### ANSI Colors

```cpp
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"
```

---

## 📥 How to Compile and Run

### **Compile:**

```bash
g++ sudoku.cpp -o sudoku
```
### **Run:**
```bash
./sudoku
```

### **Direct Compile and run:**
```bash
g++ sudoku.cpp && ./a.out
```



---

## 🧠 Backtracking Algorithm (Explanation)

The solver uses recursion + backtracking:

1. Find the first empty cell (0)
2. Try numbers 1–9
3. Check if placing the number is safe
4. If safe, place it and recurse
5. If recursion fails, undo the move (**backtrack**) and try next number
6. Continue until solved or no solution exists

---

## 🖼️ Terminal Output Example (Colored Grid)

```
-------------------------
| 5 3 . | . 7 . | . . . |
| 6 . . | 1 9 5 | . . . |
| . 9 8 | . . . | . 6 . |
-------------------------
| 8 . . | . 6 . | . . 3 |
| 4 . . | 8 . 3 | . . 1 |
| 7 . . | . 2 . | . . 6 |
-------------------------
| . 6 . | . . . | 2 8 . |
| . . . | 4 1 9 | . . 5 |
| . . . | . 8 . | . 7 9 |
-------------------------

```

Colors will appear when running in a real terminal.

---

## 📦 Input Format

You may use **0 for empty cells**.

### ▶️ How to Enter a Move Manually (Row, Column, Number)

In *Manual Play Mode*, you will be asked:

You must enter **three numbers**:
```
Your move: row  column  number
```

For example:

```
3 5 8
```

This means:

* **Row 3**
* **Column 5**
* Place **number 8** there

### ✔️ Additional Rules:

* Enter numbers **1–9 only**
* Enter **0 0 0** to exit manual play mode
* You cannot change original puzzle numbers

Example row input (for full puzzle setup):
You may use **0 for empty cells**.
Example row:

```
0 3 0 0 7 0 0 0 0
```

---

## 🛠️ Requirements

* C++ compiler (G++ recommended)
* Terminal that supports ANSI colors (most Linux/macOS terminals)

Windows users may need to enable **VT sequence processing**.

---

## 🙌 Author

Created by **Khush Pithva**.

If you like this project, don’t forget to ⭐ star the repository! ✨
