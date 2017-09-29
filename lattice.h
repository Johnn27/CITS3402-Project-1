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

//#define SETSIZE 5000
//#define prob 0.1

char setgraphnode(node n);

void printGraph(node** n);

node** generateLattice();
