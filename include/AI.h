#pragma once

#include <vector>
#include "Grid.h"
#include "Globals.h"
using std::vector;

enum class Difficulty {
	Player = 0,//No AI
	Easy = 1,  //Play randomly
	Medium = 2,//Play where you take the most spaces
	Hard = 3   //Mainmax (another):skull:
};

class AI {
public:
	AI();
	~AI();

	int2 play(Difficulty diff, const Grid& grid);

private:
	int2 playEasy(const Grid& grid);
	int2 playMedium(const Grid& grid);
	int2 playHard(const Grid& grid);//Minmax but i am too lazy to do it now
	
};