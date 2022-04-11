#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP
#include "OthelloAI.hpp"
#include "OthelloCell.hpp"
#include "OthelloGameState.hpp"
#include "OthelloApplication.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
namespace othelloz
{
    class myOthelloAI:public OthelloAI
    {
    public:
        OthelloCell chooseSide(const OthelloGameState& state);
        vector<pair<int, int>> getValidMoves( const OthelloGameState& state );
    	virtual std::pair<int,int> chooseMove(const OthelloGameState& state) override;
		int search(const OthelloGameState& state, int depth, OthelloCell myColor);
		int eval(const OthelloGameState& state, OthelloCell myColor);
        bool myTurn(const OthelloGameState& state,OthelloCell myColor);
    };
}
#endif
