// needed directives
#include <stdio.h> // standard input/output library
#include <time.h> // time library
#include <stdbool.h> // boolean library
#include <stdlib.h> // standard library

// Admin password constant
#define PASSWORD_ADMIN 1234

// Coffee prices (AED)
float ESP_PRICE = 3.5; // price of Espresso
float CAP_PRICE = 4.5; // price of Cappuccino
float MOC_PRICE = 5.5; // price of Mocha

// Coffee ingredients
#define ESP_BEANS 8 // Espresso beans quantity
#define ESP_WATER 30 // Espresso water quantity

#define CAP_BEANS 8 // Cappuccino beans quantity
#define CAP_WATER 30 // Cappuccino water quantity
#define CAP_MILK 70 // Cappuccino milk quantity

#define MOC_BEANS 8 // Mocha beans quantity
#define MOC_WATER 39 // Mocha water quantity
#define MOC_MILK 160 // Mocha milk quantity
#define MOC_CHOC 35 // Mocha chocolate syrup quantity

// Alert: low threshold quantity for ingredients
#define LOW_BEANS 60 // low threshold for beans
#define LOW_WATER 200 // low threshold for water
#define LOW_MILK 200 // low threshold for milk
#define LOW_CHOC 60 // low threshold for chocolate syrup

int beans_amnt = 100; // initial quantity of coffee beans
int water_amnt = 500; // initial quantity of water
int milk_amnt = 500; // initial quantity of milk
int choc_amnt = 100; // initial quantity of chocolate syrup
float tot_sales = 0.0; // total sales
float price; // price of the coffee
int choice; // user's choice
int refill_beans, refill_water, refill_milk, refill_choc; // refill quantities variables

// Function prototypes
void ingredients_refill(); // Function to refill ingredients
void update_ingredients(int beans, int water, int milk, int choc); // Function to update ingredient quantities
void admin_op(); // Function to enter admin mode
void menu(); // Function to display coffee menu
void user_order(); // Function to take user's coffee order
void low_ingredients(); // Function to check if any ingredient is low
void coff_availability(); // Function to show available coffee options
void admin_menu(); // Function to display admin menu
void replenish_ingredients(); // Function to replenish ingredients
void change_coffee_price(); // Function to change coffee prices
void display_and_reset_sales(); // Function to display total sales and reset it

// main function 
int main() {
    while (true) { // infinite loop
        printf("Welcome to our coffee shop!\n"); // message for user 
        printf("1) Admin menu\n"); // main menu item
        printf("2) Customer menu\n"); // main menu item
        printf("3) Exit\n"); // exit option 
        printf("Enter your choice: \n"); // prompt for user to enter their choice
        scanf("%d", &choice); // takes input from the user

        switch (choice) { // switch is used instead of if statements
            case 1: // in case one, admin mode is entered
                admin_op(); // admin mode function is called
                break; // breaks the case
            case 2: // in case two, customer mode is entered
                menu(); // menu function is called
                user_order(); // user order function is called
                break; // breaks the case
            case 3: // in case three, the program is exited
                printf("Exiting...\n"); // a message is printed to the user
                return 0; 
            default: // in case of any other input, an error message is printed
                printf("Invalid choice! Please try again.\n"); // error message for the user
        }
    }

    return 0;
}

// Function Definitions
// Updates ingredients quantities based on the coffee choice
// Parameters: beans, water, milk, choc: quantities to be deducted
void update_ingredients(int beans, int water, int milk, int choc) {
    beans_amnt -= beans;
    water_amnt -= water;
    milk_amnt -= milk;
    choc_amnt -= choc;
}

// Admin password checker
// checks if the input password is equal to the password variable 
// the return type is void because the function is noot return anything 
void admin_op() {
    int password;
    printf("Enter the admin password: \n"); // printf a prompt to the user 
    scanf("%d", &password); // scanf takes input from the user

    if (password == PASSWORD_ADMIN) // if input password is equal to the password variable
    {
        printf("Welcome, Admin!\n"); // if they're equal, a message will be sent to the user
        admin_menu(); // admin menu function is called, to display the admin menu 
    } 
    else // otherwise a message will be printed to the user to deny them access
    {
        printf("Incorrect password! Access denied.\n");
    }
}

// Function to tell if the ingredients are low
void low_ingredients() // void because the function is not returning anything 
{
    if (beans_amnt < LOW_BEANS) // if the amount of beans is lower than the threshold value
    {
        printf("Low stock: Coffee beans\n"); // an alert message will be printed 
        printf("Amount Left: %d g\n", beans_amnt); // the amount left will be displayed
    }

    if (water_amnt < LOW_WATER) // if the amount of water is lower than the threshold value 
    {
        printf("Low stock: Water\n"); // a warning message will be displayed 
        printf("Amount left: %d ml\n", water_amnt); // the current low value will be displayed
    }

    if (milk_amnt < LOW_MILK) // if the amount of milk is lower than the threshold value 
    {
        printf("Low stock: Milk\n"); // an alert message will be displayed
        printf("Amount left: %d ml\n", milk_amnt); // the current low value will be displayed 
    }

    if (choc_amnt < LOW_CHOC) // if the amount of chocolate syrup is lower than the threshold value
    {
        printf("Low stock: Chocolate syrup\n"); // an alert message will be displayed
        printf("Amount left: %d ml\n", choc_amnt); // the current low value will be displayed
    }
}

// Admin menu function that displays admin options 
void admin_menu() { // void because the function is not returning anything 
    while (true) { // infinite loop while the condition is true
        int admin_choice; // initializing admin_choice variable
        printf("\nAdmin Menu:\n"); // \n to start a new line 
        printf("1: Display ingredient quantities and total sales\n"); // menu item
        printf("2: Replenish ingredients\n"); // menu item
        printf("3: Change coffee prices\n"); // menu item
        printf("4: Display and reset total sales\n"); // menu item
        printf("0: Exit Admin Mode\n"); // menu item
        scanf("%d", &admin_choice); // takes input and stores it in admin_choice

        switch (admin_choice) { // switch is more efficient than if statements 
            case 1: // in case one, current ingredients quantities are being displayed
                printf("Current ingredient quantities:\n"); // current quantities 
                printf("Coffee beans: %d g\n", beans_amnt); // current beans quanitity
                printf("Water: %d ml\n", water_amnt); // current water quantity
                printf("Milk: %d ml\n", milk_amnt); // current milk quantity
                printf("Chocolate syrup: %d ml\n", choc_amnt); // current chocolate syrup quantity
                printf("Total sales: %.2f AED\n", tot_sales); // displays total sale
                break; // breaks the case
            case 2: // in case two, ingredients are being refilled
                replenish_ingredients(); // replenish ingredients function is called
                break; // breaks the case
            case 3: // in case three, coffee prices are being changed
                change_coffee_price(); // change coffee prices function is called
                break; // breaks the case
            case 4: // in case four, total sales are being displayed and reset
                display_and_reset_sales(); // display and reset sales function is called
                break; // breaks the case
            case 0: // in case zero, the admin mode is exited
                printf("Exiting Admin Mode...\n"); // a message is printed to the user
                return; // returns to the main function
            default: // in case of any other input, an error message is printed
                printf("Invalid choice! Try again.\n"); // error message for the user
        }
    }
}

// Function to display total sales and reset it if needed
void display_and_reset_sales() { // void because the function is not returning anything
    printf("Total sales amount: %.2f AED\n", tot_sales); // displays total sales amount
    printf("Would you like to reset total sales to zero? (1 for yes, 0 for no): "); // message
    int reset_choice; // initializing reset_choice variable
    scanf("%d", &reset_choice); // takes input and stores it in reset_choice
    
    if (reset_choice == 1) { // if the user chooses to reset the total sales
        tot_sales = 0.0; // total sales is reset to zero
        printf("Total sales has been reset. Please collect the money from the machine.\n");
    } else { // if the user chooses not to reset the total sales
        printf("Total sales remains unchanged.\n"); // a message is printed to the user
    }
}

// Function to replenish ingredients with random quantities
void replenish_ingredients() { // void because the function is not returning anything
    srand(time(0)); // seed for random numbers
    beans_amnt = rand() % 101 + 100;  // Random refill between 100 and 200
    water_amnt = rand() % 301 + 300;  // Random refill between 300 and 600
    milk_amnt = rand() % 301 + 300;   // Random refill between 300 and 600
    choc_amnt = rand() % 101 + 50;    // Random refill between 50 and 150

    printf("Ingredients replenished:\n"); // a message is printed to the user
    printf("Coffee beans: %d g\n", beans_amnt); // displays the new beans quantity
    printf("Water: %d ml\n", water_amnt); // displays the new water quantity
    printf("Milk: %d ml\n", milk_amnt); // displays the new milk quantity
    printf("Chocolate syrup: %d ml\n", choc_amnt); // displays the new chocolate syrup quantity
}

// Function to change coffee prices
void change_coffee_price() { // void because the function is not returning anything
    int coffee_choice; // initializing coffee_choice variable
    printf("Select the coffee type to change its price:\n"); // a message is printed to the user
    printf("1: Espresso\n2: Cappuccino\n3: Mocha\n"); // menu items
    scanf("%d", &coffee_choice); // takes input and stores it in coffee_choice

    switch (coffee_choice) { // switch is used instead of if statements
        case 1: // in case one, the price of Espresso is being changed
            printf("Enter new price for Espresso: "); // a message is printed to the user
            scanf("%f", &ESP_PRICE); // takes input and stores it in ESP_PRICE
            break; // breaks the case
        case 2: // in case two, the price of Cappuccino is being changed
            printf("Enter new price for Cappuccino: "); // a message for user
            scanf("%f", &CAP_PRICE); // takes input and stores it in CAP_PRICE
            break; // breaks the case
        case 3: // in case three, the price of Mocha is being changed
            printf("Enter new price for Mocha: "); // a message for user
            scanf("%f", &MOC_PRICE); // takes input and stores it in MOC_PRICE
            break; // breaks the case
        default: // in case of any other input, an error message is printed
            printf("Invalid choice!\n");
    }

    printf("Prices updated successfully!\n"); // a message is printed to the user
}

// Function to display the coffee menu
void menu() { // void because the function is not returning anything
    printf("Menu: \n"); // a message is printed to the user
    printf("1) Espresso: %.2f AED\n", ESP_PRICE); // displays the price of Espresso
    printf("2) Cappuccino: %.2f AED\n", CAP_PRICE); // displays the price of Cappuccino
    printf("3) Mocha: %.2f AED\n", MOC_PRICE); // displays the price of Mocha
}

// Function to take user's coffee order with confirmation and payment 
void user_order() { // void because the function is not returning anything
    int order_choice;  // Variable to store user's coffee choice

    while (true) { // Infinite loop for user to keep ordering
        coff_availability();  // Show available coffee options

        printf("Enter your selection (1 for Espresso, 2 for Cappuccino, 3 for Mocha, 0 to exit): ");
        scanf("%d", &order_choice); // Take user's choice

        if (order_choice == 0) { // Exit order menu
            printf("Exiting order menu...\n"); // a message is printed to the user for exiting
            return; // returns to the main function
        }

        switch (order_choice) { // switch is used instead of if statements
            case 1:  // Espresso 
                if (beans_amnt >= ESP_BEANS && water_amnt >= ESP_WATER) { // Check if ingredients are sufficient
                    price = ESP_PRICE; // Set price
                    printf("You selected Espresso. Price: %.2f AED. Confirm? (1 for yes, 0 for no): ", price); // confirmation 
                } else { // If ingredients are insufficient
                    printf("Espresso is unavailable due to insufficient ingredients.\n"); // user message
                    continue; // continue to the next iteration
                }
                break; // breaks the case

            case 2:  // Cappuccino
                if (beans_amnt >= CAP_BEANS && water_amnt >= CAP_WATER && milk_amnt >= CAP_MILK) { // Check if ingredients are sufficient
                    price = CAP_PRICE; // Set price
                    printf("You selected Cappuccino. Price: %.2f AED. Confirm? (1 for yes, 0 for no): ", price); // confirmation
                } else { // If ingredients are insufficient
                    printf("Cappuccino is unavailable due to insufficient ingredients.\n"); // user message
                    continue; // continue to the next iteration
                }
                break; // breaks the case

            case 3:  // Mocha
                if (beans_amnt >= MOC_BEANS && water_amnt >= MOC_WATER && milk_amnt >= MOC_MILK && choc_amnt >= MOC_CHOC) { // Check if ingredients are sufficient
                    price = MOC_PRICE; // Set price 
                    printf("You selected Mocha. Price: %.2f AED. Confirm? (1 for yes, 0 for no): ", price); // confirmation
                } else { // If ingredients are insufficient
                    printf("Mocha is unavailable due to insufficient ingredients.\n"); // user message
                    continue; // continue to the next iteration
                }
                break; // breaks the case

            default: // If user enters an invalid choice
                printf("Invalid choice! Please try again.\n"); // a message is printed to the user
                continue; // continue to the next iteration
        }

        int confirm; // Variable to store user's confirmation
        scanf("%d", &confirm); // Take user's confirmation

        if (confirm == 1) { // If user confirms the order
            // Process payment
            float payment = 0; // Variable to store user's payment
            while (payment < price) { // Loop until payment is sufficient
                float coin; // Variable to store user's coin
                printf("Insert coins (1 AED or 0.5 AED): "); // a message is printed to the user
                scanf("%f", &coin); // Take user's coin

                if (coin == 1.0 || coin == 0.5) { // If user inserts a valid coin
                    payment += coin; // Add coin to payment
                } else { // If user inserts an invalid coin
                    printf("Invalid coin! Please collect it and insert a valid one.\n"); // message for user
                }
            }

            printf("You paid: %.2f AED. Coffee cost: %.2f AED. Change: %.2f AED.\n", payment, price, payment - price); // a message is printed to the user
            tot_sales += price; // Add price to total sales

            // Deduct ingredients based on the choice
            switch (order_choice) { // switch is used instead of if statements
                case 1:  // Espresso
                    update_ingredients(ESP_BEANS, ESP_WATER, 0, 0); // Update ingredients
                    break; // breaks the case
                case 2:  // Cappuccino
                    update_ingredients(CAP_BEANS, CAP_WATER, CAP_MILK, 0); // Update ingredients
                    break; // breaks the case
                case 3:  // Mocha
                    update_ingredients(MOC_BEANS, MOC_WATER, MOC_MILK, MOC_CHOC); // Update ingredients
                    break; // breaks the case
            }

            printf("Enjoy your coffee!\n"); // a message is printed to the user
            low_ingredients();  // Check if any ingredient is low after serving
        } else { // If user cancels the order
            printf("Order canceled.\n"); // a message is printed to the user
        }
    }
}

// Function to show available coffee options
void coff_availability() { // void because the function is not returning anything
    if (beans_amnt >= ESP_BEANS && water_amnt >= ESP_WATER) { // Check if ingredients are sufficient
        printf("1) Espresso: %.2f AED\n", ESP_PRICE); // Display Espresso
    } else { // If ingredients are insufficient
        printf("1) Espresso: Unavailable due to temporarily insufficient ingredients\n"); // Display Espresso as unavailable
    }

    if (beans_amnt >= CAP_BEANS && water_amnt >= CAP_WATER && milk_amnt >= CAP_MILK) { // Check if ingredients are sufficient
        printf("2) Cappuccino: %.2f AED\n", CAP_PRICE); // Display Cappuccino
    } else { // If ingredients are insufficient
        printf("2) Cappuccino: Unavailable due to temporarily insufficient ingredients\n"); // Display Cappuccino as unavailable
    }

    if (beans_amnt >= MOC_BEANS && water_amnt >= MOC_WATER && milk_amnt >= MOC_MILK && choc_amnt >= MOC_CHOC) { // Check if ingredients are sufficient for mocha
        printf("3) Mocha: %.2f AED\n", MOC_PRICE); // Display Mocha
    } else { // If ingredients are insufficient
        printf("3) Mocha: Unavailable due to temporarily insufficient ingredients\n"); // Display Mocha as unavailable
    }

    if (beans_amnt < ESP_BEANS && beans_amnt < CAP_BEANS && beans_amnt < MOC_BEANS) { // Check if beans are low
        printf("No coffee can be served due to insufficient ingredients.\n"); // Display message
    }
}