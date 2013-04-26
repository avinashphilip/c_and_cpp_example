#include <stdio.h>
#include <malloc.h>
typedef struct doubly_linked_list {
	int value;
	struct doubly_linked_list *next, *prev;
}DLL_t;

DLL_t *root = (DLL_t *) NULL;

void add (DLL_t **head)
{
	DLL_t *tmp;
	tmp = (DLL_t *) malloc(sizeof(DLL_t));
	if (tmp == (DLL_t *) NULL) {
		printf("Error!. Memory allocation failure");
		return;
	}
	tmp->next = tmp->prev = (DLL_t *) NULL;
	printf ("Enter linked list element value :");
	scanf("%d", &tmp->value);
	if (*head != (DLL_t *) NULL) {
		tmp->next = *head;
		(*head)->prev = tmp;
	}
	*head = tmp;
}

void disp (DLL_t *head)
{
	for(;head != (DLL_t *) NULL; head = head->next)
		printf("%d\n", head->value);
}

void rev_list(DLL_t *head)
{
	DLL_t *tmp;
	if (head->next != (DLL_t *) NULL) {
		rev_list(head->next);
		tmp = head->prev;
		head->prev = head->next;
		head->next = tmp;
	} else {
		root = head;
		tmp = head->prev;
		head->prev = head->next;
		head->next = tmp;
	}
}

int main()
{
	add(&root);
	add(&root);
	add(&root);
	disp(root);
	rev_list(root);
	disp(root);
	return 0;
}
