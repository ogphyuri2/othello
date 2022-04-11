// DuplicateTypeRegistrationException.hpp
//
// ICS 46 Winter 2022
// ICS 46 Library
//
// Exception that is thrown when attempting to register the same type with
// the same DynamicFactory twice.  Since registration is primarily done
// using a global macro call, this will predominantly be thrown at startup.

#ifndef DAEHEEAI_HPP
#define DAEHEEAI_HPP
#include "OthelloAI.hpp"
#include "OthelloCell.hpp"
#include "OthelloGameState.hpp"
#include "OthelloApplication.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
namespace daeheej
{
    class daeheeAI:public OthelloAI
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
//    Host: circinus-46.ics.uci.edu
//    Port: 4603
#endif

