#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "business_lib.h"

int main(void) {
    customer_table *customers = make_table(10);

    FILE *infile = fopen("customers.tsv", "r");
    char line[256];
    while (fgets(line, sizeof(line), infile)) {
    	line[strcspn(line, "\n")] = '\0';

        char *email = strtok(line, "\t");
        char *name = strtok(NULL, "\t");
        char *shoeSizeStr = strtok(NULL, "\t");
        char *favFood = strtok(NULL, "\t");

        if (email && name && shoeSizeStr && favFood) {
            int shoeSize = atoi(shoeSizeStr);
            add(customers, email, name, shoeSize, favFood);
        }
    }

fclose(infile);
	
    while(true) {
	char command[20];
        printf("\nCustomer Database Commands:\n");
        printf("add - Add a new customer\n");
        printf("lookup - Lookup a customer by email\n");
        printf("delete - Delete a customer by email\n");
        printf("list - List all customers\n");
        printf("save - Save customers to file\n");
        printf("quit - Quit the program\n");
        printf("\nEnter a Command: ");
	
	if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

	command[strcspn(command, "\n")] = '\0'; 
	
	if (strcmp(command, "add") == 0) {
            char email[50], name[50], favFood[50];
	    int shoeSize;

            printf("Email Address: ");
            fgets(email, sizeof(email), stdin);
	    email[strcspn(email, "\n")] = '\0';

            printf("Name: ");
            fgets(name, sizeof(name), stdin);
	    name[strcspn(name, "\n")] = '\0';

            printf("Shoe Size: ");
            scanf("%d", &shoeSize);
            getchar();

            printf("Favorite Food: ");
            fgets(favFood, sizeof(favFood), stdin);
            favFood[strcspn(favFood, "\n")] = '\0';

            add(customers, email, name, shoeSize, favFood);
	    printf("\nCustomer Added!\n");

        } 
	
	else if (strcmp(command, "lookup") == 0) {
	    char email[50];
            
            printf("Email Address: ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0';
	    
	    bool found = false;
	    for (size_t i = 0; i < customers->num_buckets; i++) {
		ll_customer *current = customers->buckets[i];
		while (current != NULL) {
		    if (strcmp(current->email, email) == 0) {
                        printf("\nEmail: %s\n", current->email);
                        printf("Name: %s\n", current->name);
                        printf("Shoe Size: %d\n", current->shoeSize);
                        printf("Favorite Food: %s\n", current->favFood);
		        
			found = true;
			break;
		    }
		    current = current->next;
		}
		if (found == true) {
		    break;
		}
	    }
	    
	    if (found == false) {
		printf("Customer Not Found!\n");
	    }
	}
	
	else if (strcmp(command, "delete") == 0) {
            char email[50];

            printf("Email address: ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0';

            if (deleteCustomer(customers, email)) {
                printf("\nUser Deleted!\n");
            } 
	    
	    else {
                printf("Customer Not Found!\n");
            }
	} 
	
	else if (strcmp(command, "list") == 0) {
            list(customers);
        }
        
        else if (strcmp(command, "save") == 0) {
            save(customers, "customers.tsv");
	}

	else if (strcmp(command, "quit") == 0) {
	    break;
        }

	else {
            printf("Invalid Command!\n");
        }
    }

    printf("Program Ended!\n");
    end(customers);
}


