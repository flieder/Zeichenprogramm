#include "basicDrawables.h"

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


	fillBitmap::fillBitmap()
	{
	}

	fillBitmap::~fillBitmap()
	{
	}

	bool fillBitmap::applyTo(bmp::BatchBitmap24& p)
	{
		for(unsigned int iRow = 0; iRow < p.getHeight(); ++iRow)
		{
			for(unsigned int iColumn = 0; iColumn < p.getWidth(); ++iColumn)
			{
				p.setPixel(iColumn, iRow, p.getCurrentColor());
			}
		}

		return true;
	}

	bool circle::draw(bmp::Bitmap24& p_target, AbsoluteCoordinate p_from, unsigned int radius, Color24 p_color)
	{
		unsigned int xMitte = p_from.getX();
		unsigned int yMitte = p_from.getY();

		if(((p_target.getHeight()-yMitte) < radius) || (yMitte < radius) || ((p_target.getWidth()-xMitte) < radius) || (xMitte < radius))
		{
			return false;
		}

		//x-Werte von xMitte-r bis xMitte + r durchlaufen
		for(unsigned int ispalte = -radius; ispalte < (radius+1); ++ispalte)
		{
			//einzufärbende y-Werte nach Kreisgleichung x^2+y^2 = r^2 bestimmen
			unsigned int xAbs = xMitte + ispalte;
			unsigned int ireihe = round(std::sqrt(radius*radius - ispalte*ispalte));
			unsigned int yAbs1 = yMitte + ireihe;
			unsigned int yAbs2 = yMitte - ireihe;

			p_target.setPixel(xAbs, yAbs1, p_color);
			if(yAbs1 != yAbs2)
			{
				p_target.setPixel(xAbs, yAbs2, p_color);
			}
		}

		return true;
	}

	circleRound::circleRound(float r)
		: radius(r)
	{}

	circleRound::~circleRound()
	{}

	bool circleRound::applyTo(bmp::BatchBitmap24& p)
	{
		circle kreisObj;
		unsigned int radiusAbs = static_cast<unsigned int>(round(radius));

		if(!kreisObj.draw(p, p.getCurrentPos(), radiusAbs, p.getCurrentColor()))
		{
			return false;
		}

		return true;
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
