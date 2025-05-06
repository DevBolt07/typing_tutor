#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>  // For getch(), Windows only

#define MAX_LINE 256

// ANSI color codes
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_RESET "\033[0m"

char username[50];  // Global to use in file functions

char *easyText[] = {
    "the cat sat on the mat",
    "typing is fun and easy",
    "practice makes perfect",
};

char *mediumText[] = {
    "programming in c is powerful",
    "command line applications are fast",
    "debugging helps improve skills",
};

char *hardText[] = {
    "multithreading and memory management require attention",
    "system programming involves detailed understanding",
    "low level coding is efficient but complex",
};

char *getTextByDifficulty(int level) {
    switch (level) {
        case 1: return easyText[rand() % 3];
        case 2: return mediumText[rand() % 3];
        case 3: return hardText[rand() % 3];
        default: return easyText[0];
    }
}

void saveStatsToFile(const char *difficultyLabel, double timeTaken, double accuracy, double wpm) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_stats.txt", username);

    FILE *file = fopen(filename, "a");
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

void showResults(const char *original, const char *typed, double timeTaken, int difficulty) {
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

    const char *levelName = (difficulty == 1) ? "Easy" : (difficulty == 2) ? "Medium" : "Hard";
    saveStatsToFile(levelName, timeTaken, accuracy, wpm);
}

void startTypingTest(int difficulty) {
    char typed[MAX_LINE] = {0};
    const char *text = getTextByDifficulty(difficulty);

    printf("\nType the following:\n%s\n\n", text);
    printf("Start typing (real-time feedback):\n");

    clock_t start = clock();
    int i = 0;
    while (text[i] != '\0') {
        char ch = getch();

        if (ch == 13) { // Enter key
            break;
        }

        typed[i] = ch;

        if (ch == text[i]) {
            printf(COLOR_GREEN "%c" COLOR_RESET, ch);
        } else {
            printf(COLOR_RED "%c" COLOR_RESET, ch);
        }

        i++;
    }
    clock_t end = clock();

    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    typed[i] = '\0';

    showResults(text, typed, timeTaken, difficulty);
}

int main() {
    int choice;

    srand(time(0));

    // Login/Profile Setup
    printf("Enter your name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;  // remove newline

    printf("Welcome, %s! Let's begin.\n", username);

    while (1) {
        printf("\n=== CMDTYPIST - Typing Tutor ===\n");
        printf("1. Start Typing Test (Easy)\n");
        printf("2. Start Typing Test (Medium)\n");
        printf("3. Start Typing Test (Hard)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            printf("Invalid input. Try again.\n");
            continue;
        }
        getchar();  // consume newline

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
