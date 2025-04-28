
# CornerGrocerTracker  
By: Julliane Pamfilo  

=====================  
=====================  

Welcome to the Corner Grocer Tracker! This C++ program reads your daily shopping log and tells you how many times each produce item was purchased. It even creates a backup file so your data stays safe!

---

## What You’ll Need

- A C++ compiler that supports C++11 (like `g++` or Visual C++ Build Tools)
- (Optional) A text editor like Visual Studio Code
- The input file: `CS210_Project_Three_Input_File.txt` (one item per line)

---

## Quick Start

1. **Put your files together**  
   - `main.cpp` (the source code)  
   - `CS210_Project_Three_Input_File.txt` (your input data)  
   Make sure both files are in the same folder.

2. **Open a terminal** in that folder.

3. **Compile the program** by running:
   ```bash
   g++ -std=c++11 -Wall -o tracker main.cpp
   ```

4. **Run the program** by typing:
   ```bash
   ./tracker
   ```

---

## Project Reflection

### Project Summary
This project was all about making grocery inventory tracking easier. Instead of counting purchases manually, the program reads a file of shopping data and automatically tells you how many times each item was bought.

### What I Did Well
I kept my code clean, organized, and easy to read. I also made sure it was well-documented so anyone can understand and update it later.

### Where I Could Improve
I could strengthen the program by adding better error handling, like checking if the input file exists or if the data is formatted correctly. These improvements would make it more reliable and secure.

### Biggest Challenges
One of the toughest parts was figuring out how to count each item efficiently. I solved this by using a map data structure after reviewing some C++ examples and practicing with similar problems.

### Skills I Gained
This project helped me get more comfortable with file handling, using maps, and organizing larger programs — all of which are skills I can carry into other projects and classes.

### How I Made It Maintainable
I used clear function names, wrote helpful comments, and structured the code so it's easy to add new features later (like filtering by date or item category).

---

✅ **Reminder:** Make sure your GitHub repository includes:
- `main.cpp`
- `CS210_Project_Three_Input_File.txt`
- This updated `README.md`

---

## Commit Message
Add CornerGrocerTracker project and README reflection for CS 210 portfolio submission

- Added main.cpp (program source code)
- Added CS210_Project_Three_Input_File.txt (sample input data)
- Updated README.md with project summary, reflection, and setup instructions
