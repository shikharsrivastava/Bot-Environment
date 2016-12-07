int posarr[64] = {
		4 , 0 , 4 , 0 , 4 , 0 , 4 , 0 ,
		0 , 3 , 0 , 3 , 0 , 3 , 0 , 4 ,
	 	4 , 0 , 2 , 0 , 2 , 0 , 3 , 0 ,
		0 , 3 , 0 , 1 , 0 , 2 , 0 , 4 ,
		4 , 0 , 2 , 0 , 1 , 0 , 3 , 0 ,
		0 , 3 , 0 , 2 , 0 , 2 , 0 , 4 ,
		4 , 0 , 3 , 0 , 3 , 0 , 3 , 0 ,
		0 , 4 , 0 , 4 , 0 , 4 , 0 , 4 
		
	};

int BOARD::evaluate()
{
	int score=0;
	bb p=bitboard[WHITE];
	while(p>0)
	{
		int pos=(int)log2(p & -p);
		p-=p&-p;
		score+=posarr[pos];
		score++;
	}	

	p=bitboard[BLACK];
	while(p>0)
	{
		int pos=(int)log2(p & -p);
		p-=p&-p;
		score-=posarr[pos];
		score--;
	}	

	return score;
	
}
