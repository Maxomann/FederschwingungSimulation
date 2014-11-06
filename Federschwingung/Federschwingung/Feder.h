#pragma once
#include "stdafx.h"

class Feder : public sf::Drawable
{
	sf::CircleShape federOben;
	sf::RectangleShape federUnten;

	sf::Clock clock;
	int vorzeichenwechsel = 0;
	bool vorzeichen = false;//true= positiv, false= negativ
	std::vector<float> schwingungsdauer;
	std::vector<std::vector<float>> frameInfo;

	float zoom = 1;

	const float masse;/* kg */
	const float kraftNachUnten/* kg*m/s^2 , muss negativer wert oder 0 sein*/;
	const float federkonstante/* N/m */;

	float auslenkung = 0;/* m */
	float geschwindigkeit = 0;/* m/s */
	float beschleunigung = 0;/* m/s^2 */
	float wirkendeKraft = 0;/* kg*m/s^2 */


public:
	Feder( float beschleunigung/*m/s^2*/, float masse/*kg*/, float federkonstante/*N/m*/ );

	void setZoom( const float zoom );//nicht 0
	float getZoom()const;

	float getDurchschnittlicheSchwingungsdauer()const;

	void frame( double deltaT );

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

};
