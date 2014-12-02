#include "Federpendel.h"
using namespace std;
using namespace sf;

void Federpendel::draw( RenderTarget& target, RenderStates states ) const
{
	target.draw( federOben );
	target.draw( federUnten );
}

void Federpendel::setZoom( const float zoom )
{
	this->zoom = zoom;
}

float Federpendel::getZoom() const
{
	return zoom;
}

Federpendel::Federpendel( sf::Vector2f drawingOffset, float fallbeschleunigung/*m/s^2*/, float masse/*kg*/, float federkonstante/*N/m*/ )
	:fallbeschleunigung( fallbeschleunigung*-1 ),
	federlängeInRuhe( (fallbeschleunigung*masse)/federkonstante ),//wo sind die nach unten und die nach oben wirkende Kraft gleich?
	federlänge( (fallbeschleunigung*masse) / federkonstante ),
	federkonstante( federkonstante ),
	masse( masse ),
	drawingOffset( drawingOffset )
{
	federOben.setRadius( 2 );
	federOben.setFillColor( Color::Red );
	federOben.setOrigin( Vector2f( federOben.getRadius(), federOben.getRadius() * 2 ) );

	federUnten.setSize( sf::Vector2f( 10, 20 ) );
	federUnten.setFillColor( Color::Magenta );
	federUnten.setOrigin( Vector2f( federUnten.getSize().x / 2.0, 0 ) );

	schwingungsdauer.restart();
}

void Federpendel::frame( float deltaT )
{
	//simulation
	auto auslenkung = federlängeInRuhe - federlänge;

	auto federKraft = federkonstante*auslenkung*-1;
	auto gravitationsKraft = fallbeschleunigung*masse;

	auto wirkendeKraft = federKraft + gravitationsKraft;

	auto wirkendeBeschleunigung = wirkendeKraft / masse;
	auto deltaWirkendeBeschleunigung = wirkendeBeschleunigung*deltaT;

	geschwindigkeit += deltaWirkendeBeschleunigung;

	federlänge -= geschwindigkeit;


	//Messungen
	if( geschwindigkeit > 0 && vorzeichen == false )
	{
		vorzeichen = true;
		vorzeichenwechsel++;
		maximaleAuslenkung = auslenkung;
	}
	if( geschwindigkeit < 0 && vorzeichen == true )
	{
		vorzeichen = false;
		vorzeichenwechsel++;
	}
	if( vorzeichenwechsel >= 2 )
	{
		vorzeichenwechsel = 0;
		anzahlPerioden++;
		gesamteSchwingungsdauer += schwingungsdauer.restart().asSeconds();
	}

	//drawing
	federOben.setPosition( drawingOffset );
	federUnten.setPosition( sf::Vector2f( drawingOffset.x, drawingOffset.y + (federlänge*zoom) ) );
}

void Federpendel::hebAn( const float weg )
{
	if( weg > 0 )
		vorzeichen = false;
	else if( weg < 0 )
		vorzeichen = true;
	else
		cout << "ERROR: WEG KANN NICHT NULL SEIN" << endl;
	federlänge -= weg;
}

vector<float> Federpendel::getData() const
{
	return{ fallbeschleunigung, federkonstante, masse, (float)((double)gesamteSchwingungsdauer / (double)anzahlPerioden), maximaleAuslenkung };
}
