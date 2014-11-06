#pragma once
#include "stdafx.h"
#include "Feder.h"

using namespace std;
using namespace sf;
using namespace tgui;

int main()
{
	RenderWindow window( VideoMode(800,600), "Federsimulation");
	window.setVerticalSyncEnabled( true );

	Gui gui( window );

	Feder feder( 9.81f, 5, 2 );
	feder.setZoom( 4 );

	while( window.isOpen() )
	{
		Event myEvent;
		while( window.pollEvent( myEvent ) )
		{
			if( myEvent.type == Event::Closed )
				window.close();
		}

		if( Keyboard::isKeyPressed( Keyboard::Escape ) )
			window.close();

		feder.frame(0.001);

		window.clear( Color::Green );

		//draw here
		window.draw( feder );

		window.display();
	}

	system( "pause" );
}
