/*Checkers*/ 
using namespace std;
enum {WHITE,BLACK,WHITE_KING,BLACK_KING,TOTAL_BITBOARD,EMPTY};
typedef unsigned long long int bb;
struct MOVE
{
	int move;
	int kingmove;
	int who;
	MOVE()
	{
		move=kingmove=who=0;
	}
	MOVE(int a, int b=0, int c = 0) {
		move = a, kingmove = b, who = c;
	}
};
 
int inc[][4] = {{7, 9, 0, 0}, {-7, -9, 0, 0}, {-7, -9, 7, 9}, {-7, -9, 7, 9}};
bb power[64];
char sidecolor[][7]={"WHITE\0", "BLACK\0"};

class BOARD
{

	public:
	int board[64];
	int ply;
	stack<MOVE> his;
	int side;
	bb bitboard[TOTAL_BITBOARD];
	int bestmove;

	//initialize
	void init();
	void checkState();
	void parseFEN(char *);
	
	//Move generator

	void moveGen(vector<MOVE> &moveList);	
	void kingGen(vector<MOVE> &moveList);
	
	void genallmoves(vector<MOVE> &);

	void makeMove(MOVE);
	void unmakeMove();
	int killMove(int from, int move, int, int,vector<MOVE> &moveList);
	int kingKillMove(int, int, int, int, int, vector<MOVE>&);
	
	// print functions
	void printBoard();
	void printMove(int move);
	void printMoveList(vector<MOVE> &moveList);
	void printBitboard(bb a);

	// evaluate
	int evaluate();

	//search
	int maxx(int depth);
	int minn(int depth);
	MOVE search(int depth);
	bool Valid(int,int,int);

	//protocol
	void parse(int ,char **);
	void genFEN();


};



