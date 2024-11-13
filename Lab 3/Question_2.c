#include <stdio.h>
#include <math.h>

int main() {
    // Define the initial balance
    int initial_balance = 1000;
    
    // Define the transactions array
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]);
    
    // Initialize the balance
    int balance = initial_balance;
    
    // Initialize the tobeprocessed array
    int tobeprocessed[num_transactions];
    int tobeprocessed_count = 0;
    
    // Process each transaction
    for (int i = 0; i < num_transactions; i++) {
        int transaction = transactions[i];
        if (transaction < 0 && -transaction > balance) {
            // If withdrawal exceeds current balance, skip and store in tobeprocessed
            printf("Invalid transaction: %d exceeds current balance of %d.\n", transaction, balance);
            tobeprocessed[tobeprocessed_count++] = transaction;
        } else if (balance == 0) {
            // If balance is 0, stop processing further transactions
            printf("Balance is 0. No further transactions will be processed.\n");
            tobeprocessed[tobeprocessed_count++] = transaction;
            break;
        } else {
            // Update the balance for valid transactions
            balance += transaction;
        }
    }
    
    // Print the final balance and the contents of the tobeprocessed array
    printf("Final balance: %d AED\n", balance);
    printf("Unprocessed transactions: ");
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");
    
    return 0;
}