#include <stdio.h>      // Standard input/output library
#include <stdlib.h>     // Standard library for general functions
#include <string.h>     // For string handling
#include <time.h>       // For time and date functions

// Function prototypes
float convertToFahrenheit(float celsius); // Converts Celsius to Fahrenheit
const char* evaluateAction(float currentF, float desiredF, const char* mode); // Determines the system action
void displayStatus(float currentC, float desiredC, float currentF, float desiredF, const char* action, const char* mode, const char* timeOfDay); // Displays the system status
void showIntro(); // Shows system introduction
void showMenu(); // Displays menu of modes
void logToFile(float currentC, float desiredC, float currentF, float desiredF, const char* action, const char* mode, const char* timeOfDay); // Logs data to file

int main() {
    float currentC, desiredC;          // Temperature in Celsius
    float currentF, desiredF;          // Temperature in Fahrenheit
    char proceed;                      // Stores user's choice to continue
    int modeChoice, timeChoice;        // Stores user-selected mode and time
    char mode[20];                     // String for mode name
    char timeOfDay[20];                // String for time of day

    showIntro(); // Display system intro

    do {
        showMenu(); // Show user the operating mode options

        // Ask user to select a valid mode (1-4)
        printf("Select operating mode (1-4): ");
        while (scanf("%d", &modeChoice) != 1 || modeChoice < 1 || modeChoice > 4) {
            printf("Invalid input. Enter a number between 1 and 4: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        // Assign string to mode based on user selection
        switch (modeChoice) {
            case 1: strcpy(mode, "Auto"); break;
            case 2: strcpy(mode, "Heating Only"); break;
            case 3: strcpy(mode, "Cooling Only"); break;
            case 4: strcpy(mode, "Manual Override"); break;
        }

        // Ask user to choose the time of day
        printf("\n--- Time of Day ---\n1. Morning\n2. Afternoon\n3. Night\nChoose: ");
        while (scanf("%d", &timeChoice) != 1 || timeChoice < 1 || timeChoice > 3) {
            printf("Invalid input. Choose 1-3: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        // Set default desired temperature based on time of day
        switch (timeChoice) {
            case 1: strcpy(timeOfDay, "Morning"); desiredC = 22.0; break;
            case 2: strcpy(timeOfDay, "Afternoon"); desiredC = 24.0; break;
            case 3: strcpy(timeOfDay, "Night"); desiredC = 20.0; break;
        }

        // If Manual Override mode is selected
        if (modeChoice == 4) {
            int manualOption;

            // Ask user to input current temperature
            printf("\nEnter current room temperature in Celsius: ");
            while (scanf("%f", &currentC) != 1) {
                printf("Invalid input. Please enter a number: ");
                while (getchar() != '\n'); // Clear buffer
            }

            // Manual control options
            printf("\nManual Override:\n1. Force Heating\n2. Force Cooling\n3. System Off\nSelect option: ");
            while (scanf("%d", &manualOption) != 1 || manualOption < 1 || manualOption > 3) {
                printf("Invalid input. Enter 1-3: ");
                while (getchar() != '\n');
            }

            // Convert current temperature to Fahrenheit
            currentF = convertToFahrenheit(currentC);
            desiredF = currentF; // Manual override sets desired same as current

            // Determine manual action based on user selection
            const char* action;
            if (manualOption == 1) action = "Heating (Manual)";
            else if (manualOption == 2) action = "Cooling (Manual)";
            else action = "System Off (Manual)";

            // Display status and log to file
            displayStatus(currentC, desiredC, currentF, desiredF, action, mode, timeOfDay);
            logToFile(currentC, desiredC, currentF, desiredF, action, mode, timeOfDay);
            goto ask_continue; // Skip rest and ask to repeat
        }

        // For automatic modes, ask current temperature
        printf("Enter current room temperature in Celsius: ");
        while (scanf("%f", &currentC) != 1) {
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n'); // Clear buffer
        }

        // Convert both temperatures to Fahrenheit
        currentF = convertToFahrenheit(currentC);
        desiredF = convertToFahrenheit(desiredC);

        // Determine system action based on mode and temperatures
        const char* action = evaluateAction(currentF, desiredF, mode);

        // Display the result and log it
        displayStatus(currentC, desiredC, currentF, desiredF, action, mode, timeOfDay);
        logToFile(currentC, desiredC, currentF, desiredF, action, mode, timeOfDay);

        // Ask user if they want to continue
        ask_continue:
        printf("\nWould you like to simulate again? (Y/N): ");
        scanf(" %c", &proceed);
        while (getchar() != '\n'); // Clear buffer
    } while (proceed == 'Y' || proceed == 'y');

    // End of simulation
    printf("\nSystem shutting down. Logs saved to 'system_log.txt'.\n");
    return 0;
}

// Function to convert Celsius to Fahrenheit
float convertToFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Evaluate action needed based on temperature and mode
const char* evaluateAction(float currentF, float desiredF, const char* mode) {
    if (strcmp(mode, "Auto") == 0) {
        if (currentF < desiredF - 3) return "Heating";      // Too cold
        else if (currentF > desiredF + 3) return "Cooling"; // Too hot
        else return "Ideal";                                // Within range
    } else if (strcmp(mode, "Heating Only") == 0) {
        return currentF < desiredF ? "Heating" : "Idle";    // Heat if needed
    } else if (strcmp(mode, "Cooling Only") == 0) {
        return currentF > desiredF ? "Cooling" : "Idle";    // Cool if needed
    }
    return "Idle"; // Default case
}

// Show the current status of the system
void displayStatus(float currentC, float desiredC, float currentF, float desiredF, const char* action, const char* mode, const char* timeOfDay) {
    printf("\n===== SYSTEM STATUS REPORT =====\n");
    printf("Time of Day: %s\n", timeOfDay);
    printf("Mode       : %s\n", mode);
    printf("Current    : %.2f°C / %.2f°F\n", currentC, currentF);
    printf("Target     : %.2f°C / %.2f°F\n", desiredC, desiredF);
    printf("Action     : %s\n", action);
    printf("================================\n");
}

// Display the introduction when program starts
void showIntro() {
    printf("===============================================\n");
    printf("   SMART HOME TEMPERATURE CONTROL SYSTEM V2.0\n");
    printf("===============================================\n");
    printf("Features:\n");
    printf("- Auto, Manual, Heating/Cooling modes\n");
    printf("- Time-based scheduling\n");
    printf("- Activity logging to 'system_log.txt'\n\n");
}

// Display the mode selection menu
void showMenu() {
    printf("\n--- Operating Modes ---\n");
    printf("1. Auto Mode (Auto Heating/Cooling)\n");
    printf("2. Heating Only Mode\n");
    printf("3. Cooling Only Mode\n");
    printf("4. Manual Override (Force Mode)\n");
}

// Log the status to a text file
void logToFile(float currentC, float desiredC, float currentF, float desiredF, const char* action, const char* mode, const char* timeOfDay) {
    FILE *log = fopen("system_log.txt", "a"); // Open file for appending
    if (log == NULL) {
        printf("Error opening log file.\n");
        return;
    }

    time_t now = time(NULL);           // Get current system time
    char *dt = ctime(&now);            // Convert time to readable format
    dt[strcspn(dt, "\n")] = 0;         // Remove newline character

    // Write log entry with all parameters
    fprintf(log, "[%s] Time: %s | Mode: %s | Current: %.2fC / %.2fF | Desired: %.2fC / %.2fF | Action: %s\n",
            dt, timeOfDay, mode, currentC, currentF, desiredC, desiredF, action);
    fclose(log); // Close file
}