🎮 Hangman Game in C

This is a **terminal-based Hangman game** written in **C language**.  
The game selects a random word from a built-in word list and the player must guess the word letter-by-letter within a limited number of attempts.


✅ Features

- Random word is selected every game
- ASCII hangman graphic updates with each wrong guess
- Tracks and displays guessed letters
- Input validation (prevents repeated guesses)
- Cross-platform screen clearing (`cls` / `clear`)
- Replay option at the end of the game



🧠 How to Play

1. A word is chosen randomly and displayed as underscores.
2. You must **guess letters** one by one.
3. Correct guesses fill in the word.
4. Incorrect guesses draw parts of the hangman.
5. You **win** if you reveal the entire word.
6. You **lose** if the hangman drawing is completed (6 wrong attempts).


🛠️ Requirements

- C Compiler (GCC, Clang, MinGW, or any standard compiler)



🚀 Compilation & Running

**For Windows / Linux / Mac**
```bash
gcc hangman.c -o hangman
./hangman
