#include "Feder.h"
using namespace std;
using namespace sf;


Feder::Feder( float erdbeschleunigung/*m/s^2*/, float masse/*kg*/, float federkonstante/*N/m*/ )
	:kraftNachUnten( masse*erdbeschleunigung*-1 ),
	masse( masse ),
	federkonstante(federkonstante)
{
	federOben.setRadius( 10 );
	federOben.setFillColor( Color::Red );
	federOben.setOrigin( Vector2f( federOben.getRadius(), federOben.getRadius()*2 ) );

	federUnten.setSize( sf::Vector2f( 10, 20 ) );
	federUnten.setFillColor( Color::Magenta );
	federUnten.setOrigin( Vector2f( federUnten.getSize().x / 2.0, 0 ) );

	clock.restart();
}

void Feder::frame(double deltaT)
{
	float kraftNachOben = federkonstante*auslenkung*-1;
	wirkendeKraft = kraftNachOben + kraftNachUnten;

	//F/m=a
	beschleunigung = wirkendeKraft / masse;

	//v1 = v0 + a
	geschwindigkeit += beschleunigung;

	//p1 = p0 + v
	auslenkung += (geschwindigkeit*deltaT);


	if( geschwindigkeit > 0 && vorzeichen == false )
	{
		vorzeichen = true;
		vorzeichenwechsel ++;
	}
	if( geschwindigkeit < 0 && vorzeichen == true )
	{
		vorzeichen = false;
		vorzeichenwechsel ++;
	}
	if( vorzeichenwechsel >= 2 )
	{
		vorzeichenwechsel = 0;
		schwingungsdauer.push_back( clock.restart().asSeconds() );
	}

	frameInfo.push_back( { auslenkung, geschwindigkeit, beschleunigung, wirkendeKraft } );

	federOben.setPosition( sf::Vector2f( 40, 80 ) );
	federUnten.setPosition( sf::Vector2f( 40, 80-(auslenkung*zoom) ) );
}

void Feder::draw( RenderTarget& target, RenderStates states ) const
{
	target.draw( federOben );
	target.draw( federUnten );
}

void Feder::setZoom( const float zoom )
{
	this->zoom = zoom;
}

float Feder::getZoom() const
{
	return zoom;
}
