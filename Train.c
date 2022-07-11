#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

struct TRAIN
{
	 bool Light;
	 struct TRAIN* next;
	 struct TRAIN* prev;
}*Train;

void AddElement(struct TRAIN* train, bool light)
{
	struct TRAIN* p, * temp;
	temp = (struct TRAIN*)malloc(sizeof(struct TRAIN));
	p = train->next;
	train->next = temp;
	temp->Light = light;
	temp->next = p;
	temp->prev = train;
	if (p != NULL)
		p->prev = temp;
}

void Initialize()
{
	Train = (struct TRAIN*)malloc(sizeof(struct TRAIN));
	Train->Light = false;
	Train->next = NULL;
	Train->prev = NULL;
	struct TRAIN* first = Train;
	for (int i = 0; i < 39; i++)
	{
		AddElement(Train, i % 2 == 0);
		Train = Train->next;
	}
	struct TRAIN* last = Train;
	Train->next = first;
	Train = Train->next;
	Train->prev = last;
}

void LengthOfTrain_Quadratic()
{
	size_t all_count = 0;
	while (true)
	{
		size_t count = 0;
		Train = Train->next;
		count++;
		all_count++;
		while (!Train->Light)
		{
			Train = Train->next;
			count++;
			all_count++;
		}
		Train->Light = false;
		for (int i = count; i > 0; i--)
		{
			Train = Train->prev;
			all_count++;
		}
		if (!Train->Light)
		{
			printf("The length of the train is %d\nTotal steps: %d\n", count, all_count);
			break;
		}
	}
}

int MyPower(size_t x, size_t y)
{
	if (y == 0)
		return 1;
	size_t base = x;
	for (int i = 1; i < y; i++)
		base *= x;
	return base;
}

void LengthOfTrain_Linear()
{
	size_t all_count = 0;
	for (int i = 0;; i++)
	{
		size_t step = MyPower(2, i);
		for (int q = 0; q < step; q++)
		{
			Train = Train->next;
			all_count++;
			Train->Light = false;
		}
		for (int q = 0; q < step; q++)
		{
			Train = Train->prev;
			all_count++;
		}
		if (!Train->Light)
		{
			Train->Light = true;
			size_t count = 0;
			Train = Train->next;
			count++;
			all_count++;
			while (!Train->Light)
			{
				Train = Train->next;
				count++;
				all_count++;
			}
			printf("The length of the train is %d\nTotal steps: %d\n", count, all_count);
			break;
		}
	}
}

int main()
{
	Initialize();
	Train->Light = true;
	printf("Choose the difficulty:\n1 - O(n^2)\n2 - O(n)\n");
	unsigned short choice;
	scanf_s("%hu", &choice);
	switch (choice)
	{
	case 1:
		LengthOfTrain_Quadratic();
		break;
	case 2:
		LengthOfTrain_Linear();
		break;
	default:
		printf("Wrong number!");
		break;
	}
	return 0;
}