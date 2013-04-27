#include <stdio.h>
#include <malloc.h>

typedef struct linked_list {
	int value;
	struct linked_list *next;
} LL_t;

LL_t *root = (LL_t *)NULL;

/**
 * add new element as head of list and keep updating
 */
int add (LL_t **head)
{
	LL_t *tmp = malloc (sizeof(LL_t));

	if (tmp == (LL_t *)NULL) {
		printf("memory allocation failure!\n");
		return 1;
	}

	tmp->next = NULL;
	printf("Enter number :");
	scanf("%d", &tmp->value);

	if (*head != (LL_t *)NULL)
		tmp->next = *head;

	*head = tmp;
	return 0;
}

/**
 * Display list from headd
 */
void disp (LL_t *head)
{
	for(; head; head = head->next)
		printf("%d\n", head->value);
}


void free_list (LL_t *head)
{
	LL_t *tmp;

	for(; head;) {
		tmp = head;
		head = head->next;
		free(tmp);
		
	}
}

int free_element(LL_t **head, int value)
{
	LL_t *tmp;

	if ((*head)->value == value) {
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		return 0;
	}

	for (tmp = *head; tmp; tmp = tmp->next) {
		if (tmp->next->value == value ) { 
			LL_t * del = tmp->next;
			tmp->next = tmp->next->next;
			free(del);
			return 0;
		}
	}

	return -1;
}

void rev (LL_t *head)
{
	if (head->next) {
		rev(head->next);
		head->next->next = head;
		head->next = (LL_t *) NULL;
	} else {
		root = head;
	}

}

int main()
{
	int choice;
	int value, br = 1;

	printf ("choice 1 for add, 2 for disp, 3 for free element, 4 for free list, 5 for reverse, 6 for exit\n");

	while (br) {
		printf("Enter choice :");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				if (add(&root))
					goto failure;
				break;
			case 2:
				disp(root);
				break;
			case 3:
				printf("Enter number :");
				scanf("%d", &value);
				free_element(&root, value);
				break;
			case 4:
				free_list(root);
				break;
			case 5:
				rev(root);
				break;
			default:
				br = 0;
				break;
		}
	}

failure:
	free_list(root);
	return 0;
}
