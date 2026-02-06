#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
char *data;
struct Node *prev;
struct Node *next;
} Node;


static char *dupstr(const char *s){
    if(!s) return NULL;

    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (p) memcpy(p, s, n);
    return p;

}

static Node *new_node(const char *s){
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;

    n->data = dupstr(s);
    n->prev = n->next = NULL;
    return n;
}

Node *insert_front(Node *head, const char *s){
    Node *n = new_node(s);
    if (!n) return head;

    n->next = head;
    if (head) head->prev = n;
    return n;
}

Node *delete_node(Node *head, Node *target){
    if (!head || !target) return head;

    if(target->prev) target->prev->next = target->next;
    if(target->next) target->next->prev = target->prev;
    if(target == head) head = target->next;

    free(target->data);
    free(target);
    return head;

}

Node *find(Node *head, const char *s){
    for (Node *cur = head; cur; cur = cur->next){
        if (strcmp(cur->data, s) == 0) return cur;
    }
    return NULL;
}


Node *delete_by_value(Node *head, const char *s){
    Node *t = find(head,s);
    return delete_node(head, t);

  }

void print_list(Node *head){
for( Node *cur = head; cur; cur = cur->next){
    printf("[%s]%s", cur->data, cur->next ? " <-> " : "");
    }

    printf("\n");
}

void free_list(Node *head){
    Node *cur = head;
    while(cur){
        Node *next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }

}

int main(void){
    Node *head = NULL;

    head = insert_front(head, "three");
    head = insert_front(head, "two");
    head = insert_front(head, "one");


    printf("After inserts: ");
    print_list(head);

    Node *f = find(head, "two");
    printf("Find 'two': %s\n", f ? "found" : "not found");

    head = delete_by_value(head, "two");
    printf("After delete two: ");
    print_list(head);


    head = delete_by_value(head, "one");
    printf("After delete one: ");
    print_list(head);


    head = delete_by_value(head, "three");
    printf("After delete three: ");
    print_list(head);


    free_list(head);

    return 0;
}