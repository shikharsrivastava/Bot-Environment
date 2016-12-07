void BOARD::makeMove(MOVE a)
{
	int move=a.move;
	int km=a.kingmove;

	his.push(a);
	int from =FROM(move);
	int to=TO(move);
	int pt;
	if(KING(move))
	pt=side+2;
	else
	pt=side;

	board[from]=EMPTY;
	bitboard[pt] &= ~power[from];
	int fin;
	if (side == WHITE) {
		if(to >= 56 && to < 64 && pt != side + 2)
			fin = side + 2;
		else 
			fin = pt;
	}
	else if (side == BLACK) {
		if (to >= 0 && to < 8 && pt != side + 2)
			fin = side + 2;
		else
			fin = pt;
	}
	board[to]=fin;
	bitboard[fin] |= power[to];
	for(int i=0;i<KILLED(move);i++)
	{		
		int id=((km >> (17+i))&1)*2 + ((move >> (17+i))&1);
		int incr=inc[pt][id];
		int type=board[from+incr];
		board[from+incr]=EMPTY;
		bitboard[type] &= ~power[from+incr];
		from+=2*incr;		
	}

	/*printBitboard(bitboard[WHITE]);
	printf("\n");
	printBitboard(bitboard[BLACK]);*/

	ply++;
	side^=1;	
}

void BOARD::unmakeMove()
{
	MOVE a=his.top();
	his.pop();
	int move =a.move;
	int km=a.kingmove;
	int who = a.who;
	ply--;
	side^=1;	
	int pt;
	int from = TO(move);
	int to=FROM(move);
	//printf("from = %d to =%d\n",from,to);
	if (KING(move))
		pt = side + 2;
	else
		pt = side;
	int fin;
	if (side == WHITE) {
		if (from >= 56 && from < 64 && pt != side + 2)
			fin = side + 2;
		else
			fin = pt;
	}
	else {
		if (from >= 0 && from < 8 && pt != side + 2)
			fin = side + 2;
		else
			fin = pt;
	}
	board[to]=pt;
	bitboard[pt] |=power[to];
	
	board[from]=EMPTY;
	bitboard[fin] &=~power[from]; 
	
	

	for(int i=KILLED(move)-1;i>=0;i--)
	{
		int id = ((km >> (17+i))&1)*2 + ((move >> (17+i))&1);
		int incr=-inc[pt][id];
		if ((who >> (17+i))&1) {
			board[from+incr]=(side^1)+2;
			bitboard[(side^1)+2] |=power[from+incr];
		}
		else {
			board[from+incr] = side^1;
			bitboard[side^1] |=power[from+incr];
		}

		from+=2*incr;	
	}

	
}
