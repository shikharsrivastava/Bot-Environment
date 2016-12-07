MOVE BOARD::search(int depth)
{
	MOVE bestMove(0,0,0);
	if(side==WHITE)
	{
		vector <MOVE> moveList;
		genallmoves(moveList);
	
		if(moveList.size()==0)
		bestMove.move = -1;
		int bestScore=-1000000;
		for(int i=0;i<moveList.size();i++)
		{
			int move=moveList[i].move;
			makeMove(moveList[i]);				
			int next=minn(depth-1);
			if(next > bestScore)
			{
				bestScore=next;
				bestMove=moveList[i];
			}
			unmakeMove();
		}
	}
	else
	{
		vector <MOVE> moveList;
		genallmoves(moveList);
				
		if(moveList.size() == 0)
		bestMove.move=-1;
		int bestScore=1000000;
		for(int i=0;i<moveList.size();i++)
		{
			int move=moveList[i].move;
			makeMove(moveList[i]);
			int next=maxx(depth-1);
			if(next < bestScore)
			{
				bestScore=next;
				bestMove=moveList[i];
			}
			unmakeMove();
		}
	}
	return bestMove;
}
// Max subroutine for MinMax functiom
int BOARD::maxx(int depth)
{
	if(depth==0)
		return evaluate();vector <MOVE> moveList;
	genallmoves(moveList);
	int bestScore=-100000;
	for(int i=0;i<moveList.size();i++)
	{
		int move=moveList[i].move;
		makeMove(moveList[i]);
		bestScore=max(bestScore,minn(depth-1));
		unmakeMove();
	}
	
	return bestScore;
}
// Min subroutine for MinMax function
int BOARD::minn(int depth)
{
	if(depth==0)
		return evaluate();
	vector <MOVE> moveList;
	genallmoves(moveList);
	int bestScore=+100000;
	for(int i=0;i<moveList.size();i++)
	{
		int move=moveList[i].move;
		makeMove(move);
		bestScore=min(bestScore,maxx(depth-1));
		unmakeMove();
	}
	return bestScore;
}
	
bool BOARD::Valid(int move,int kingmove,int who)
{
	MOVE tmp=MOVE (move,kingmove,who);
	vector<MOVE> moveList;
	genallmoves(moveList);
	for(int i=0;i<moveList.size();i++)
	{
		if(moveList[i].move == tmp.move && moveList[i].kingmove == tmp.kingmove && moveList[i].who == tmp.who)
			return true;
	}
	return false;
}	

	
	
