# Homework 7: Design Document

author: Lorenzo Uk
date: December 2024

## Introduction

In this homework assignment, I will create a simple database that tracks customer information. The database can read a file from the disk that adds and deletes customers. We can track an email address(string), a name (string), shoe size (integer), and favorite food (string). The way I will separate the code is by creating 3 directories, businessdb which is the main file where I would include I/O, the library file, and its header file to store the functions, test cases to check if the program works, and a Makefile to compile all the code.

## Buisnessdb(Main)

The buisnessdb creates the interface, I would use a while True loop that takes the input and runs the functions, add, lookup, delete, list, save, and quit along with the hashtable that stores the customers.tsv

## Library File/Header File

I will first read the customers.tsv using fopen and read and store those values into strings in a hashtable. In the header file, I will store the struct and create a function in the library file that stores the values of customers.tsv in strings.

## Add Function

I would compute the hash of the email, and first check if it exists in the hash table. If yes, replace the customer data, if not, add the new customer and its details. I will use a hash function on the email address to determine the index in the hash table. I will search the bucket at the computed index to check if the email already exists. If found, replace the existing customer data with the new data. Lastly, I free any memory associated with the old data to prevent memory leaks. If the email is not found, create a new customer node with the provided details. Then I would insert the new node into the appropriate hash table bucket.

## Lookup Function

I would check if the email address is in the hash table by using an if statement, if it's not, it will return a message saying that nobody has that email address. If the email address was found, I would return customer information. 

## Delete Function

The user is prompted is delete and they will enter an email address to delete, then I would traverse the linked list at that bucket index to locate the entry with the matching email. If found, unlink the node from the list and free the memory using free(). If not, display a message indicating that the customer was not found.

## List Function

I would traverse all buckets in the hash table and print each customer's information in a format similar to lookup.

## Save Function

I would use fopen customers.tsv and iterate through the hash table, and save each customer's details into its pointer

## Quit Function

I will just clean up all memory and exit the program.