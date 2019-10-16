//
// APS105 Lab 9
//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
//  Created by Mustajab Azam  on 2019-04-01.
//  Copyright © 2019 mustajabazam. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist;
    char *songName;
    char *genre;
    struct node *next;
} Node;

typedef struct linkedList {
    Node *head;
} LinkedList;


// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//

bool isEmpty(LinkedList *list);
Node *findFirstNode(LinkedList *list, char *songName);
Node *createNode(char *artist, char *songName, char *genre);
bool insertAtFront(LinkedList *list, char *artist, char *songName, char *genre);
bool insertIntoOrderedList(LinkedList *orderedList, char *artist, char *songName, char *genre);
void printList(LinkedList *list);
void deleteFront(LinkedList *list);
int deleteAllNodes(LinkedList *list);
bool deleteFirstMatch(LinkedList *list, char *songName);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *songName);
void artistFound(char *artist);
void artistNotFound(char *artist);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

const int MAX_LENGTH = 1024;

int main(void) {
    // Declare the head of the linked list.
    LinkedList myMusicLibrary;
    myMusicLibrary.head = NULL;
    
    // Announce the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");
    
    char response;
    char input[MAX_LENGTH + 1];
    do {
        inputStringFromUser("\nCommand", input, MAX_LENGTH);
        
        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);
        
        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE
            char *songName = (char *) malloc(MAX_LENGTH *sizeof(char));
            char *artist = (char *) malloc(MAX_LENGTH *sizeof(char));
            char *genre = (char *) malloc(MAX_LENGTH *sizeof(char));
            
            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
            char *promptName = "Song name" ;
            char *promptArtist =  "Artist" ;
            char *promptGenre = "Genre" ;
            
            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            
            if (findFirstNode(&myMusicLibrary, songName)) {
                songNameDuplicate(songName);
            } else {
                insertIntoOrderedList(&myMusicLibrary, artist, songName, genre);
            }
            
        }
        else if (response == 'D') {
            // Delete a song from the list.
            
            char *prompt = "\nEnter the name of the song to be deleted" ;
            char *songName = (char *) malloc(MAX_LENGTH *sizeof(char));
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            
            if (deleteFirstMatch(&myMusicLibrary, songName)) {
                songNameDeleted(songName);
            } else {
                songNameNotFound(songName);
            }
            
        }
        else if (response == 'S') {
            // Search for a song by its name.
            
            char *prompt = "\nEnter the name of the song to search for" ;
            char *songName = (char *) malloc(MAX_LENGTH *sizeof(char));
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            
            Node *nodeToPrint = findFirstNode(&myMusicLibrary, songName);
            if (nodeToPrint) {
                songNameFound(songName);
                printf("\n%s\n", nodeToPrint->songName);
                printf("%s\n", nodeToPrint->artist);
                printf("%s\n", nodeToPrint->genre);
            } else {
                songNameNotFound(songName);
            }
            
        }
        else if (response == 'P') {
            // Print the music library.
            if (isEmpty(&myMusicLibrary)) {
                printMusicLibraryEmpty();
            } else {
                printMusicLibraryTitle();
                printList(&myMusicLibrary);
            }
        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf ("\nInvalid command.\n");
        }
    } while (response != 'Q');
    
    // Delete the entire linked list.
    deleteAllNodes(&myMusicLibrary);
    
    // Print the linked list to confirm deletion.
    printMusicLibraryEmpty();
    
    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
    int i = 0;
    char c;
    
    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate(char *songName) {
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) {
    printf("\nThe song name '%s' was found in the music library.\n",
           songName);
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char *songName) {
    printf("\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char *songName) {
    printf("\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

// Add your functions below this line.

bool isEmpty(LinkedList *list) {
    if (list->head == NULL) {
        // The head does not point to anything.
        return true;
    }
    
    return false;
}

/**
 * @brief Find the first node with the given value.
 *
 * @param list A pointer to the linked list to search. Assumed to be non-NULL.
 * @param songName The value to search for.
 *
 * @return The node that was found, or NULL if the node was not found.
 */
Node *findFirstNode(LinkedList *list, char *songName) {
    Node *current = list->head;
    
    while (current != NULL) {
        if (strcmp(current->songName, songName) == 0) {
            // Found the node.
            return current;
        }
        
        // Did not find the node.
        // Move to the next element in the list.
        current = current->next;
    }
    
    // Did not find the node in the entire list.
    return NULL;
}

/**
 * @brief Allocate a new node on the heap.
 *
 * @param artist The data value of the node.
 *
 * @param songName The data value of the node.
 *
 * @param genre The data value of the node.
 *
 * @return A pointer to the new node.
 */
Node *createNode(char *artist, char *songName, char *genre) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    
    if (newNode != NULL) {
        newNode->artist = artist;
        newNode->songName = songName;
        newNode->genre = genre;
        newNode->next = NULL;
    }
    
    return newNode;
}

/**
 * @brief Insert a new node at the front of the list.
 *
 * This function will allocate space for a new node and update the list.
 *
 * @param list A pointer to the linked list to modify. Assumed to be non-NULL.
 *
 * @return true if a new node was successfully added, false otherwise (e.g., out-of-memory).
 */
bool insertAtFront(LinkedList *list, char *artist, char *songName, char *genre) {
    // Create a new node.
    Node *temp = createNode(artist, songName, genre);
    if (temp == NULL) {
        // We couldn't allocate enough memory for a new node.
        return false;
    }
    
    // The node will be inserted before head, so next should point to head.
    temp->next = list->head;
    // Now update head to the new front of the list.
    list->head = temp;
    
    return true;
}

/**
 * @brief Insert a node into an ordered list, and keeps it in order.
 *
 * @param orderedList A pointer to the linked list to search. Assumed to be non-NULL.
 *
 * @return true if a new node was successfully added, false otherwise (e.g., out-of-memory).
 */
bool insertIntoOrderedList(LinkedList *orderedList, char *artist, char *songName, char *genre) {
    if (isEmpty(orderedList) == true) {
        // The list is empty, insertion at front/back is the same thing.
        return insertAtFront(orderedList, artist, songName, genre);
    }
    
    if (strcmp (songName, orderedList->head->songName) < 0) {
        // The value to insert comes before the current head, so insert before it.
        return insertAtFront(orderedList, artist, songName, genre);
    }
    
    Node *current = orderedList->head;
    while (current->next != NULL && strcmp (songName, current->next->songName) > 0) {
        // The value to insert is larger than the next element in the list.
        // Move to the next element in the list.
        current = current->next;
    }
    
    Node *newNode = createNode(artist, songName, genre);
    if (newNode == NULL) {
        // Could not allocate memory for a new node.
        return false;
    }
    
    // current may be the last element in the list.
    // current may also be the last element in an ordered list that is less than value.
    newNode->next = current->next; // Link the rest of the list with this new node.
    current->next = newNode; // Overwrite next with the new node.
    
    return true;
}

/**
 * @brief Print out the data value of each element of the list.
 *
 * @param list A pointer to the linked list to print. Assumed to be non-NULL.
 */
void printList(LinkedList *list) {
    Node *current = list->head;
    
    while (current != NULL) {
        // Print out the data at this element.
        printf("\n%s\n", current->songName);
        printf("%s\n", current->artist);
        printf("%s\n", current->genre);
        // Move to the next element in the list.
        current = current->next;
    }
}

/**
 * @brief Delete every node of the linked list.
 *
 * @param list A pointer to the linked list to erase. Assumed to be non-NULL.
 *
 * @return The number of nodes deleted.
 */
int deleteAllNodes(LinkedList *list) {
    int numDeleted = 0;
    
    while (isEmpty(list) == false) {
        deleteFront(list);
        numDeleted++;
    }
    
    // The list is now empty.
    list->head = NULL;
    
    return numDeleted;
}

/**
 * @brief Delete the first node of the linked list.
 *
 * @param list A pointer to the linked list to modify. Assumed to be non-NULL.
 */
void deleteFront(LinkedList *list) {
    if (isEmpty(list) == true) {
        // The list is empty, there is nothing to delete.
        return;
    }
    
    // Save the location of the node after head. Could be NULL, that's okay
    Node *newHead = list->head->next;
    // print that current head is deleted
    songNameDeleted(list->head->songName);
    // Free up the memory used by the current head.
    free(list->head->songName);
    free(list->head->artist);
    free(list->head->genre);
    
    free(list->head);
    // Update the current head to the saved location.
    list->head = newHead;
}

/**
 * @brief Delete the first node that matches a search query.
 *
 * @param list A pointer to the linked list to search. Assumed to be non-NULL.
 * @param songName The value to search for.
 *
 * @return true if a node was deleted, false if the node was not found.
 */
bool deleteFirstMatch(LinkedList *list, char *songName) {
    if (isEmpty(list) == true) {
        // There is nothing to do in an empty list.
        return false;
    }
    
    if (strcmp(list->head->songName, songName) == 0) {
        // The first node matches the value.
        
        // Save a pointer to the second element in the list. Could be NULL, that's ok.
        Node *temp = list->head->next;
        
        free(list->head); // Delete the first element of the list.
        list->head = temp; // Update the list to point to a new head.
        
        return true;
    }
    
    // Search for a node that matches the value, but maintain a pointer to the node just before it.
    Node *current = list->head;
    while (current->next != NULL && strcmp(current->next->songName, songName) != 0) {
        current = current->next;
    }
    
    // current now points to a node just before the node that matched, OR current points to the last node.
    if (current->next != NULL) {
        // current does not point to the last node.
        Node *temp = current->next; // temp is the node we must delete.
        current->next = temp->next; // Update n so that temp is no longer linked.
        free(temp);
        
        return true;
    }
    
    return false;
}

