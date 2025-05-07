# CMDTYPIST - Command Line Typing Tutor

CMDTYPIST is a lightweight, console-based typing tutor application designed to help users improve their typing speed and accuracy through interactive typing tests with real-time feedback.

![CMDTYPIST Screenshot](https://github.com/yourusername/cmdtypist/assets/screenshot.png)

## Features

- **Multiple Difficulty Levels**: Easy, Medium, and Hard typing challenges
- **Real-time Feedback**: Color-coded feedback showing correct and incorrect keystrokes
- **Performance Metrics**: Track your typing speed (WPM), accuracy, and time
- **User Profiles**: Save your progress and statistics to personal log files
- **Customizable Text**: Easily add your own typing samples by modifying text files

## Requirements

- Windows OS
- C compiler (GCC recommended)
- Text files for typing samples (easy.txt, medium.txt, hard.txt)

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/cmdtypist.git
   ```

2. Navigate to the project directory:
   ```
   cd cmdtypist
   ```

3. Compile the program:
   ```
   gcc -o cmdtypist main.c
   ```

4. Create text files with typing samples:
   - `easy.txt` - Short, simple sentences
   - `medium.txt` - Moderate length paragraphs
   - `hard.txt` - Complex, longer texts

## Usage

1. Run the executable:
   ```
   ./cmdtypist
   ```

2. Enter your username when prompted

3. Select a difficulty level from the menu:
   - 1: Easy
   - 2: Medium
   - 3: Hard
   - 4: Exit

4. Follow the on-screen instructions to complete the typing test

5. View your results and stats after each test

## Customization

You can customize the typing samples by editing the text files:

- `easy.txt` - For beginners or warm-up exercises
- `medium.txt` - For intermediate typists
- `hard.txt` - For advanced practice

Each line in these files represents one typing challenge.

## How the Program Works

1. The program selects a random line from the appropriate difficulty file
2. A 3-second countdown prepares you for the test
3. As you type, real-time feedback shows correct characters in green and incorrect in red
4. The program calculates:
   - WPM (Words Per Minute): Based on the standard definition of 5 characters per word
   - Accuracy: Percentage of keystrokes that were correct
   - Time taken to complete the test

5. Results are saved to a username-specific stats file

## Project Structure

```
cmdtypist/
├── main.c           # Main source code
├── easy.txt         # Easy difficulty typing samples
├── medium.txt       # Medium difficulty typing samples
├── hard.txt         # Hard difficulty typing samples
├── README.md        # This file
└── *_stats.txt      # User statistics (generated when used)
```

## Future Improvements

- Cross-platform support (currently Windows-only)
- More detailed statistics and graphs
- Typing lessons and tutorials
- Custom difficulty settings
- Multiplayer/competitive mode

## Author

Hemantkumar Shivaji Lakhane

## Acknowledgments

- Inspired by classic typing tutors
- Thanks to all contributors and testers