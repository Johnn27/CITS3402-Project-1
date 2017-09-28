

typedef struct{
	int x;
	int y;
	struct stackNode *parent;
	struct stackNode *next;
} stackNode;

typedef struct{
	stackNode *start;
} Stack;

Stack * initStack();

void push(int x, int y, Stack * stack);

stackNode pop(Stack *stack);

bool checkIfPresent(int xCheck, int yCheck, Stack *stack);

bool isEmpty(Stack * s);