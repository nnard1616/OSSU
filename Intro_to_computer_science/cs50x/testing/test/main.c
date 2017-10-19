#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node
{
    bool is_word;
    struct node* children[27];
} node;


int is_match(char* in[])
{
    string l = "fuck";
    return (strcmp(in, l));
}

int main()
{
    node* root = malloc(sizeof(node));


    //    root->children[4] = NULL;
    //    start[4].children[2]->word = true;

    char f[2];
    f[0] = 'a';
    f[1] = '\0';

    printf("%i\n", (f[1] == '\0'));
    return 0;
}
