#include <bits/stdc++.h>
#include "global.h"
#include "init.cpp"
#include "movegen.cpp"
#include "move.cpp"
#include "evaluate.cpp"
#include "search.cpp"
#include "proto.cpp"

/* Tesing FEN for BOT
#define FEN "8/5D2/8/2d5/3K4/4d3/5D2/8/W"
#define FEN2 "8/8/8/2d1d3/8/2d1d3/3D4/8/W"
#define FEN3 "8/8/3D4/4d3/8/4d3/8/8 B"
#define FEN4 "5d1d/D7/1D1d1D1D/6D1/7D/8/8/d1d1d1d1/W"
#define FEN5 "1D3D2/2D3D1/8/8/7D/6d1/7d/2d3d1/B"
#define FEN6 "1d1d1d1d/d1d5/7d/D1d5/5d1d/D7/1D1D1D1D/D3D1D2/W"
#define FEN7 "1d1d1d1d/d1d5/7d/D1d5/1D3d1d/8/1D1D1D1D/D3D1D1/B"
#define FEN8 "1d1d1d1d/d1d5/7d/D7/5d1d/8/3D1D1D/D1k1D1D1/W"
#define FENK "8/1D1D1D1D/8/1D1d1D1d/8/8/1d1d1d1d/8/B"
*/


int main(int argc ,char * argv[]) 
{	
	
	BOARD b;
	b.init();
	vector<MOVE> moveList;
	MOVE move;
	int k,nk;
	while(1)
	{
		k=0,nk=0;
		b.printBoard();
		moveList.clear();
		b.genallmoves(moveList);
		if(moveList.size() == 0)
		{
			printf("Game over \n");
			printf("%s wins\n",sidecolor[b.side^1]);
			break;	
		}

		move=b.search(3);
		printf("Moving : ");
		b.printMove(move.move);
		b.makeMove(move);
		getchar();
		
	}
	
	return 0;
}
