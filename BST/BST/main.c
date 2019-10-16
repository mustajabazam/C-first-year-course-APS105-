//
//  main.c
//  BST
//
//  Created by Mustajab Azam  on 2019-04-23.
//  Copyright © 2019 mustajabazam. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define COUNT 10

/* A Binary Tree node */
struct TNode {
    int data;
    struct TNode* left;
    struct TNode* right;
};

struct TNode* newNode(int data);

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(int arr[], int start, int end) {
    /* Base Case */
    if (start > end)
        return NULL;
    
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct TNode *root = newNode(arr[mid]);
    
    /* Recursively construct the left subtree and make it
     left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);
    
    /* Recursively construct the right subtree and make it
     right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);
    
    return root;
}

/* Helper function that allocates a new node with the
 given data and NULL left and right pointers. */
struct TNode* newNode(int data) {
    struct TNode* node = (struct TNode*)
    malloc(sizeof(struct TNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

void print2D(struct TNode *root);
void print2DUtil(struct TNode *root, int space);
void searchValue(int value, struct TNode *root);
void addValue(int value, struct TNode *root);

int main(int argc, const char * argv[]) {
    int array[] = {3,5,6,7,9,10,21,24,27,30,31,35};
    int n = sizeof(array)/sizeof(array[0]);
    /* Convert List to BST */
    struct TNode *root = sortedArrayToBST(array, 0, n-1);
    print2D(root);
    
    //searchValue(35, root);
    addValue(100, root);
    
    printf("\n\n\n\n\n\n\n\n\n");
    print2D(root);
    
    return 0;
}


//void repeatSearchValue(int value, struct TNode *root) {
//    if (root->right == NULL && root->left == NULL && root->data != value) {
//        printf("NOT FOUND\n");
//    }
//    if (root->data == value) {
//        printf("FOUND");
//    } else if (root->data > value) {
//        repeatSearchValue(value, root->left);
//    } else if (root->data < value) {
//        repeatSearchValue(value, root->right);
//    }
//}

void repeatAddValue(int value, struct TNode *root) {
    struct TNode *newAddedNode;
    if (root->data > value) {
        if (root->left != NULL && root->left->data > value) {
            repeatAddValue(value, root->left);
        } else if (root->left != NULL && root->left->data < value) {
            newAddedNode = newNode(value);
            newAddedNode->left = root->left;
            root->left = newAddedNode;
        } else {
            newAddedNode = newNode(value);
            root->left = newAddedNode;
        }
    }
}




void searchValue(int value, struct TNode *root) {
    if (root->right == NULL && root->left == NULL && root->data != value) {
        printf("\n%d NOT FOUND\n", value);
    }
    
    if (root->data == value) {
        printf("\n%d FOUND\n", value);
    } else if (root->data > value) {
        searchValue(value, root->left);
    } else if (root->data < value) {
        searchValue(value, root->right);
    }
}

void addValue(int value, struct TNode *root) {
    struct TNode *addedNode;
    if (root->data > value) {
        if (root->left != NULL && root->left->data > value) {
            addValue(value, root->left);
        } else if (root->left != NULL && root->left->data < value) {
            addedNode = newNode(value);
            addedNode->left = root->left;
            root->left = addedNode;
        } else {
            addedNode = newNode(value);
            root->left = addedNode;
        }
    } else if (root->data < value) {
        if (root->right != NULL && root->right->data < value) {
            addValue(value, root->right);
        } else if (root->right != NULL && root->right->data > value) {
            addedNode = newNode(value);
            addedNode->right = root->right;
            root->right = addedNode;
        }  else {
            addedNode = newNode(value);
            root->right = addedNode;
        }
    }
}

void print2DUtil(struct TNode *root, int space) {
    // Base case
    if (root == NULL)
        return;
    
    // Increase distance between levels
    space += COUNT;
    
    // Process right child first
    print2DUtil(root->right, space);
    
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
    
    // Process left child
    print2DUtil(root->left, space);
}

void print2D(struct TNode *root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
