#pragma once
#include "stdafx.h"

class Federpendel : public sf::Drawable
{
	sf::Vector2f drawingOffset;
	sf::CircleShape federOben;
	sf::RectangleShape federUnten;

	float zoom = 1;

	//Messungen
	sf::Clock schwingungsdauer;
	bool vorzeichen;
	int vorzeichenwechsel = 0;
	long gesamteSchwingungsdauer=0;
	int anzahlPerioden = 0;
	float maximaleAuslenkung = -1;

	//Konstanten
	const float fallbeschleunigung;/*m/s^2*/
	const float masse;/* kg */
	const float federlängeInRuhe;/*m*/
	const float federkonstante;/* N/m */

	//Zustandsgrößen
	float geschwindigkeit = 0;/* m/s */
	float federlänge/*=federlängeInRuhe*/;


public:
	Federpendel( sf::Vector2f drawingOffset,
		   float fallbeschleunigung/*m/s^2*/,
		   float masse/*kg*/,
		   float federkonstante/*N/m*/ );

	void hebAn( const float weg/*m*/ );

	void setZoom( const float zoom );//nicht 0
	float getZoom()const;

	std::vector<float> getData()const;

	void frame( float deltaT );

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
};
