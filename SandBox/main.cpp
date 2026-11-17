#include <MyLib/Application.h>
#include <iostream>

class MyGame : public MyLib::Application {
protected:
	void OnStart( ) override { std::cout << "Start/n"; };
	void OnUpdate( ) override { };
	void OnEnd( ) override { std::cout << "End/n"; };
};

int main( ) {
	MyGame game;
	if ( !game.Initialize( 1280, 720, L"My Game" ) )return -1;
	game.Run( );
	game.Shutdown( );
	return 0;
};