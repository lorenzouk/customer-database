#include "business_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// By: Dan Bernstein
unsigned long djb_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while (*str != '\0') {
	
	c = *str;
        hash = ((hash << 5) + hash) + (unsigned char)c;
	str++;
    }
    return hash;
}

customer_table *make_table(size_t num_buckets) {
    customer_table *out = calloc(1, sizeof(customer_table));
    out->buckets = calloc(num_buckets, sizeof(customer_table *));
    out->num_buckets = num_buckets;
    return out;
}

ll_customer *addToList(ll_customer *list, char *email, char *name, int shoeSize, char *favFood) {
    ll_customer *newCustomer = calloc(1, sizeof(ll_customer));
    
    newCustomer->email = strdup(email);
    newCustomer->name = strdup(name);
    newCustomer->shoeSize = shoeSize;
    newCustomer->favFood = strdup(favFood);

    newCustomer->next = list;
    
    return newCustomer;  
}

void add(customer_table *table, char *email, char *name, int shoeSize, char *favFood) {
    unsigned long hashval = djb_hash(email);
    size_t bucket = hashval % table->num_buckets;
    ll_customer *current = table->buckets[bucket];

    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            free(current->name);
            free(current->favFood);

            current->name = strdup(name);
            current->shoeSize = shoeSize;
            current->favFood = strdup(favFood);
            return;
        }

        current = current->next;
    }

    table->buckets[bucket] = addToList(table->buckets[bucket], email, name, shoeSize, favFood);
}

bool lookUp(ll_customer *list, char *email, char *name, int shoeSize, char *favFood) {
    ll_customer *current = list;

    while (current != NULL) {
        if (strcmp(current->email, email) == 0 &&
            strcmp(current->name, name) == 0 &&
            current->shoeSize == shoeSize &&
            strcmp(current->favFood, favFood) == 0) {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool deleteCustomer(customer_table *table, char *email) {
    unsigned long hashval = djb_hash(email);
    size_t bucket = hashval % table->num_buckets;
    
    ll_customer *current = table->buckets[bucket];
    ll_customer *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            if (prev == NULL) {
                table->buckets[bucket] = current->next;
            } 
	    
	    else {
                prev->next = current->next;
            }

            free(current->email);
            free(current->name);
            free(current->favFood);
            free(current);

            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

void list(customer_table *table) {
    for (size_t i = 0; i < table->num_buckets; i++) {
        ll_customer *current = table->buckets[i];
        while (current != NULL) {
            printf("\nEmail: %s\n", current->email);
            printf("Name: %s\n", current->name);
            printf("Shoe Size: %d\n", current->shoeSize);
            printf("Favorite Food: %s\n", current->favFood);
            current = current->next;
        }
    }
}

bool save(customer_table *table, char *filename) {
    FILE *file = fopen(filename, "w");

    for (size_t i = 0; i < table->num_buckets; i++) {
        ll_customer *current = table->buckets[i];
        while (current != NULL) {
            fprintf(file, "%s\t%s\t%d\t%s\n", current->email, current->name, current->shoeSize, current->favFood);
            current = current->next;
        }
    }

    fclose(file);
    return true;
}

void end(customer_table *table) {
    for (size_t i = 0; i < table->num_buckets; i++) {
        ll_customer *current = table->buckets[i];
        while (current != NULL) {
            ll_customer *temp = current;
            current = current->next;

            free(temp->email);
            free(temp->name);
            free(temp->favFood);
            free(temp);
        }
    }

    free(table->buckets);
    free(table);
}
