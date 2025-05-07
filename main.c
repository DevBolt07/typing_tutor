#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>  // For getch(), Windows only
#include <windows.h>  // For Sleep()

#define MAX_LINE 256
#define MAX_LINES 100

// ANSI color codes
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_RESET "\033[0m"

char username[50];  // Global username

// Reads a random line from a given file
char* getRandomLineFromFile(const char* filename) {
    static char lines[MAX_LINES][MAX_LINE];
    int count = 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    while (fgets(lines[count], MAX_LINE, file) && count < MAX_LINES) {
        lines[count][strcspn(lines[count], "\n")] = '\0';  // Remove newline
        count++;
    }

    fclose(file);

    if (count == 0) return NULL;

    int index = rand() % count;
    return lines[index];
}

char* getTextByDifficulty(int level) {
    switch (level) {
        case 1: return getRandomLineFromFile("easy.txt");
        case 2: return getRandomLineFromFile("medium.txt");
        case 3: return getRandomLineFromFile("hard.txt");
        default: return getRandomLineFromFile("easy.txt");
    }
}

void saveStatsToFile(const char* difficultyLabel, double timeTaken, double accuracy, double wpm) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_stats.txt", username);

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error saving stats.\n");
        return;
    }

    time_t now = time(NULL);
    fprintf(file, "Date: %s", ctime(&now));
    fprintf(file, "Difficulty: %s | Time: %.2fs | Accuracy: %.2f%% | WPM: %.2f\n\n",
            difficultyLabel, timeTaken, accuracy, wpm);

    fclose(file);
}

void showResults(const char* original, const char* typed, double timeTaken, int difficulty) {
    int correct = 0, total = strlen(original);
    for (int i = 0; i < total && typed[i] != '\0'; i++) {
        if (original[i] == typed[i])
            correct++;
    }

    double accuracy = ((double)correct / total) * 100;
    double wpm = ((double)strlen(typed) / 5) / (timeTaken / 60);

    printf("\n\n--- Results ---\n");
    printf("Time taken: %.2f seconds\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Words per minute (WPM): %.2f\n", wpm);

    const char* levelName = (difficulty == 1) ? "Easy" : (difficulty == 2) ? "Medium" : "Hard";
    saveStatsToFile(levelName, timeTaken, accuracy, wpm);
}

void showCountdown(int seconds) {
    printf("Get ready! Starting in:\n");
    for (int i = seconds; i > 0; i--) {
        printf("%d...\r", i);
        fflush(stdout);
        Sleep(1000);  // Sleep for 1000 milliseconds (1 second)
    }
    printf("Go!        \n\n");
}

void startTypingTest(int difficulty) {
    char typed[MAX_LINE] = {0};
    char* text = getTextByDifficulty(difficulty);

    if (text == NULL) {
        printf("Could not load typing text.\n");
        return;
    }

    printf("\nType the following:\n%s\n\n", text);
    showCountdown(3);  // Visual countdown
    printf("Start typing (real-time feedback):\n");

    int i = 0, typedIndex = 0;
    clock_t start = 0, end = 0;
    int firstKeyPressed = 0;

    while (text[i] != '\0' && typedIndex < MAX_LINE - 1) {
        char ch = getch();

        // Start timing on first keystroke
        if (!firstKeyPressed) {
            start = clock();
            firstKeyPressed = 1;
        }

        // Handle Backspace key
        if (ch == '\b') {
            if (typedIndex > 0) {
                typedIndex--;
                printf("\b \b");
            }
            continue;
        }

        if (ch == 13) break;  // Enter key

        typed[typedIndex] = ch;

        if (ch == text[i]) {
            printf(COLOR_GREEN "%c" COLOR_RESET, ch);
        } else {
            printf(COLOR_RED "%c" COLOR_RESET, ch);
        }

        typedIndex++;
        i++;
    }

    end = clock();  // Stop timer
    typed[typedIndex] = '\0';
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    showResults(text, typed, timeTaken, difficulty);
}


int main() {
    int choice;

    srand(time(0));

    printf("Enter your name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;  // Remove newline

    printf("Welcome, %s! Let's begin.\n", username);

    while (1) {
        printf("\n=== CMDTYPIST - Typing Tutor ===\n");
        printf("1. Start Typing Test (Easy)\n");
        printf("2. Start Typing Test (Medium)\n");
        printf("3. Start Typing Test (Hard)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Clear invalid input
            printf("Invalid input. Try again.\n");
            continue;
        }
        getchar();  // Clear newline

        if (choice == 4) {
            printf("Goodbye, %s! Your progress is saved in %s_stats.txt\n", username, username);
            break;
        } else if (choice >= 1 && choice <= 3) {
            startTypingTest(choice);
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
