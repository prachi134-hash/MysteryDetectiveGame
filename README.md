# Mystery Detective – Text-Based Adventure Game in C++

![Mystery Detective](https://img.shields.io/badge/Language-C++-blue)

A console-based, story-driven detective game where the player investigates a mysterious crime in a small town. Explore locations, interact with NPCs, collect clues, solve puzzles, and ultimately identify the culprit. This game demonstrates object-oriented programming (OOP) concepts and interactive gameplay in C++.

---

## 🎮 Features

- **Interactive Locations:** Crime Scene, Library, River, Suspect House, Police Station  
- **Mini-Puzzles & Riddles:** Diary code, river riddle, and locked drawer code  
- **Inventory System:** Track clues and items collected during investigation  
- **NPC Interactions:** Talk to townspeople for hints  
- **Replayability:** Randomized culprit each game session  
- **Object-Oriented Design:** Uses classes for Player, Location, NPC, and Game logic  

---

## 🕹 How to Play

1. **Compile the Game**  
   Make sure you have a C++ compiler installed (e.g., g++).  
   ```bash
   g++ -std=c++17 game.cpp -o game.exe
   ```
2. **Run the Game**
```bash
./game.exe   # Windows PowerShell or CMD
```

3.**Gameplay Flow**

--Enter your detective name.
--Choose locations to explore by typing the number.
--Collect clues from the environment or by solving puzzles.
--Talk to NPCs for hints.
--Use clues to unlock mini-puzzles in Library, River, and Suspect House.
--Once you gather enough evidence, go to the Police Station to make your accusation.

4.**Winning the Game**

--Gather all critical clues including the Confession Letter.
--Accurately accuse the correct culprit at the Police Station.

MysteryDetectiveGame/
├─ game.cpp         # Main game source code
├─ README.md        # Project description and instructions

## 💻 Technologies

- C++ (C++17 standard)
- Object-Oriented Programming concepts: Classes, Inheritance, Polymorphism
- Standard Library: `<iostream>`, `<vector>`, `<string>`, `<algorithm>`, `<cstdlib>`, `<ctime>`

---

## 📌 Notes

- Make sure to compile the game in a folder where you have write permissions.
- The culprit is randomized each game session to enhance replayability.
- You can extend the game by adding more locations, puzzles, or NPCs for a richer experience.

