#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *prev, *next;
} Node;

Node *head = NULL;
Node *clipboard = NULL;

Node* createNode(char ch) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void insertChar(char ch) {
    Node* newNode = createNode(ch);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void displayText() {
    Node* temp = head;
    printf("Text: ");
    while (temp) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void cutText(int pos, int len) {
    if (!head) return;
    Node* temp = head;
    int count = 1;
    while (temp && count < pos) {
        temp = temp->next;
        count++;
    }
    if (!temp) return;
    clipboard = NULL;
    for (int i = 0; i < len && temp; i++) {
        Node* next = temp->next;
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
        temp->prev = temp->next = NULL;
        if (!clipboard)
            clipboard = temp;
        else {
            Node* ctemp = clipboard;
            while (ctemp->next)
                ctemp = ctemp->next;
            ctemp->next = temp;
            temp->prev = ctemp;
        }
        temp = next;
    }
}

void pasteText(int pos) {
    if (!clipboard) return;
    if (!head) {
        head = clipboard;
        clipboard = NULL;
        return;
    }
    Node* temp = head;
    int count = 1;
    while (temp->next && count < pos) {
        temp = temp->next;
        count++;
    }
    Node* ctemp = clipboard;
    while (ctemp) {
        Node* newNode = createNode(ctemp->data);
        newNode->next = temp->next;
        if (temp->next)
            temp->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        temp = newNode;
        ctemp = ctemp->next;
    }
    clipboard = NULL;
}

int main() {
    int choice, pos, len;
    char ch;
    do {
        printf("\n--- Text Editor Menu ---\n");
        printf("1. Insert Character\n");
        printf("2. Display Text\n");
        printf("3. Cut Text\n");
        printf("4. Paste Text\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter character to insert: ");
                scanf(" %c", &ch);
                insertChar(ch);
                break;
            case 2:
                displayText();
                break;
            case 3:
                printf("Enter position and length to cut: ");
                scanf("%d %d", &pos, &len);
                cutText(pos, len);
                break;
            case 4:
                printf("Enter position to paste: ");
                scanf("%d", &pos);
                pasteText(pos);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}

 
