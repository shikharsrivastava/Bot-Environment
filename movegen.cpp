#define createMove(from, to, killed,king) ((from ) | (to <<6) | (killed<<12) | (king <<16))
#define bound(beg) ((beg < 64) && (beg >= 0))
#define isValid(beg, end) ((bound(beg)) && (bound(end)) && (abs((beg / 8) - (end / 8)) == 1))

int BOARD::killMove(int from, int move, int who, int depth ,vector<MOVE> &moveList) {
	
	int flag = 0;
	for (int i = 0; i < 2; i++) {
		int mid = from + inc[side][i];
		int to = from + 2*inc[side][i];
		if (isValid(from, mid) && isValid(mid, to) && (board[mid] == (side^1) || board[mid] == ((side^1) +2)) && board[to] == EMPTY) {
			if (board[mid] == (side^1))
				killMove(to, move | (i << (17+depth)), who, depth+1,moveList);
			else
				killMove(to, move | (i << (17+depth)), who | (1 << (17 + depth)), depth+1,moveList);
			flag = 1;
		}
	}
	if (flag == 0 && depth > 0) {
		move |= (depth << 12);
		move |= (from << 6);
		moveList.push_back(MOVE(move, 0, who));		
	}
	return flag;
}

void BOARD::moveGen(vector<MOVE> &moveList) {
	
	bb temp=bitboard[side];
	while (temp > 0) {
		int from = (int)log2(temp & -temp);
		temp-=(temp & -temp);	
			
			for (int m = 0; m < 2; m++) {
				int to = from + inc[side][m];
				if (isValid(from, to)) {
				
					if (board[to] == EMPTY) {
						moveList.push_back(MOVE(createMove(from, to, 0, 0), 0, 0));
					}
				}
			
			}
	}
}

int BOARD::kingKillMove(int from,int move,int kingmove, int who, int depth,vector<MOVE>& moveList)
{
	
	int pt=side+2;
	int flag=0;
	for(int i=0;i<4;i++)
	{
		int mid = from + inc[pt][i];
		int to = from + 2*inc[pt][i];

		if (isValid(from, mid) && isValid(mid, to) && (board[mid] == (side^1) || board[mid] == ((side^1) +2)) && board[to] == EMPTY) {
			if (board[mid] == (side ^ 1))
				kingKillMove(to, move | ((i&1) << (17+depth)), kingmove | (((i>>1)&1) << (17+depth)),who, depth+1,moveList);
			else
				kingKillMove(to, move | ((i&1) << (17+depth)), kingmove | (((i>>1)&1) << (17+depth)), who | (1<<(17+depth)), depth+1,moveList);
			flag = 1;
		}
	}	

	if (flag == 0 && depth > 0) {
		move |= (depth << 12);
		move |= (from << 6);
		moveList.push_back(MOVE(move, kingmove, who));		
	}
	return flag;
	
}


void BOARD::kingGen(vector<MOVE> &moveList)
{

	int pt=side+2;
	bb temp=bitboard[pt];

	while (temp > 0) {
		int from = (int)log2(temp & -temp);
		temp-=(temp & -temp);	
			
			for (int m = 0; m < 4; m++) {
				int to = from + inc[pt][m];
				if (isValid(from, to)) {
				
					if (board[to] == EMPTY) {
						moveList.push_back(MOVE(createMove(from, to, 0, 1), 0, 0));
					}
				}
			
			}
	}
	
}
void BOARD::genallmoves(vector<MOVE>& moveList)
{
	
	//king killing move
	
	//printf("h1\n");
	bb temp;
	bool killmovefound=false;	
	int pt=side+2;
	temp=bitboard[pt];
	//printf("temp = %llu\n",temp);
	while(temp>0)
	{
		int from = (int)log2(temp & -temp);
		temp-=(temp & -temp);
		if(kingKillMove(from,createMove(from,0,0,1),0,0,0,moveList))
		{ 
			killmovefound=true;
		}	
	}
		//printf("h2\n");

	 temp = bitboard[side];
	while(temp>0)
	{
		int from = (int)log2(temp & -temp);
		temp-=(temp & -temp);
		if(killMove(from ,createMove(from,0,0,0), 0, 0,moveList))
		{ 
			killmovefound=true;
		}	
	}
	
		//printf("h3\n");
	if(!killmovefound)
	{
		kingGen(moveList);
		moveGen(moveList);
	
	}
		//printf("h4\n");


}
