#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Admin password constant 
#define PASSWORD_ADMIN "Admin321"


// coffee prices (AED)
#define ESP_PRICE 3.5 // Espresso price
#define CAP_PRICE 4.5 // Cappuccino price
#define MOC_PRICE 5.5 // Mocha price


// coffee ingredients
#define ESP_BEANS 8 
#define ESP_WATER 30

#define CAP_BEANS 8
#define CAP_WATER 30
#define CAP_MILK 70

#define MOC_BEANS 8
#define MOC_WATER 39
#define MOC_MILK 160
#define MOC_CHOC 35

// ALERT: low threshold quantity for ingredients
#define LOW_BEANS 60
#define LOW_WATER 200
#define LOW_MILK 200
#define LOW_CHOC 60

int beans_amnt = 100;
int water_amnt = 500;
int milk_amnt = 500;
int choc_amnt = 100;
float tot_sales = 0.0;
float sales;
float price; 
int refill_beans, refill_water, refill_milk, refill_choc;
// function prototype 
void ingredients_refill();

// function definition 
void ingredients_refill()
{
    printf("Enter the quantity of coffee beans to refill (in g): \n");
    scanf("%d", &refill_beans);
    beans_amnt += refill_beans;

    printf("Enter the quantity of water to refill (in ml): \n");
    scanf("%d", &refill_water);
    water_amnt += refill_water;

    printf("Enter the quantity of milk to refill (in ml): \n");
    scanf("%d", &refill_milk);
    milk_amnt += refill_milk;

    printf("Enter the quantity of chocolate syrup to refill (in ml): \n");
    scanf("%d", &refill_choc);
    choc_amnt += refill_choc;

    printf("Refill successful!\n");
    printf("Current stock: \n");
    printf("Coffee beans: %d g\n", beans_amnt);
    printf("Water: %d ml\n", water_amnt);
    printf("Milk: %d ml\n", milk_amnt);
    printf("Chocolate syrup: %d ml\n", choc_amnt);
}



void admin_op(); //prototype

// function definition
void admin_op()
{
    char password[20];
    printf("Enter the admin password: \n");
    scanf("%19s", password);
    
    if (strcmp(password, PASSWORD_ADMIN)==0)
    {
        printf("Welcome, Admin!\n");
    }
    
    else
    {
        printf("Incorrect password! Access denied.\n");
    }
}

// function call
// admin_op();

// function prototype
void menu();


// function definition
void menu()
{
    printf("Menu: \n");
    printf("1) Espresso: %.2f AED\n", ESP_PRICE);
    printf("2) Cappuccino: %.2f AED\n", CAP_PRICE);
    printf("3) Mocha: %.2f AED\n", MOC_PRICE);
}
// function call
// menu();

// function prototype
void user_order();

// function definition 
void user_order()
{
    char coff_typ[20];

    printf("Enter a coffee type (espresso, cappuccino, mocha): \n");
    scanf("%19s", coff_typ);
    
    strlwr(coff_typ);
    
    if (strcmp(coff_typ, "espresso")== 0){
        printf("One espresso on the way!\n");
    }
    
    else if (strcmp(coff_typ, "cappuccino")== 0){
        printf("One cappuccino on the way!\n");
    }

    else if (strcmp(coff_typ, "mocha")==0){
        printf("One mocha on the way!\n");
    }

    else{
        printf("Sorry, we don't provide %s\n ", coff_typ);
    }
}


int main(){
while (true) // infinite loop
{
    int choice;
    printf("Welcome to our coffee shop!\n");
    printf("1) Admin menu\n");
    printf("2) Customer menu\n");
    printf("3) Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);

    switch (choice)
    {
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

// function prototype
void low_ingredients();

// function definition
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
// function prototype
void tot_sales();
// function definition 
void tot_sales()
{
    


}


void coff_availability(); // function prototype
// function definition
void coff_availability()
{
    if (beans_amnt >= ESP_BEANS && water_amnt >= ESP_WATER)
    {
        printf("Espresso is available!\n");
    }

    else
    {
        printf("Espresso is not available due to lack of ingredients!\n");
    }

    if (beans_amnt >= CAP_BEANS && water_amnt >= CAP_WATER && milk_amnt >= CAP_MILK)
    {
        printf("Cappuccino is available!\n");
    }

    else
    {
        printf("Cappuccino is not available due to lack of ingredients!\n");
    }

    if (beans_amnt >= MOC_BEANS && water_amnt >= MOC_WATER && milk_amnt >= MOC_MILK && choc_amnt >= MOC_CHOC)
    {
        printf("Mocha is available!\n");
    }

    else
    {
        printf("Mocha is not available due to lack of ingredients!\n");
    }
}