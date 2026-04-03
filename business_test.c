#include "business_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



int main(void) {
    customer_table *table = make_table(10);

    // Add Test Case
    printf("Add Test Case:");
    add(table, "lorenzokiri.uk@gmail.com", "Lorenzo Uk", 19, "burger");
    add(table, "skibbit@toilet.com", "Skibbiti", 39, "pizza");
    list(table);

    // Lookup Test Case
    printf("\nLookup Test Case:\n");
    if (lookUp(table->buckets[djb_hash("lorenzokiri.uk@gmail.com") % table->num_buckets], "lorenzokiri.uk@gmail.com", "Lorenzo Uk", 19, "burger"))
        printf("Success\n");
    else {
        printf("Failure\n");
    }

    if (lookUp(table->buckets[djb_hash("skibbit@toilet.com") % table->num_buckets], "skibbit@toilet.com", "Skibbiti", 39, "pizza"))
        printf("Success\n");
    else {
	printf("Failure\n");
    }

    // List Test Case
    printf("\nList Test Case:");
    list(table);

    // Delete Test Case
    printf("\nDelete Test Case:\n");
    if (deleteCustomer(table, "lorenzokiri.uk@gmail.com"))
        printf("Success\n");
    else {
	printf("Not Found\n");
    }

    if (lookUp(table->buckets[djb_hash("lorenzokiri.uk@gmail.com") % table->num_buckets], "lorenzokiri.uk@gmail.com", "Lorenzo Uk", 19, "burger"))
	printf("Found(Failure)\n");
    else {
	printf("Not Found(Success)\n");
    }

    list(table);

    // Save Test Case
    printf("\nSave Test Case:\n");
    
    if (save(table, "customers.tsv")) {
        printf("Success\n");
    }

    else {
	printf("Failure\n");
    }

    // Add Duplicate Emails
    add(table, "ammy@ucsc.edu", "Sammy The Slug", 27, "bananas");
    
    printf("\nVersion 1:\n");
    list(table);

    add(table, "ammy@ucsc.edu", "Sammy", 30, "pizza");
    
    printf("\nVersion 2:\n");
    list(table);

    end(table);

    return 0;
}

