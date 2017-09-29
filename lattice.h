typedef struct {
	bool populated;
	bool visited;
	int xcoord;
	int ycoord;
	bool northcon;
	bool southcon;
	bool eastcon;
	bool westcon;
} node;

#define SETSIZE 500
#define prob 0.6

char setgraphnode(node n);

void printGraph(node** n);

node** generateLattice();
