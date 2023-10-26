#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *head;
    int len;

};

struct node *createNode(int val)
{
    struct node *temp =(struct node *)malloc(sizeof(struct node));
    temp->next=NULL;
    temp->data=val;
    return temp;
}

struct BigInteger initialize(char *ch)
{
    struct BigInteger temp;
    temp.head=NULL;
    temp.len = strlen(ch);
    for(int i = 0;i < strlen(ch); i++){

            struct node *itr = createNode(ch[i] - '0');
            itr->next = temp.head;
            temp.head = itr;
    }
    return temp;
}

int length(struct node* head)
{
    int l=0;
    struct node* temp= head;
    while(temp!=NULL)
    {
        l++;
        temp= temp->next;
    }
    return l;
}


void append(struct node **head, int data)
{
    struct node *temp = createNode(data);
    if(*head == NULL) {
        *head = temp;
        return;
    }
    temp->next = *head;
    *head = temp;
}


void displayReverse(struct node* current) 
{
    if (current == NULL) {
        return;
    }
    displayReverse(current->next);
    printf("%d", current->data);
}

void display(struct BigInteger a) 
{
    displayReverse(a.head);
    printf("\n");
}


struct node *reverseLL(struct node *head)
{
    struct node* current = head;
    struct node *prev = NULL, *next = NULL;

    while (current != NULL) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct node *head = NULL;
    struct node *head1 = a.head;
    struct node *head2 = b.head;
    struct BigInteger c;
    int carry = 0, sum = 0, x, y;
    while(head1 || head2)
    {
        if(head1)
        {
            x = head1->data;
            head1 = head1->next;
        }
        else
            x = 0;

        if(head2)
        {
            y = head2->data;
            head2 = head2->next;
        }
        else
            y = 0;

        sum = x + y + carry;
        carry = sum/10;
        append(&head, sum%10);
    }
    if(carry > 0)
        append(&head, carry);
    c.head = reverseLL(head);
    return c;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct node *head = NULL;
    struct node *head1 = a.head;
    struct node *head2 = b.head;
    struct BigInteger c;

    int borrow = 0, difference = 0 ,x, y;
    while(head1 || head2)
    {
        if(head1!=NULL)
            x = head1->data;
        else
            x = 0;

        if(head2!=NULL)
            y = head2->data;
        else
            y = 0;

        difference = x - y - borrow;
        if(difference < 0) 
        {
            difference = difference+10;
            borrow = 1;
        }
        else 
        {
            borrow = 0;
        }
        append(&head, difference%10);
        if(head1!=NULL)
            head1 = head1->next;
        if(head2!=NULL)
            head2 = head2->next;
    }
    if(borrow)
    {
        append(&head, borrow);
    }

    while (head != NULL && head->data == 0) 
    {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }

    c.head = reverseLL(head);
    return c;
}

struct node *muladdition(struct node *a, struct node *b)
{
    struct node *result = NULL;
    struct node *itr;
    int carry = 0, sum = 0;

    while (a && b)
    {
        sum = a->data + b->data + carry;
        if (sum > 9)
        {
            sum -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        if (result == NULL)
        {
            result = createNode(sum);
            itr = result;
        }
        else
        {
            itr->next = createNode(sum);
            itr = itr->next;
        }
        a = a->next;
        b = b->next;
    }
    while (a)
    {
        if (result == NULL)
        {

            result = createNode((a)->data);
            itr = result;
        }
        else
        {
            itr->next = createNode((a)->data + carry);
            carry = 0;
            itr = itr->next;
        }
        a = a->next;
    }

    while (b)
    {
        if (result == NULL)
        {

            result = createNode((b)->data);
            itr = result;
        }
        else
        {
            itr->next = createNode((b)->data + carry);
            carry = 0;
            itr = itr->next;
        }
        b = b->next;
    }
    if (carry)
    {
        itr->next = createNode(carry);
        itr = itr->next;
    }
    return result;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{

    struct BigInteger r, result;
    r.head = NULL;
    result.head = NULL;
    struct node *itr = NULL, *temp1 = NULL, *temp2 = NULL;
    int sum = 0, carry = 0, c = 0, n = 0;
    while (b.head)
    {
        r.head = NULL;
        itr = NULL;
        temp1 = a.head;
        while (temp1)
        {
            sum = temp1->data * b.head->data + carry;
            carry = sum / 10;
            sum %= 10;
            if (!r.head)
            {
                r.head = createNode(sum);
                itr = r.head;
            }
            else
            {
                itr->next = createNode(sum);
                itr = itr->next;
            }
            temp1 = temp1->next;
        }
        if (carry)
        {
            itr->next = createNode(carry);
            itr = itr->next;
        }
        n = c;
        while (n--)
        {
            temp2 = createNode(0);
            temp2->next = r.head;
            r.head = temp2;
        }
        result.head = muladdition(r.head, result.head);
        carry = 0;
        c += 1;
        b.head = b.head->next;
    }
    return result;
}
