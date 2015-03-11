

#include "PulseLib.h"
#include "pulse.h"
#include "move.h"
using std::pair;
using std::vector;
#include <iostream>
using std::cout;

namespace pulse {


PulseLib::PulseLib()
{
	pulsePtr = new pulse::Pulse();
	position = NULL;
}

void PulseLib::startGame()
{
	if (position != NULL)
		delete position;

	position = new Position( Notation::toPosition(Notation::STANDARDPOSITION) );
}

void PulseLib::play(myMove& aimove)
{
	pulsePtr->go(*position);
	while (!pulsePtr->resultReceived)
	{
		//wait for it
	}
	position->makeMove(pulsePtr->BestMove);

	aimove.origFile = Square::getFile(Move::getOriginSquare(pulsePtr->BestMove));
	aimove.origRank = Square::getRank(Move::getOriginSquare(pulsePtr->BestMove));
	aimove.destFile = Square::getFile(Move::getTargetSquare(pulsePtr->BestMove));
	aimove.destRank = Square::getRank(Move::getTargetSquare(pulsePtr->BestMove));
	aimove.code		= pulsePtr->BestMove;
}

void PulseLib::makeMove(const myMove& move)
{
	int origSquare = Square::valueOf(move.origFile, move.origRank);
	int destSquare = Square::valueOf(move.destFile, move.destRank);
	int pulse_move = Move::valueOf(MoveType::NORMAL, origSquare, destSquare, position->board[origSquare], position->board[destSquare], PieceType::NOPIECETYPE);
	position->makeMove(pulse_move);
}

bool PulseLib::hasLost()
{
	MoveGenerator moveGenerators;
	MoveList<MoveEntry>& moves = moveGenerators.getLegalMoves(*position, 1, position->isCheck());
	return moves.size == 0;
}

// Return all the possible moves from this position
void PulseLib::getMoveList(int origFile, int origRank, std::vector<myMove>& legalMoves)
{
	MoveGenerator moveGenerators;

	MoveList<MoveEntry>& moves = moveGenerators.getLegalMoves(*position, 1, position->isCheck());
	// only keep the moves that start from our orig square :
	for (int i = 0; i < moves.size; i++)
	{
		int move = moves.entries[i]->move;
		int origSquare = Move::getOriginSquare(move);

		if (Square::getFile(origSquare) == origFile && Square::getRank(origSquare) == origRank )
		{
			int destSquare = Move::getTargetSquare(move);
			myMove m;
			m.origFile = origFile;
			m.origRank = origRank;
			m.destFile = Square::getFile(destSquare);
			m.destRank = Square::getRank(destSquare);
			legalMoves.push_back(m);
		}
	}
	
}


void PulseLib::drawPos()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++ )
		{
			int sq = Square::valueOf(j,i);
			char C = '.';
			if ( position->board[sq] != 12)
			{
				C = 'X';
			}
			cout << C;
		}
		cout << std::endl;
	}
	cout << "_____" << std::endl;
}

}