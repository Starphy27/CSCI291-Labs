// needed directives
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

// Admin password constant
#define PASSWORD_ADMIN 1234

// Coffee prices (AED)
float ESP_PRICE = 3.5;
float CAP_PRICE = 4.5;
float MOC_PRICE = 5.5;

// Coffee ingredients
#define ESP_BEANS 8
#define ESP_WATER 30

#define CAP_BEANS 8
#define CAP_WATER 30
#define CAP_MILK 70

#define MOC_BEANS 8
#define MOC_WATER 39
#define MOC_MILK 160
#define MOC_CHOC 35

// Alert: low threshold quantity for ingredients
#define LOW_BEANS 60
#define LOW_WATER 200
#define LOW_MILK 200
#define LOW_CHOC 60

int beans_amnt = 100;
int water_amnt = 500;
int milk_amnt = 500;
int choc_amnt = 100;
float tot_sales = 0.0;
float price;
int choice;
int refill_beans, refill_water, refill_milk, refill_choc;

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

// Function Definitions
// Updates ingredients quantities based on the coffee choice
void update_ingredients(int beans, int water, int milk, int choc) {
    beans_amnt -= beans;
    water_amnt -= water;
    milk_amnt -= milk;
    choc_amnt -= choc;
}

// Admin password checker
void admin_op() {
    int password;
    printf("Enter the admin password: \n");
    scanf("%d", &password);

    if (password == PASSWORD_ADMIN)
    {
        printf("Welcome, Admin!\n");
        admin_menu();
    } 
    else 
    {
        printf("Incorrect password! Access denied.\n");
    }
}

// Function to tell if the ingredients are low
void low_ingredients()
{
    if (beans_amnt < LOW_BEANS)
    {
        printf("Low stock: Coffee beans\n");
        printf("Amount Left: %d g\n", beans_amnt);\
    }

    if (water_amnt < LOW_WATER)
    {
        printf("Low stock: Water\n");
        printf("Amount left: %d ml\n", water_amnt);
    }

    if (milk_amnt < LOW_MILK)
    {
        printf("Low stock: Milk\n");
        printf("Amount left: %d ml\n", milk_amnt);
    }

    if (choc_amnt < LOW_CHOC)
    {
        printf("Low stock: Chocolate syrup\n");
        printf("Amount left: %d ml\n", choc_amnt);
    }
}

// Admin menu function that displays admin options 
void admin_menu() {
    while (true) {
        int admin_choice;
        printf("\nAdmin Menu:\n");
        printf("1: Display ingredient quantities and total sales\n");
        printf("2: Replenish ingredients\n");
        printf("3: Change coffee prices\n");
        printf("4: Display and reset total sales\n"); // New menu option
        printf("0: Exit Admin Mode\n");
        scanf("%d", &admin_choice);

        switch (admin_choice) {
            case 1:
                printf("Current ingredient quantities:\n");
                printf("Coffee beans: %d g\n", beans_amnt);
                printf("Water: %d ml\n", water_amnt);
                printf("Milk: %d ml\n", milk_amnt);
                printf("Chocolate syrup: %d ml\n", choc_amnt);
                printf("Total sales: %.2f AED\n", total_amount);
                break;
            case 2:
                replenish_ingredients();
                break;
            case 3:
                change_coffee_price();
                break;
            case 4:
                display_and_reset_sales();
                break;
            case 0:
                printf("Exiting Admin Mode...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Function to display total sales and reset it if needed
void display_and_reset_sales() {
    printf("Total sales amount: %.2f AED\n", tot_sales);
    printf("Would you like to reset total sales to zero? (1 for yes, 0 for no): ");
    int reset_choice;
    scanf("%d", &reset_choice);
    
    if (reset_choice == 1) {
        tot_sales = 0.0;
        printf("Total sales has been reset. Please collect the money from the machine.\n");
    } else {
        printf("Total sales remains unchanged.\n");
    }
}

// Function to replenish ingredients with random quantities
void replenish_ingredients() {
    srand(time(0));
    beans_amnt = rand() % 101 + 100;  // Random refill between 100 and 200
    water_amnt = rand() % 301 + 300;  // Random refill between 300 and 600
    milk_amnt = rand() % 301 + 300;   // Random refill between 300 and 600
    choc_amnt = rand() % 101 + 50;    // Random refill between 50 and 150

    printf("Ingredients replenished:\n");
    printf("Coffee beans: %d g\n", beans_amnt);
    printf("Water: %d ml\n", water_amnt);
    printf("Milk: %d ml\n", milk_amnt);
    printf("Chocolate syrup: %d ml\n", choc_amnt);
}

// Function to change coffee prices
void change_coffee_price() {
    int coffee_choice;
    printf("Select the coffee type to change its price:\n");
    printf("1: Espresso\n2: Cappuccino\n3: Mocha\n");
    scanf("%d", &coffee_choice);

    switch (coffee_choice) {
        case 1:
            printf("Enter new price for Espresso: ");
            scanf("%f", &ESP_PRICE);
            break;
        case 2:
            printf("Enter new price for Cappuccino: ");
            scanf("%f", &CAP_PRICE);
            break;
        case 3:
            printf("Enter new price for Mocha: ");
            scanf("%f", &MOC_PRICE);
            break;
        default:
            printf("Invalid choice!\n");
    }

    printf("Prices updated successfully!\n");
}

// Function to display the coffee menu
void menu() {
    printf("Menu: \n");
    printf("1) Espresso: %.2f AED\n", ESP_PRICE);
    printf("2) Cappuccino: %.2f AED\n", CAP_PRICE);
    printf("3) Mocha: %.2f AED\n", MOC_PRICE);
}

// Function to take user's coffee order with confirmation and payment 
void user_order() {
    int order_choice;  // Variable to store user's coffee choice

    while (true) {
        coff_availability();  // Show available coffee options

        printf("Enter your selection (1 for Espresso, 2 for Cappuccino, 3 for Mocha, 0 to exit): ");
        scanf("%d", &order_choice);

        if (order_choice == 0) {
            printf("Exiting order menu...\n");
            return;
        }

        switch (order_choice) {
            case 1:  // Espresso
                if (beans_amnt >= ESP_BEANS && water_amnt >= ESP_WATER) {
                    price = ESP_PRICE;
                    printf("You selected Espresso. Price: %.2f AED. Confirm? (1 for yes, 0 for no): ", price);
                } else {
                    printf("Espresso is unavailable due to insufficient ingredients.\n");
                    continue;
                }
                break;

            case 2:  // Cappuccino
                if (beans_amnt >= CAP_BEANS && water_amnt >= CAP_WATER && milk_amnt >= CAP_MILK) {
                    price = CAP_PRICE;
                    printf("You selected Cappuccino. Price: %.2f AED. Confirm? (1 for yes, 0 for no): ", price);
                } else {
                    printf("Cappuccino is unavailable due to insufficient ingredients.\n");
                    continue;
                }
                break;

            case 3:  // Mocha
                if (beans_amnt >= MOC_BEANS && water_amnt >= MOC_WATER && milk_amnt >= MOC_MILK && choc_amnt >= MOC_CHOC) {
                    price = MOC_PRICE;
                    printf("You selected Mocha. Price: %.2f AED. Confirm? (1 for yes, 0 for no): ", price);
                } else {
                    printf("Mocha is unavailable due to insufficient ingredients.\n");
                    continue;
                }
                break;

            default:
                printf("Invalid choice! Please try again.\n");
                continue;
        }

        int confirm;
        scanf("%d", &confirm);

        if (confirm == 1) {
            // Process payment
            float payment = 0;
            while (payment < price) {
                float coin;
                printf("Insert coins (1 AED or 0.5 AED): ");
                scanf("%f", &coin);

                if (coin == 1.0 || coin == 0.5) {
                    payment += coin;
                } else {
                    printf("Invalid coin! Please collect it and insert a valid one.\n");
                }
            }

            printf("You paid: %.2f AED. Coffee cost: %.2f AED. Change: %.2f AED.\n", payment, price, payment - price);
            tot_sales += price;

            // Deduct ingredients based on the choice
            switch (order_choice) {
                case 1:  // Espresso
                    update_ingredients(ESP_BEANS, ESP_WATER, 0, 0);
                    break;
                case 2:  // Cappuccino
                    update_ingredients(CAP_BEANS, CAP_WATER, CAP_MILK, 0);
                    break;
                case 3:  // Mocha
                    update_ingredients(MOC_BEANS, MOC_WATER, MOC_MILK, MOC_CHOC);
                    break;
            }

            printf("Enjoy your coffee!\n");
            low_ingredients();  // Check if any ingredient is low after serving
        } else {
            printf("Order canceled.\n");
        }
    }
}

// Function to show available coffee options
void coff_availability() {
    if (beans_amnt >= ESP_BEANS && water_amnt >= ESP_WATER) {
        printf("1) Espresso: %.2f AED\n", ESP_PRICE);
    } else {
        printf("1) Espresso: Unavailable due to temporarily insufficient ingredients\n");
    }

    if (beans_amnt >= CAP_BEANS && water_amnt >= CAP_WATER && milk_amnt >= CAP_MILK) {
        printf("2) Cappuccino: %.2f AED\n", CAP_PRICE);
    } else {
        printf("2) Cappuccino: Unavailable due to temporarily insufficient ingredients\n");
    }

    if (beans_amnt >= MOC_BEANS && water_amnt >= MOC_WATER && milk_amnt >= MOC_MILK && choc_amnt >= MOC_CHOC) {
        printf("3) Mocha: %.2f AED\n", MOC_PRICE);
    } else {
        printf("3) Mocha: Unavailable due to temporarily insufficient ingredients\n");
    }

    if (beans_amnt < ESP_BEANS && beans_amnt < CAP_BEANS && beans_amnt < MOC_BEANS) {
        printf("No coffee can be served due to insufficient ingredients.\n");
    }
}

// main function 
int main() {
    while (true) {
        printf("Welcome to our coffee shop!\n");
        printf("1) Admin menu\n");
        printf("2) Customer menu\n");
        printf("3) Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                admin_op();
                break;
            case 2:
                menu();
                user_order();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}