#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>  // For getch(), Windows only

#define MAX_LINE 256

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
        case 1:
            return easyText[rand() % 3];
        case 2:
            return mediumText[rand() % 3];
        case 3:
            return hardText[rand() % 3];
        default:
            return easyText[0];
    }
}

void showResults(const char *original, const char *typed, double timeTaken) {
    int correct = 0, total = strlen(original);
    for (int i = 0; i < total; i++) {
        if (original[i] == typed[i])
            correct++;
    }
    double accuracy = ((double)correct / total) * 100;
    double wpm = ((double)strlen(typed) / 5) / (timeTaken / 60);

    printf("\n\n--- Results ---\n");
    printf("Time taken: %.2f seconds\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Words per minute (WPM): %.2f\n", wpm);
}

void startTypingTest(int difficulty) {
    char typed[MAX_LINE];
    const char *text = getTextByDifficulty(difficulty);

    printf("\nType the following:\n%s\n\n", text);
    printf("Your input: ");

    time_t start = time(NULL);
    fgets(typed, MAX_LINE, stdin);
    time_t end = time(NULL);

    // Remove newline character
    typed[strcspn(typed, "\n")] = 0;

    double timeTaken = difftime(end, start);
    showResults(text, typed, timeTaken);
}

int main() {
    int choice;

    srand(time(0));

    while (1) {
        printf("\n=== CMDTYPIST - Typing Tutor ===\n");
        printf("1. Start Typing Test (Easy)\n");
        printf("2. Start Typing Test (Medium)\n");
        printf("3. Start Typing Test (Hard)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        if (choice == 4) {
            printf("Goodbye!\n");
            break;
        } else if (choice >= 1 && choice <= 3) {
            startTypingTest(choice);
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}