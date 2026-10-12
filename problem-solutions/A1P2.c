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

char *tostr(int key)
{
    char *c = malloc(12);
    sprintf(c, "%d", key);
    return c;
}

char *tostring(struct node *root)
{
    char *string = malloc(1024);
    string[0] = '\0';
    struct node *temp = root;
    while (temp != NULL)
    {
        char *numstr = tostr(temp->data);
        strcat(string, numstr);
        strcat(string, " ");
        free(numstr);
        temp = temp->next;
    }
    int len = strlen(string);
    if (len > 0 && string[len - 1] == ' ')
    {
        string[len - 1] = '\0';
    }
    return string;
}

bool ispalindrome(struct node *root)
{
    char *string = tostring(root);
    int len = strlen(string);
    char a[10], b[10];
    int ind_a = 0, ind_b;
    for (int i = 0; i < len / 2; i++)
    {
        if (string[i] != ' ' && string[len - i - 1] != ' ')
        {
            if (string[i] != ' ')
            {
                a[ind_a] = string[i];
                ind_a++;
            }
            if (string[len - 1 - i] != ' ')
            {
                b[ind_b] = string[len - 1 - i];
                ind_b++;
            }
        }
        else if (string[i] == ' ')
        {
            a[ind_a] = '\0';
            b[ind_b] = '\0';
            int lena = strlen(a), lenb = strlen(b);
            if (lena != lenb)
            {
                return 0;
            }
            else if (lena == 1 && lenb == 1)
            {
                if (a[0] != b[0])
                {
                    return 0;
                }
            }
            for (int k = 0; k < lenb; k++)
            {
                if (a[k] != b[lenb - 1 - k])
                {
                    return 0;
                }
            }
            memset(a, 0, sizeof(a));
            memset(b, 0, sizeof(b));
            ind_a = 0;
            ind_b = 0;
        }
    }
    return 1;
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
        if (ispalindrome(root))
        {
            printf("True\n");
        }
        else
        {
            printf("False\n");
        }
        freelist(root);
    }
}