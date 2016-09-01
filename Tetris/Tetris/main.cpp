#include <SDL.h>
#include "Tetris.h"
#include <vector>
#include "Core\FSM\IState.h"
#include "Src\States\GameplayState.h"

int main( int argc, char* args[])
{

	std::vector<IState*>* states = new std::vector<IState*>();
	states->push_back( new GameplayState() );


	Tetris* game = new Tetris( states );
	return 0;
}