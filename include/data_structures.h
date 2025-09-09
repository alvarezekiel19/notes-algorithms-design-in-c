#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "common.h"

// Linked List Node
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Binary Tree Node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Queue structure
typedef struct Queue {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Stack structure
typedef struct Stack {
    int* data;
    int top;
    int capacity;
} Stack;

// Hash table entry
typedef struct HashEntry {
    char* key;
    int value;
    struct HashEntry* next;
} HashEntry;

// Hash table
typedef struct HashTable {
    HashEntry** buckets;
    int size;
    int capacity;
} HashTable;

// Function declarations for common operations
ListNode* create_list_node(int data);
void free_list(ListNode* head);
void print_list(ListNode* head);

TreeNode* create_tree_node(int data);
void free_tree(TreeNode* root);
void print_tree_inorder(TreeNode* root);

Queue* create_queue(int capacity);
void free_queue(Queue* queue);
bool enqueue(Queue* queue, int data);
bool dequeue(Queue* queue, int* data);

Stack* create_stack(int capacity);
void free_stack(Stack* stack);
bool push(Stack* stack, int data);
bool pop(Stack* stack, int* data);

HashTable* create_hash_table(int capacity);
void free_hash_table(HashTable* table);
bool hash_insert(HashTable* table, const char* key, int value);
bool hash_get(HashTable* table, const char* key, int* value);

#endif /* DATA_STRUCTURES_H */
