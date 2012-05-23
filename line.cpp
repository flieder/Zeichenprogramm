#include "line.h"

#include <cmath>

namespace bmp
{
	int round(float zahl);

	bool line::draw(Bitmap24& p_target, AbsoluteCoordinate p_from, AbsoluteCoordinate p_to, Color24 p_color)
	{
		if(!p_from.refersTo(p_target) || !p_to.refersTo(p_target))
		{
			return false;
		}

		// Abstand von Ursprung zu Ziel + Steigung + Y-Achsenabschnitt
		unsigned int xStart = p_from.getX();
		unsigned int yStart = p_from.getY();
		unsigned int xZiel = p_to.getX();
		unsigned int const xAbstand = (xZiel - xStart);
		unsigned int const yAbstand = (p_to.getY() - yStart);

		float steigung = std::abs(static_cast<float>(yAbstand)/xAbstand);

		float yAchse = yStart - steigung * xStart;

		int deltaX = 1;
		if(xAbstand < 0)
		{
			deltaX = -1;
		}

		// Linie malen: durchlaufe spalten (x) und bemale gerundetes y-Feld
		//				nach Geradengleichung
		for(unsigned int spalte=xStart; spalte!=xZiel; spalte+=deltaX)
		{
			p_target.setPixel(spalte,round(steigung*spalte+yAchse),p_color);
		}

		return true;
	}

	lineto::lineto(bmp::RelativeCoordinate p_to)
		: to( p_to )
	{}

	lineto::~lineto()
	{
		/* does not require to do anything special in this implementation */
	}

	bool lineto::applyTo(bmp::BatchBitmap24& p)
	{
		line lineObj;
		AbsoluteCoordinate absTo = to.convert(p);

		if( ! lineObj.draw(p, p.getCurrentPos(), absTo, p.getCurrentColor()) )
		{
			return false;
		}

		return p.setCurrentPos( absTo );
	}

	int round(float zahl)
	{
		int gerundet = 0;
		if(zahl < 0.0f)
		{
			gerundet = static_cast<int>(std::floor(zahl + 0.5));
		}
		else
		{
			gerundet = static_cast<int>(std::ceil(zahl - 0.5));
		}
		return gerundet;
	}
}
