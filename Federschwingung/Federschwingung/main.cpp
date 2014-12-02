#pragma once
#include "stdafx.h"
#include "Federpendel.h"

using namespace std;
using namespace sf;
using namespace tgui;

int main()
{
	RenderWindow window( VideoMode(800,600), "Federsimulation");
	window.setVerticalSyncEnabled( true );

	Gui gui( window );

	float deltaT = 0.001f;

	
	map<int, Federpendel> simulationen;
	map<int, vector<float>> simulationsdaten;
	//fallbeschleunigung, federkonstante, masse, schwingungsdauer, maximaleAuslenkung

	Federpendel feder( sf::Vector2f(40,80), 9.81f, 3.f, 1.f );
	feder.setZoom( 1 );
	feder.hebAn(10);
	simulationen.emplace(std::pair<int, Federpendel>(0,feder));

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

		for(auto& el : simulationen )
			el.second.frame( deltaT );

		for( const auto& el : simulationen )
			simulationsdaten[el.first] = el.second.getData();
		for( const auto& el : simulationsdaten )
		{
			for( const auto& data : el.second )
				cout << data << ":";
			cout << "XXX" << endl;
		}

		window.clear( Color::Green );

		//draw here
		for(const auto& el : simulationen )
			window.draw( el.second );

		window.display();
	}

	//system( "pause" );
}
