#define FROM(move) ((move) & (0x3f))
#define TO(move)   ((move>>6) & (0x3f))
#define KILLED(move) ((move >> 12) & (0xf))
#define KING(move)  ((move >> 16) & (1))
void BOARD::init() 
{
	bitboard[WHITE] = 0;
	for (int i = 0; i <= 63; i++)
		board[i] = EMPTY;
	for (int i = 0; i <= 6; i+=2) {
		bitboard[WHITE] |= (1 << i);
		board[i] = WHITE;
	}
	for (int i = 9; i <= 15; i+=2) {
		bitboard[WHITE] |= (1 << i);
		board[i] = WHITE;
	}
	for (int i = 16; i <= 22; i+=2) {
		bitboard[WHITE] |= (1 << i);
		board[i] = WHITE;
	}
	
	bitboard[BLACK] = 0;
	for (int i = 57; i <= 63; i+=2) {
		bitboard[BLACK] |= ((bb)1 << i);
		
		board[i] = BLACK;
	}
	for (int i = 48; i <= 54; i+=2) {
		bitboard[BLACK] |= ((bb)1 << i);
		board[i] = BLACK;
	}
	for (int i = 41; i <= 47; i+=2) {
		bitboard[BLACK] |= ((bb)1 << i);
		board[i] = BLACK;
	}
	ply = 0;
	side = WHITE;
	power[0]=1;
	for(int i=1;i<64;i++)
	power[i]=power[i-1]<<1;
	bitboard[WHITE_KING]=0;
	bitboard[BLACK_KING]=0;
	
}


void BOARD::printBoard() {
	for (int k = 7; k >= 0; k--) {
		for (int j = 0; j < 8; j++) {
			int i = k * 8 + j;
			if (board[i] == WHITE) 
				printf("W ");
			else if (board[i] == BLACK)
				printf("B ");
			else if (board[i] == EMPTY)
				printf(". ");
			else if (board[i] == WHITE_KING)
				printf("K ");
			else if (board[i] == BLACK_KING)
				printf("k ");
		}
		printf("\n");
	}
	printf("Side = %d\n",side);
}

void BOARD::printMove(int move) {
	printf("from %d to %d killed %d\n", FROM(move), TO(move), KILLED(move));
}

void BOARD::printMoveList(vector<MOVE> &moveList) {
	for (int i = 0; i < moveList.size(); i++) {
		int move = moveList[i].move;
		printMove(move);
	}
}

void BOARD::printBitboard(bb a) {
	for (int k = 7; k >= 0; k--) {
		for (int j = 0; j < 8; j++) {
			int i = k * 8 + j;
			int bit = (a >> i) & 1;
			printf("%d ", bit);
		}
		printf("\n");
	}
	
}

void BOARD::checkState() {
	printf("ply = %d\n", ply);
	for (int i = 0; i < TOTAL_BITBOARD; i++) {
		printf("bitboard #%d:\n", i);		
		printBitboard(bitboard[i]);
	}
	printf("side = %d\n", side);
}

void BOARD::parseFEN(char *s)
{

	int pos=0;
	int row=7;
	for(int i=0;i<64;i++)
	board[i]=EMPTY;

	bitboard[WHITE]=bitboard[BLACK]=0;

	for(int i=0;i<strlen(s);i++)
	{

		switch(s[i])
	{
	
		case 'D':board[row*8+pos]=WHITE;
			bitboard[WHITE] |=((bb)1 << (row*8+pos));
			pos++;
			break;
		case 'd':board[row*8+pos]=BLACK;
			bitboard[BLACK] |=((bb)1 << (row*8+pos));
			pos++;
			break;
		case ' ':break;
		case 'W':side=WHITE;
			break;
		case 'B':side=BLACK;
			break;
		case 'K':board[row*8+pos] = WHITE_KING;
			 bitboard[WHITE_KING] |= ((bb)1 << (row*8+pos));
			 pos++;
			 break;
		case 'k':board[row*8+pos] = BLACK_KING;
			 bitboard[BLACK_KING] |= ((bb)1 << (row*8+pos));
			 pos++;
			 break;

		case '/':row--;
			pos=0;
			break;
		default: pos+=s[i]-'0';
			
	}
	}
}
	
		
