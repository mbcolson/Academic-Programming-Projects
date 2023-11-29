#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    unsigned long link;
};

void insert(struct node **head, struct node **tail, int n) {
    struct node *cur, *prv, *nxt, *tmp;    

    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->data = n;
    
    cur = *head;
    prv = NULL;

    while((cur != NULL) && (cur->data < tmp->data)) {
        nxt = (struct node *)(cur->link ^ (unsigned long)prv);
        prv = cur;
        cur = nxt;
    }

    tmp->link = (unsigned long)prv ^ (unsigned long)cur;
 
    if (prv != NULL)
        prv->link ^= (unsigned long)cur ^ (unsigned long)tmp;
    else
        *head = tmp;

    if (cur != NULL)
        cur->link ^= (unsigned long)prv ^ (unsigned long)tmp;
    else
        *tail = tmp; 
}    

void delete(struct node **head, struct node **tail, int n) {
    struct node *cur, *prv, *nxt;

    cur = *head;
    prv = NULL;

    while(cur != NULL) {
        if (cur->data == n) {
            nxt = (struct node *)(cur->link ^ (unsigned long)prv);

            if (prv != NULL)
	        prv->link ^= (unsigned long)cur ^ (unsigned long)nxt;
            else 
                *head = nxt;

            if (nxt != NULL)
	        nxt->link ^= (unsigned long)cur ^ (unsigned long)prv;
            else 
                *tail = prv;

            free(cur);
          
            cur = nxt;
        } else if (cur->data > n)
	    break;
        else {
            nxt = (struct node *)(cur->link ^ (unsigned long)prv);
            prv = cur;
            cur = nxt;
        }
    }
}

void list(struct node *head) {
    struct node *cur, *prv, *nxt;
    int count = 0;

    prv = NULL;
    cur = head;

    while(cur != NULL) {
        if (count % 10 == 0)
            printf("\n");
        
        printf("%5d ", cur->data);
        nxt = (struct node *)(cur->link ^ (unsigned long)prv);
        prv = cur;
        cur = nxt;     
        count++;
    } 

    printf("\n");    
}

int main() {
    int i, num;
    struct node *head, *tail;

    srand(time(NULL));

    for(i = 0; i < 100; i++)
        insert(&head, &tail, rand() % 200);

    printf("\nNumbers in ascending order\n");

    list(head);

    while(1) {
        printf("Enter number to delete (-1 to exit): ");
        scanf("%d", &num);

        if (num == -1)
            break;

        delete(&head, &tail, num);
    } 

    printf("\nNumbers in descending order\n");

    list(tail);

    printf("\n");

    return 0;
}
