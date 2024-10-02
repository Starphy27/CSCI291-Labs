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

void ingredients_refill();
void tot_sales();
void low_ingredients();
void coff_availability();

int main(){
    user_order();

    return 0; 
}