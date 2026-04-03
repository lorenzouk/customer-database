#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// Struct for user data
typedef struct ll_customer {
    char *email;
    char *name;
    int shoeSize;
    char *favFood;
    struct ll_customer *next;
} ll_customer;

// Struct for hash table nodes of customers
typedef struct customer_table {
    size_t num_buckets;
    ll_customer **buckets;
} customer_table;

// Make the hash table
customer_table *make_table(size_t num_buckets);

// Dan Bernstein hash
unsigned long djb_hash(char *str);

// Add customer to the list
ll_customer *addToList(ll_customer *list, char *email, char *name, int shoeSize, char *favFood);

// Add customer information to the table
void add(customer_table *table, char *email, char *name, int shoeSize, char *favFood);

// Look up the customer information on the table
bool lookUp(ll_customer *list, char *email, char *name, int shoeSize, char *favFood);

// Delete the customer
bool deleteCustomer(customer_table *table, char *email);

// List customers
void list(customer_table *table);

// Save customers
bool save(customer_table *table, char *filename);

// End program/free customer table
void end(customer_table *table);

#define UNUSED(x) (void)(x)

