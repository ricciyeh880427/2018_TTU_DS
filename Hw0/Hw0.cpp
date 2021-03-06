#include <stdio.h>
#include <stdlib.h>

#define MAX 5

struct Node
{
	int item;
	Node* next;
};

typedef Node* nodePtr;

Node *inputData(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;

	nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
	tmpPtr->item = num;
	tmpPtr->next = NULL;

	if (headPtr == NULL)
		return tmpPtr;
	else {
		while (currentPtr->next != NULL)
			currentPtr = currentPtr->next;

		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

void printArrayForward(int A[])
{
	for (int i = 0; i < MAX; i++)
		printf("%d ", A[i]);
}

void printArrayBackward(int A[], int i)
{
	if (i == MAX)
		return;
	printArrayBackward(A, i + 1);
	printf("%d ", A[i]);
}

void printListForward(nodePtr ptr)
{
	while (ptr != NULL)
	{
		printf("%d ", ptr->item);
		ptr = ptr->next;
	}
}

void printListBackward(nodePtr ptr)
{
	if (ptr == NULL)
		return;

	printListBackward(ptr->next);
	printf("%d ", ptr->item);
}

int main()
{
	int num;
	int A[MAX] = { 0 };
	nodePtr headPtr = NULL;

	printf("Input %d numbers: ", MAX);

	for (int i = 0; i < MAX; i++) {
		scanf("%d", &num);
		A[i] = num;
		headPtr = inputData(num, headPtr);
	}

	printf("\nArray Forward Iteratively:  ");
	printArrayForward(A);
	printf("\nArray Backward Recursively: ");
	printArrayBackward(A, 0);

	printf("\nList Forward Iteratively:  ");
	printListForward(headPtr);
	printf("\nList Backward Recursively: ");
	printListBackward(headPtr);

	printf("\n");
	system("PAUSE");
	return 0;
}