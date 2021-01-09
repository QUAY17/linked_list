/***************************************************************************
 * @file    collatz.c
 * @brief   Lab 8 Linked Lists
 * @author  Jennifer Quay Minnich
 * @date    Nov 05, 2020
 *
 * @details Linked List program that calculates the collatz conecture / hailstone sequence from user input.
 *
 * @bug none
 *
 * @todo none
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define LEN 32


struct node_t {
int x; // value of node
struct node_t *next;
};

int main() 
{

    struct node_t *tail = NULL;
    struct node_t *head = NULL;

    char buf[LEN];
    int  n;
    int  i = 0;

    printf("\nNumber for sequence: ");
    fgets(buf, LEN, stdin);
    n = atoi(buf);

    //uses redirection for input and output
    //freopen("hailstone.txt","w",stdout);

    while(1)
    {
        struct node_t *p = NULL;
        p = malloc(sizeof(struct node_t));

        p->x = n; // stores node data
        p->next = NULL;
        //pointer to tail
        if(head == NULL)
        {
            head = p;
            tail = p;
        }
        else
        {
            tail->next = p;
            tail = tail->next;
        }
        //count nodes
        ++i;
        // calculate sequence
        if (n == 1)
            break;
        if (n % 2 == 0)
            n = n / 2;
        else
            n = (n *3) + 1;
    }
        //print nodes
        printf("cycle length: %d\n", i);
        while (head !=NULL)
        {
            printf("%d, ", head->x);
            head = head->next;
        }
        printf("\n");

    return 0;
}
