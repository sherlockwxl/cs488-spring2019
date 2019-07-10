// Winter 2019

#include "A5.hpp"

#include <iostream>
using namespace std;

int main( int argc, char **argv ) 
{
	if (argc > 1) {
		std::string luaSceneFile(argv[1]);
		std::string title("** Assignment 5 - [");
		title += luaSceneFile;
		title += "]";

		CS488Window::launch(argc, argv, new A5(luaSceneFile), 2048, 1024, title);

	} else {
		cout << "Must supply Lua file as First argument to program.\n";
        cout << "For example:\n";
        cout << "./A5 Assets/simpleScene.lua\n";
	}

	return 0;
}
