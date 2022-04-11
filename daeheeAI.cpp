// main.cpp
//
// ICS 46 Winter 2022
// Project #3: Black and White
//
// This is the program's main() function, which launches the GUI.  You will
// not want to make any changes to this file.

#include <ics46/factory/DynamicFactory.hpp>
#include "daeheeAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,daeheej::daeheeAI,"Not Smart my AI (Required)");
//Choose the currentSide.
OthelloCell daeheej::daeheeAI::chooseSide(const OthelloGameState& state)
{
    OthelloCell myColor;
    if(state.isWhiteTurn())
		myColor = OthelloCell::white;
	else
		myColor = OthelloCell::black;
    return myColor;
}
//Create All Possible Valid move and return the vector
vector<pair<int,int>> daeheej::daeheeAI::getValidMoves(const OthelloGameState& state)
{
	vector<pair<int,int>> validMoves;
	for(int x = 0; x < state.board().width(); x++)
	{
		for(int y = 0; y < state.board().height(); y++)
		{
			if(state.isValidMove(x,y))
            {
				validMoves.push_back(pair(x,y));
            }
		}
	}
	return validMoves;
}

//Set up Best_score to -3000 to prevent any exception
//Use helper function to organize, use unique_ptr to store the possiblemove and simulate.
//if it get better score it will replace and become a best score
pair<int, int> daeheej::daeheeAI::chooseMove(const OthelloGameState& state)
{
    int best_score = -3000;
    OthelloCell myColor = chooseSide(state);
    vector<pair<int,int>> possibleMove = getValidMoves(state);
	pair<int,int> guess_move;
    for(auto move:possibleMove)
    {
        unique_ptr<OthelloGameState> copy_ptr = state.clone();
        copy_ptr -> makeMove(move.first,move.second);
        int score = search(*copy_ptr, 3, myColor);
    	if(score > best_score)
		{
			best_score = score;
			guess_move.first = move.first;
			guess_move.second = move.second;
		}
    }
	return guess_move;
}
bool daeheej::daeheeAI::myTurn(const OthelloGameState& state,OthelloCell myColor)
{
    if(myColor == OthelloCell::black && state.isBlackTurn())
    {
        return true;
    }
    else if (myColor == OthelloCell::white && state.isWhiteTurn())
    {
        return true;
    }
    return false;
}
//If depth equal to 0 or game over or no more possible move, then go to evaluate score
//If not check the player's turn and using max, min to compare the good move with recursive function.
//replace the max and min score
//depth start with 3, which not make a slow program.
int daeheej::daeheeAI::search(const OthelloGameState& state, int depth, OthelloCell myColor)
{
    vector<pair<int,int>> allPossibleMove = getValidMoves(state);
    if(depth == 0 || state.isGameOver() || allPossibleMove.size() == 0)
    {
        return eval(state, myColor);
    }
    else
    {
        if(myTurn(state, myColor))
        {
            int max = -3000;
            for(auto move:allPossibleMove)
            {
                unique_ptr<OthelloGameState> copyMaxMove = state.clone();
                copyMaxMove->makeMove(move.first, move.second);
                int tempScore = search(*copyMaxMove, depth-1, myColor);
                if(tempScore > max)
                {
                    max = tempScore;
                }
            }
            return max;
        }
        else
        {
            int min = 3000;
            for(auto move:allPossibleMove)
            {
                unique_ptr<OthelloGameState> copyMinMove = state.clone();
                copyMinMove->makeMove(move.first, move.second);
                int tempScore_opp = search(*copyMinMove, depth-1, myColor);
                if(tempScore_opp <= min)
                {
                    min = tempScore_opp;
                }
            }
            return min;
        }
    }
}
//evaluate the value and return a score(result)
int daeheej::daeheeAI::eval(const OthelloGameState& state, OthelloCell myColor)
{
    int result = 0;
    if (myColor==OthelloCell::black)
    {
        result = state.blackScore() - state.whiteScore();
    }
    else
    {
        result = state.whiteScore() - state.blackScore();
    }
    const OthelloBoard& board = state.board();
    //Prevent error if board is not equal to standard board(8 X 8)
    if(board.height() != 8 && board.width() != 8)
    {
        return result;
    }
    //Thanks for help to teach winning strategy https://www.ultraboardgames.com/othello/tips.php
    //If its bad move, take out result point, if its good move add result point to make AI priory pick that move
    else
    {
        if(board.cellAt(0,0)== myColor || board.cellAt(7,0)== myColor || board.cellAt(0,7)== myColor || board.cellAt(7,7) == myColor)
        {
            result += 150;
        }
        else if(board.cellAt(2,0) == myColor || board.cellAt(3,0) == myColor || board.cellAt(4,0) == myColor || board.cellAt(5,0) == myColor)
        {
            result += 100;
        }
        else if(board.cellAt(7,2) == myColor || board.cellAt(7,3) == myColor || board.cellAt(7,4) == myColor || board.cellAt(7,5) == myColor)
        {
            result += 100;
        }
        else if(board.cellAt(2,7) == myColor || board.cellAt(3,7) == myColor || board.cellAt(4,7) == myColor || board.cellAt(5,7) == myColor)
        {
            result += 100;
        }
        else if(board.cellAt(0,1) == myColor || board.cellAt(1,0) == myColor || board.cellAt(1,1) == myColor)
        {
            result -= 120;
        }
        else if(board.cellAt(0,6) == myColor || board.cellAt(1,6) == myColor || board.cellAt(1,7) == myColor)
        {
            result -= 90;
        }
        else if(board.cellAt(6,0) == myColor || board.cellAt(6,1) == myColor || board.cellAt(7,1) == myColor)
        {
            result -= 90;
        }
        else if(board.cellAt(6,6) == myColor || board.cellAt(6,7) == myColor || board.cellAt(7,6) == myColor)
        {
            result -= 90;
        }
        return result;
    }
}