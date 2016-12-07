void BOARD::parse(int argc,char ** argv)
{
	
	MOVE move;
	int i=1;
	while(i<argc)
		{
		//printf("i = %d , %s\n",i,argv[i]);
		if(i<argc && !strncmp(argv[i],"fen",3))
		{
		parseFEN(argv[i+1]);
		i+=2;		
		}
		else if(i<argc && !strncmp(argv[i],"move",4))
		{
			move.move=atoi(argv[i+1]);
			move.kingmove=atoi(argv[i+2]);
			move.who=atoi(argv[i+3]);
			makeMove(move);
			i+=4;
		}
		else if(i<argc && !strncmp(argv[i],"makebest",8))
		{
			i+=1;
			move=search(8);
			makeMove(move);
			printBoard();
		}
		else if(i<argc && !strncmp(argv[i],"print",5))
		{i+=1;printBoard();}
		else if(i<argc && !strncmp(argv[i],"isvalid",7))
		{
			move=atoi(argv[i+1]);
			if(Valid(move.move,move.kingmove,move.who))
			{
			printf("1\n");
			makeMove(move);
			printf("%llu %llu %llu %llu\n",bitboard[WHITE],bitboard[BLACK],bitboard[WHITE_KING],bitboard[BLACK_KING]);
			}
			else
			printf("0\n");
			i+=2;
		}
		else if(i<argc && !strncmp(argv[i],"best",4))
		{

			move=search(6);
			if(move.move >0)
			{
			makeMove(move);
			printf("%llu %llu %llu %llu\n",bitboard[WHITE],bitboard[BLACK],bitboard[WHITE_KING],bitboard[BLACK_KING]);
			}
			else
			printf("-1 -1\n");
			i+=1;
			;
		}
		else if(i<argc && !strncmp(argv[i],"undo",4))
		{
			
			unmakeMove();
			printf("%llu %llu %llu %llu\n",bitboard[WHITE],bitboard[BLACK],bitboard[WHITE_KING],bitboard[BLACK_KING]);
			i+=1;
		}
		else if(i<argc && !strncmp(argv[i],"genfen",6))
		{i+=1;genFEN();}
	}

}
void BOARD::genFEN()
{
	string s="";
	char c;
	for(int i=7;i>=0;i--)
	{
		c='0';
		for(int j=0;j<8;j++)
		{
			if(board[i*8+j] == EMPTY)
			c++;
			else if(board[i*8+j] == WHITE)
			{
				if(c>'0')
				{s=s+c,c='0';}
				s=s+'D';
			}
			else if(board[i*8+j] == BLACK)
			{
			if(c>'0')
			{s=s+c,c='0';}
			s=s+'d';
			}
			else if(board[i*8+j] == WHITE_KING)
			{
			if(c>'0')
			{s=s+c,c='0';}
			s=s+'K';
			}
			else if(board[i*8+j] == BLACK_KING)
			{
			if(c>'0')
			{s=s+c,c='0';}
			s=s+'d';
			}
		
		}
		if(c>'0')
		s=s+c;
		s=s+'/';
	}
	if(side==WHITE)
	s=s+'W';
	else
	s=s+'B';
	cout<<s<<endl;
}


