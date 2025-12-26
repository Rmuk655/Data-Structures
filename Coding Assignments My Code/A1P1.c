#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node *next;
};

struct node *create_node(struct node *root, int key)
{
    if (root == NULL)
    {
        root = (struct node *)malloc(sizeof(struct node));
        root->data = key;
        root->next = NULL;
        return root;
    }
    struct node *temp = root;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = (struct node *)malloc(sizeof(struct node));
    temp->next->data = key;
    temp->next->next = NULL;
    return root;
}

struct node *create_list(struct node *root, char string[])
{
    char *token = strtok(string, ", ");
    int num = atoi(token);
    root = create_node(root, num);
    while (token != NULL)
    {
        token = strtok(NULL, ", ");
        if (token != NULL)
        {
            num = atoi(token);
            root = create_node(root, num);
        }
    }
    return root;
}

struct node *grouplist(struct node *root)
{
    struct node *temp1 = root;
    struct node *temp2 = root->next;
    struct node *temp3 = root->next;
    int a = 1, b = 1;
    while ((temp1 != NULL && temp1->next != NULL && temp1->next->next != NULL) || (temp2 != NULL && temp2->next != NULL && temp2->next->next != NULL))
    {
        a = 1;
        b = 1;
        if (temp1 != NULL && temp1->next != NULL && temp1->next->next != NULL)
        {
            temp1->next = temp1->next->next;
            temp1 = temp1->next;
            a = 0;
        }

        if (temp2 != NULL && temp2->next != NULL && temp2->next->next != NULL)
        {
            temp2->next = temp2->next->next;
            temp2 = temp2->next;
            b = 0;
        }
    }
    temp1->next = temp3;
    temp2->next = NULL;
    // while (temp2 != NULL && temp2->next != NULL && temp2->next->next != NULL)
    // {
    //     temp2->next = temp2->next->next;
    //     temp2 = temp2->next;
    // }
    return root;
}

void printlist(struct node *root)
{
    if (root == NULL)
    {
        printf("Linked list is NULL! Cannot print it!");
        printf("\n");
        return;
    }
    struct node *temp = root;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freelist(struct node *root)
{
    if (root == NULL)
    {
        printf("Linked list is NULL! Cannot free it!");
        printf("\n");
        return;
    }
    while (root->next != NULL)
    {
        struct node *temp = root;
        root = root->next;
        free(temp);
    }
}

void test()
{
}

int main()
{
    // test();
    int num_of_tests;
    char string[1000];
    scanf("%d", &num_of_tests);
    getchar(); // consumes the leftover newline
    for (int i = 0; i < num_of_tests; i++)
    {
        struct node *root = NULL;
        fgets(string, sizeof(string), stdin);
        printlist(root);
        root = create_list(root, string);
        printlist(root);
        root = grouplist(root);
        printlist(root);
        freelist(root);
    }
}