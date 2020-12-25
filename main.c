/***************************************************************************
 * @file    lab8.c
 * @brief   Lab 8 Linked Lists
 * @author  Jennifer Quay Minnich
 * @date    Nov 05, 2020
 *
 * @details Linked Lists program that allows user to control data container. User can create and delete nodes, input or delete nodes at specified positions, display list of nodes, count nodes in the list, and search the list for a specified node. 
 *
 * @bug after deleting nodes, inputting new nodes can get buggy
 *
 * @todo none
 **************************************************************************/


/* function declarations needed for the linked list */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEN 32
#define ENTER_NUMBER 1
#define DELETE_NUMBER 2
#define PRINT_NUMBER 3
#define COUNT_ITEMS 4
#define FIND_NUMBER 5
#define QUIT 6


struct node_t {
double x; // value of node
struct node_t *next;
};

struct node_t *create_node(double n);
void print_node(struct node_t *node);
void print_list(struct node_t *head);
struct node_t *insert_head(struct node_t *head, struct node_t *node, double n);
struct node_t *insert_tail(struct node_t *head, struct node_t *node, double n);
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos, double n);
int count_nodes(struct node_t *head);
struct node_t *find_node(struct node_t *head, double n);
struct node_t *delete_node_head(struct node_t *head, double n);
struct node_t *delete_node_tail(struct node_t *head, double n);
struct node_t *delete_node_middle(struct node_t *head, int pos, double n);
void delete_list(struct node_t *head);
struct node_t *delete(struct node_t *head, double n);

int main() 
{

    struct node_t *head = NULL;
    struct node_t *node = NULL; //new node

    char buf[LEN];
    char place;
    int menu, count, pos;
    double n;

    while (1)
    {
        printf("\n1. Enter Number\n");
        printf("2. Delete Number\n");
        printf("3. Print List\n");
        printf("4. Count Numbers in List\n");
        printf("5. Find Number\n");
        printf("6. QUIT\n");
        printf("Enter selection: ");
        fgets(buf, LEN, stdin);
        menu = atoi(buf);

        switch(menu) 
        {
            case ENTER_NUMBER:
                printf("\nWhat number would you like to add to the list?\n");
                fgets(buf, LEN, stdin);
                n = atof(buf);
                //call function

                //submenu
                printf("\nWhere should item be entered? \nA. head\nB. tail\nC. middle\n");
                fgets(buf, LEN, stdin);
                sscanf(buf, "%c", &place);

                switch (place)
                {
                case 'A':
                case 'a':
                    //call function insert at head
                    head = insert_head(head,node,n);
                    break;
                case 'B':
                case 'b':
                    //call function insert at tail
                    head = insert_tail(head,node,n);
                    break;
                case 'C':
                case 'c':
                    printf("\nAfter what position?\n");
                    fgets(buf, LEN, stdin);
                    pos = atoi(buf);
                    //error checking
                    if (pos <= 1)
                    {
                        insert_head(head,node,n);
                    }
                    if (pos >= count)
                    {
                        insert_tail(head,node,n);
                    }
                    else
                    {
                       //call function insert at position
                       insert_middle(head,node,pos,n);
                    }
                }                           
            break;
            case DELETE_NUMBER:
                printf("\nEnter use case:  \nA. head\nB. tail\nC. middle \nD. by number \nE. delete all\n");
                fgets(buf, LEN, stdin);
                sscanf(buf, "%c", &place);

                switch (place)
                {
                case 'A':
                case 'a':
                    if (head == NULL)
                    {
                        printf("Error. Count elements in list first (use selection no. 4)\n");
                        break;
                    }
                    else
                    {
                        //call function delete head
                        delete_node_head(head,n);
                    }
                break;
                case 'B':
                case 'b':
                    if (head == NULL)
                    {
                        printf("Error. Count elements in list first (use selection no. 4)\n");
                        break;
                    }
                    else
                    {
                        //call function delete tail
                        delete_node_tail(head,n);
                    }
                break;
                case 'C':
                case 'c':
                    printf("\nAfter what position?\n");
                    fgets(buf, LEN, stdin);
                    pos = atoi(buf);
                    //error checking
                    if (pos > count)
                    {
                        printf("Error. Count elements in list first (use selection no. 4)\n");
                        break;
                    }
                    else
                    {
                       //call function delete at position
                       delete_node_middle(head,pos,n);
                    }
                break;
                case 'D':
                case 'd':
                    printf("\nWhat number?\n");
                    fgets(buf, LEN, stdin);
                    n = atof(buf);
                    //call function to delete node
                    head = delete(head,n);
                break;
                case'E':
                case'e':
                    if (head == NULL)
                    {
                        printf("Error. Count elements in list first (use selection no. 4)\n");
                        break;
                    }
                    else
                    {
                        //call function delete list
                        delete_list(head);
                        break;
                    }
                }       
            break;
            case PRINT_NUMBER:
                //call print list function
                print_list(head);
                if (!head)
                {
                    printf("node not found\n");
                }
            break;
            case COUNT_ITEMS:
                //call count nodes function
                count = count_nodes(head);
                printf("number of nodes: %d\n", count_nodes(head));
            break;
            case FIND_NUMBER:
                printf("\nWhat number would you like to find?\n");
                fgets(buf, LEN, stdin);
                n = atof(buf);
                //call find node function
                node = find_node(head, n);
                //printf("\nnode: %p", &head);
                if (node)
                {
                    printf("node was found\n");
                    print_node(node);
                    break;
                }
                else
                {
                    printf("node not found\n");
                    break;
                }
            break;
            case QUIT:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("Later!\n");
                exit(EXIT_SUCCESS);
            default:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("You entered something I don't understand.\n\n");
            break;
        }
    }

    return 0;
}

/**
 * creates new node and allocates memory for it
 * @param n the node data  
 * @returns node with data
 */
struct node_t *create_node(double n)
{
    struct node_t *node = NULL; //new node
    node = malloc(sizeof(struct node_t));

    if (node == NULL)
    {
        printf("Error: malloc failed in insert_head\n");
        exit(EXIT_FAILURE);
    }

    node->x = n;
    node->next = NULL;
    return node;
}
/**
* inserts new node to first (head) location
* @param *head pointer to first node
* @param *node pointer to new node
* @param n the node data
* @returns node holding data to head location
*/
struct node_t *insert_head(struct node_t *head, struct node_t *node, double n)
{
    node = create_node(n);
    node->next = head;
    return node;

}

/**
 * inserts new node to specified position in list
 * @param *head pointer to first node
 * @param *node pointer to new node
 * @param pos position to place node after
 * @param n the node data 
 * @returns node holding data to head location
 */
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos, double n)
{
    
    node = create_node(n);
    struct node_t *p = head;

    int i = 1;
    while (i < pos)
    {
        p=p->next;
        i++;
    }
    
    node->next = p->next;
    p->next = node;
}

/**
 * inserts new node to last (tail) location
 * @param *head pointer to first node
 * @param *node pointer to new node
 * @param n the node data 
 * @returns head holding data to tail location
 */
struct node_t *insert_tail(struct node_t *head, struct node_t *node, double n)
{
    
    struct node_t *p = head;
    node = create_node(n);
    if (head == NULL)
        return node;

    for(; p->next !=NULL; p = p->next)
        ;
    
    p->next = node;
    return head;
}

/**
 * prints node data 
 * @param *node pointer to new node
 */

void print_node(struct node_t *node)
{
    printf("\nnode: %lf, node address: %p", node->x, &node);
}

/**
 * prints list of stored nodes
 * @param *head pointer to first node
 */
void print_list(struct node_t *head)
{   
    while(head)
    {
        print_node(head);
        head = head->next;
    }
}

/**
 * counts stored nodes in list
 * @param *head pointer to first node
 * @returns count of nodes in list
 */
int count_nodes(struct node_t *head)
{
    int count = 0;
    for (; head !=NULL; head = head->next)
        count++;
    return count;

}

/**
 * searches list for specified node data
 * @param n the node data 
 * @returns head if node is found, NULL if not
 */
struct node_t *find_node(struct node_t *head, double n)
{
    struct node_t *p = head;
    while (p != NULL)
    {
        if (isgreaterequal(p->x,n) && islessequal(p->x,n))
            return p;
        p = p->next;
    }
    return NULL;
}

/**
 * deletes specfic node and frees memory
 * @param head pointer to the first node
 * @param n the node data 
 */
struct node_t *delete(struct node_t *head, double n)
{

    struct node_t *node = find_node(head, n);

    if(node == NULL)
    {
        return head;
    }

    if(node == head)
    {
        head = head->next;
        free(node);
        return head;
    }

    struct node_t *curr = head;
    struct node_t *prev = head;

    while(curr != NULL)
    {

    if(curr == node)
    {
        prev->next = curr->next;
        free(curr);
        return head;
    }
    prev = curr;
    curr = curr->next;
    }

    return head;
    
}

/**
 * deletes node at first (head) location and frees memory
 * @param n the node data 
 */
struct node_t *delete_node_head(struct node_t *head, double n)
{
    struct node_t *p = head;
    head = head->next;
    free(p);
}


/**
 * deletes node at last (tail) location and frees memory
 * @param n the node data 
 */
struct node_t *delete_node_tail(struct node_t *head, double n)
{
    struct node_t *p = head;
    struct node_t *prev = NULL;
 
    while (p->next != NULL)
    {
        prev=p;
        p=p->next;
    }
    if (p == head)
    {
        head = 0;
    }
    else
    {
        prev->next = 0;
    }
    free(p);
}

/**
 * deletes node in specified position in list
 * @param *head pointer to first node
 * @param pos position to place node after
 * @param n the node data 
 */
struct node_t *delete_node_middle(struct node_t *head, int pos, double n)
{
    struct node_t *p = head;
    struct node_t *next = NULL;

    int i = 1;
    while (i < pos-1)
    {
        p=p->next;
        i++;
    }
    next = p->next;
    p->next = next->next; 
    free(next);

}

void delete_list(struct node_t *head)
{
    struct node_t *p = head;
    while (head != NULL)
    {
        head = head->next;
        free(p);
        p = head;
    }
    printf("deleted.\n");
}
