#include <stdio.h>  // Standard input/output library
#include <string.h> // String handling library
#include <ctype.h>  // Character handling library
#include <stdlib.h> // Standard library
#include <time.h>   // Time library

#define TEAM_NUMBER_SIZE 9      // Maximum number of teams
#define KIT_NUMBER_MAX 99       // Maximum kit number
#define KIT_NUMBER_MIN 1        // Minimum kit number
#define CLUB_NAME_SIZE 25       // Maximum club name size
#define SQUAD_SIZE 25           // Maximum squad size
#define TEAM_NAME_SIZE 20       // Maximum team name size
#define PLAYER_NAME_SIZE 25     // Maximum player name size
#define POSITION_SIZE 20        // Maximum position size

typedef struct {
    int day;        // Day of birth
    int month;      // Month of birth
    int year;       // Year of birth
} age_t;           // Age structure

typedef struct {
    char name[PLAYER_NAME_SIZE];    // Player name
    int kit_num;                    // Kit number
    char club[TEAM_NAME_SIZE];      // Club name
    age_t date_of_birth;            // Date of birth
    char position[POSITION_SIZE];   // Position
} player_t;                        // Player structure

typedef struct {
    char name[TEAM_NAME_SIZE];      // Team name
    player_t players[SQUAD_SIZE];   // Players in the team
    int activeSize;                 // Number of active players
} team_t;                        // Team structure

// FUNCTION PROTOTYPES
void display_menu(void); // Display the menu
void enroll_club(team_t teams[], int *num_teams); // enroll a club function 
void add_player(team_t teams[], int num_teams);  // Add a player to a team function
void search_update(team_t teams[], int num_teams); // Search and update player details function
void display_club_statistics(team_t teams[], int num_teams); // Display club statistics function
void handle_error(const char* message); // Handle error function
float avg_age_calculation(player_t players[], int players_number); // Calculate average age function
int is_valid_kit_num(team_t teams[], int num_teams, const char* name_club, int kit_num); // Check if kit number is valid
int get_team_index(team_t teams[], int num_teams, const char* name_club); // Get team index function
int validate_date(int day, int month, int year); // Validate date function
void clear_input_buffer(void); // Clear input buffer function

int main() {
    team_t teams[TEAM_NUMBER_SIZE]; // Array of teams
    int num_teams = 0;             // Number of teams

    while (1) { // Infinite loop
        display_menu(); // Display the menu function call

        int choice; // User choice
        printf("Enter choice: "); // Prompt user for choice
        if (scanf("%d", &choice) != 1) { // Check if input is a number
            clear_input_buffer(); // Clear input buffer
            handle_error("Invalid input. Please enter a number."); // Handle error
            continue; // Continue to next iteration
        }
        clear_input_buffer(); // Clear input buffer

        switch (choice) { // Switch statement based on user choice
            case 1: // Case 1
                enroll_club(teams, &num_teams); // Enroll a club function call
                break; // Break from switch statement
            case 2: // Case 2
                add_player(teams, num_teams); // Add a player to a team function call
                break; // Break from switch statement
            case 3: // Case 3
                search_update(teams, num_teams); // Search and update player details function call
                break; // Break from switch statement
            case 4: // Case 4
                display_club_statistics(teams, num_teams); // Display club statistics function call
                break;  // Break from switch statement
            case 5: // Case 5
                printf("Exiting the program.\n"); // Print exit message
                return 0; // Exit the program
            default: // Default case
                handle_error("Invalid choice. Please enter a number between 1 and 5."); // Handle error
        }
    }
    return 0;
}

// FUNCTION DEFINITIONS
// Clear input buffer function definition
void clear_input_buffer(void) {
    int c; // Character variable
    while ((c = getchar()) != '\n' && c != EOF); // Loop until newline or end of file is encountered
}

// Display menu function definition
void display_menu(void) { 
    printf("\n=== Management System for Sports League ===\n"); // Print menu header
    printf("1. Enroll a club\n"); // Print menu options
    printf("2. Add a player to a team\n");
    printf("3. Search and update player details\n");
    printf("4. Display club statistics\n");
    printf("5. Exit\n");
    printf("____________________________________\n"); // Print menu footer
}

void enroll_club(team_t teams[], int *num_teams) {
    if (*num_teams >= TEAM_NUMBER_SIZE) { // Check if maximum number of teams is reached
        handle_error("Maximum number of teams reached."); // Handle error
        return; // Return from function
    }

    char name_club[CLUB_NAME_SIZE]; // Club name variable
    printf("Enter the name of the club: "); // Prompt user for club name
    if (scanf("%24s", name_club) != 1) {  // Limit input to 24 chars to leave room for null terminator
        clear_input_buffer(); // Clear input buffer
        handle_error("Invalid club name."); // Handle error
        return; // Return from function
    }
    clear_input_buffer(); // Clear input buffer

    if (get_team_index(teams, *num_teams, name_club) != -1) { // Check if club name already exists
        handle_error("Club name already exists."); // Handle error
        return;
    }

    strncpy(teams[*num_teams].name, name_club, TEAM_NAME_SIZE - 1); // Copy club name to team structure
    teams[*num_teams].name[TEAM_NAME_SIZE - 1] = '\0'; // Null terminate the club name
    teams[*num_teams].activeSize = 0;   // Initialize active size to 0
    (*num_teams)++; // Increment number of teams
    
    printf("Club successfully enrolled.\n"); // Print success message
}

// Add a player to a team function definition
void add_player(team_t teams[], int num_teams) {
    if (num_teams == 0) { // Check if number of teams is 0
        handle_error("No clubs enrolled yet."); // Handle error
        return;
    }

    char name_club[CLUB_NAME_SIZE]; // Club name variable
    printf("Enter the name of the club: "); // Prompt user for club name
    scanf("%24s", name_club);  // Limit input to 24 chars to leave room for null terminator
    clear_input_buffer(); // Clear input buffer

    int team_index = get_team_index(teams, num_teams, name_club); // Get team index
    if (team_index == -1) { // Check if team index is valid
        handle_error("Club name does not exist."); // Handle error
        return;
    }

    if (teams[team_index].activeSize >= SQUAD_SIZE) { // Check if squad is full
        handle_error("Team squad is full."); // Handle error
        return;
    }

    player_t new_player; // New player variable
    printf("Enter the player's name: "); // Prompt user for player name
    scanf("%24s", new_player.name); // Read player name
    clear_input_buffer(); // Clear input buffer

    printf("Enter the player's kit number (%d-%d): ", KIT_NUMBER_MIN, KIT_NUMBER_MAX); // Prompt user for kit number
    if (scanf("%d", &new_player.kit_num) != 1) { // Check if input is a number
        clear_input_buffer();   // Clear input buffer
        handle_error("Invalid kit number."); // Handle error
        return;
    }
    clear_input_buffer(); // Clear input buffer

    if (new_player.kit_num < KIT_NUMBER_MIN || new_player.kit_num > KIT_NUMBER_MAX) { // Check if kit number is within range
        handle_error("Invalid kit number range."); // Handle error
        return; // Return from function
    }

    if (!is_valid_kit_num(teams, num_teams, name_club, new_player.kit_num)) { // Check if kit number is valid
        handle_error("Kit number already exists in the club."); // Handle error
        return;
    }

    printf("Enter the player's date of birth (DD MM YYYY): "); // Prompt user for date of birth
    if (scanf("%d %d %d", &new_player.date_of_birth.day, 
              &new_player.date_of_birth.month, 
              &new_player.date_of_birth.year) != 3) { // Check if input is a date
        clear_input_buffer(); // Clear input buffer
        handle_error("Invalid date format."); // Handle error
        return;
    }
    clear_input_buffer(); // Clear input buffer

    if (!validate_date(new_player.date_of_birth.day, 
                      new_player.date_of_birth.month, 
                      new_player.date_of_birth.year)) { // Check if date is valid
        handle_error("Invalid date."); // Handle error
        return;
    }

    printf("Enter the player's position: "); // Prompt user for player position
    scanf("%19s", new_player.position); // Limit input to 19 chars to leave room for null terminator
    clear_input_buffer(); // Clear input buffer

    strncpy(new_player.club, name_club, TEAM_NAME_SIZE - 1); // Copy club name to player structure
    new_player.club[TEAM_NAME_SIZE - 1] = '\0'; // Null terminate the club name
    
    teams[team_index].players[teams[team_index].activeSize] = new_player; // Add player to team
    teams[team_index].activeSize++; // Increment active size

    printf("Player successfully added to the team.\n"); // Print message
}

// Search and update player details function definition
void search_update(team_t teams[], int num_teams) { 
    if (num_teams == 0) { // Check if number of teams is 0
        handle_error("No clubs enrolled yet."); // Handle error
        return; // Return from function
    }

    char name_club[CLUB_NAME_SIZE]; // Club name variable
    printf("Enter the name of the club: "); // Prompt user for club name
    scanf("%24s", name_club); // Read club name
    clear_input_buffer(); // Clear input buffer

    int team_index = get_team_index(teams, num_teams, name_club); // Get team index
    if (team_index == -1) { // Check if team index is valid
        handle_error("Club name does not exist."); // Handle error
        return;
    }

    int kit_num; // Kit number variable
    printf("Enter the player's kit number: "); // Prompt user for kit number
    if (scanf("%d", &kit_num) != 1) { // Check if input is a number
        clear_input_buffer(); // Clear input buffer
        handle_error("Invalid kit number."); // Handle error
        return;
    }
    clear_input_buffer(); // Clear input buffer

    int player_index = -1; // Player index variable
    for (int i = 0; i < teams[team_index].activeSize; i++) { // Iterate through players in the team
        if (teams[team_index].players[i].kit_num == kit_num) { // Check if kit number matches
            player_index = i; // Set player index
            break; // Break from loop
        }
    }

    if (player_index == -1) { // Check if player index is valid
        handle_error("Player not found in the club."); // Handle error
        return; // Return from function
    }

    player_t *player = &teams[team_index].players[player_index]; // Get player pointer
    printf("\nCurrent Player Details:\n"); // Print current player details
    printf("Name: %s\n", player->name); // Print player name
    printf("Kit Number: %d\n", player->kit_num); // Print kit number
    printf("Date of Birth: %d/%d/%d\n", player->date_of_birth.day, 
           player->date_of_birth.month, player->date_of_birth.year); // Print date of birth
    printf("Position: %s\n\n", player->position); // Print position

    printf("Enter new details:\n"); // Prompt user for new details
    
    printf("Enter the new player's name: "); // Prompt user for new player name
    scanf("%24s", player->name); // Read new player name
    clear_input_buffer(); // Clear input buffer

    printf("Enter the new player's kit number (%d-%d): ", KIT_NUMBER_MIN, KIT_NUMBER_MAX); // Prompt user for new kit number
    int new_kit_num; // New kit number variable
    if (scanf("%d", &new_kit_num) != 1) { // Check if input is a number
        clear_input_buffer(); // Clear input buffer
        handle_error("Invalid kit number."); // Handle error
        return;
    }
    clear_input_buffer(); // Clear input buffer

    if (new_kit_num != kit_num && !is_valid_kit_num(teams, num_teams, name_club, new_kit_num)) { // Check if new kit number is valid
        handle_error("New kit number already exists in the club."); // Handle error
        return;
    }
    player->kit_num = new_kit_num; // Update kit number

    printf("Enter the new player's date of birth (DD MM YYYY): "); // Prompt user for new date of birth
    if (scanf("%d %d %d", &player->date_of_birth.day, 
              &player->date_of_birth.month, 
              &player->date_of_birth.year) != 3) { // Check if input is a date
        clear_input_buffer(); // Clear input buffer
        handle_error("Invalid date format."); // Handle error
        return; // Return from function
    }
    clear_input_buffer(); // Clear input buffer

    if (!validate_date(player->date_of_birth.day, 
                      player->date_of_birth.month, 
                      player->date_of_birth.year)) { // Check if date is valid
        handle_error("Invalid date."); // Handle error
        return;
    }

    printf("Enter the new player's position: "); // Prompt user for new player position
    scanf("%19s", player->position); // Read new player position
    clear_input_buffer(); // Clear input buffer

    printf("Player details successfully updated.\n"); // Print success message
}

// Display club statistics function
void display_club_statistics(team_t teams[], int num_teams) {
    if (num_teams == 0) { // Check if number of teams is 0
        handle_error("No clubs enrolled yet."); // Handle error
        return;
    }

    char name_club[CLUB_NAME_SIZE]; // Club name variable
    printf("Enter the name of the club: "); // Prompt user for club name
    scanf("%24s", name_club); // Read club name
    clear_input_buffer(); // Clear input buffer

    int team_index = get_team_index(teams, num_teams, name_club); // Get team index
    if (team_index == -1) { // Check if team index is valid
        handle_error("Club name does not exist."); // Handle error
        return; // Return from function
    }

    team_t *team = &teams[team_index]; // Get team pointer
    
    printf("\nClub Statistics for %s:\n", team->name); // Print club statistics
    printf("Number of players: %d\n", team->activeSize); // Print number of players
    
    if (team->activeSize > 0) { // Check if number of players is greater than 0
        float avg_age = avg_age_calculation(team->players, team->activeSize); // Calculate average age
        printf("Average age of players: %.2f years\n", avg_age); // Print average age
        
        printf("\nPlayer List:\n"); // Print player list
        printf("%-25s %-15s %-15s %-15s\n", "Name", "Kit Number", "Position", "Age"); // Print column headers
        printf("------------------------------------------------------------\n"); 
        
        time_t t = time(NULL); // Get current time
        struct tm* current_time = localtime(&t); // Get local time
        int current_year = current_time->tm_year + 1900; // Get current year
        
        for (int i = 0; i < team->activeSize; i++) { // Iterate through players
            player_t *player = &team->players[i]; // Get player pointer
            int age = current_year - player->date_of_birth.year; // Calculate age
            printf("%-25s %-15d %-15s %-15d\n", 
                   player->name, player->kit_num, player->position, age); // Print player details
        }
    }
}

// Handle error function
void handle_error(const char* message) {
    printf("\nError: %s\n", message); // Print error message
}

// Calculate average age function definition
float avg_age_calculation(player_t players[], int players_number) {
    if (players_number == 0) return 0; // Check if number of players is 0

    time_t t = time(NULL); // Get current time
    struct tm* current_time = localtime(&t);    // Get local time
    int current_year = current_time->tm_year + 1900; // Get current year

    int total_age = 0; // Initialize total age
    for (int i = 0; i < players_number; i++) { // Iterate through players
        total_age += current_year - players[i].date_of_birth.year; // Calculate total age
    }

    return (float)total_age / players_number; // Calculate and return average age
}

// Check if kit number is valid 
int is_valid_kit_num(team_t teams[], int num_teams, const char* name_club, int kit_num) {
    if (kit_num < KIT_NUMBER_MIN || kit_num > KIT_NUMBER_MAX) { // Check if kit number is within range
        return 0; 
    }

    int team_index = get_team_index(teams, num_teams, name_club); // Get team index
    if (team_index == -1) { // Check if team index is valid
        return 0;
    }

    for (int i = 0; i < teams[team_index].activeSize; i++) { // Iterate through players in the team
        if (teams[team_index].players[i].kit_num == kit_num) { // Check if kit number already exists
            return 0;
        }
    }

    return 1;
}

// Get team index function 
int get_team_index(team_t teams[], int num_teams, const char* name_club) { 
    for (int i = 0; i < num_teams; i++) { // Iterate through teams
        if (strcmp(teams[i].name, name_club) == 0) { // Check if club name matches
            return i; // Return team index
        }
    }
    return -1; // Return -1 if club name not found
}

// Validate date function
int validate_date(int day, int month, int year) {
    time_t t = time(NULL); // Get current time
    struct tm* current_time = localtime(&t); // Get local time
    int current_year = current_time->tm_year + 1900; // Get current year
    
    if (year < 1900 || year > current_year) return 0; // Check if year is within range
    if (month < 1 || month > 12) return 0; // Check if month is within range
    
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Days in each month
    
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) { // Check for leap year
        days_in_month[1] = 29; // Update days in February for leap year
    }
    
    if (day < 1 || day > days_in_month[month - 1]) return 0; // Check if day is within range
    
    return 1;
}