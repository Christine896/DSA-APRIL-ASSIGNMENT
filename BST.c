//SCT 221-0224/2022 - CHRISTINE WAMBUI
//SCT 221-0378/2022 - NEEMA MUTANU

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int findIndex(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

struct TreeNode* buildTree(int in[], int post[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    struct TreeNode* node = newNode(post[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd)
        return node;

    int inIndex = findIndex(in, inStart, inEnd, node->val);

    node->right = buildTree(in, post, inIndex + 1, inEnd, postIndex);
    node->left = buildTree(in, post, inStart, inIndex - 1, postIndex);

    return node;
}

void BFS(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* temp = queue[front++];
        printf("%d ", temp->val);

        if (temp->left != NULL)
            queue[rear++] = temp->left;
        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }
}

struct TreeNode* bst_construct(int in[], int post[], int n) {
    int postIndex = n - 1;
    return buildTree(in, post, 0, n - 1, &postIndex);
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    struct TreeNode* root = bst_construct(inOrder, postOrder, n);

    printf("The traversal of the constructed Binary Search Tree: \n");
    BFS(root);
    printf("\n\n");

    return 0;
}

