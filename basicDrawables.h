#ifndef H_BASICDRAWABLE
#define H_BASICDRAWABLE

#include "drawable.h"
#include "batchbmp.h"

namespace bmp
{
	// a class whose instances can draw a line to a Bitmap24
	// NOTE: there is a reason why this is a class (and not a simple function)
	//       but it'll only reveal in some future workshop (or you use black voodoo already now)
	class line
	{
	public:
		// returns false in case of error (one of the coordinates does not refer to the target)
		bool draw(bmp::Bitmap24& p_target,
				  AbsoluteCoordinate p_from, AbsoluteCoordinate p_to, Color24 p_color);
	};


	// a class whose instances can draw lines to BatchBitmap24
	// from the current position to another coordinate
	// the current position of the bitmap is changed to the end position of the line
	class lineto
		: public IBatchDrawable
	{
	public:
		lineto(bmp::RelativeCoordinate p_to);
		virtual ~lineto();

		virtual bool applyTo(bmp::BatchBitmap24& p);

	private:
		// NOTE: we use relative coordinates here to stay independent
		//       from the bitmap which the lineto is later applied to
		bmp::RelativeCoordinate to;
	};


	//Klasse "fillBitmap" abgeleitet von IBatchDrawable. Füllt die in "ApplyTo" übergeben
	//BatchBitmap24 mit der aktuellen Farbe
	class fillBitmap
		: public IBatchDrawable
	{
	public:
		fillBitmap();
		virtual ~fillBitmap();

		virtual bool applyTo(bmp::BatchBitmap24& p);
	};


	//Klasse circle: kann Kreis um Punkt mit gegebenem Radius (in Pixel) und Farbe in eine Bitmap24 malen
	class circle
	{
	public:
		bool draw(bmp::Bitmap24& p_target, AbsoluteCoordinate p_from, unsigned int radius, Color24 p_color);
	};

	//Klasse circleRound: kann Kreis um aktuelle Position mit Radius und aktueller Farbe in BatchBitmap24 malen
	//Achtung: alle angaben (Koordinaten, Radius) relativ!
	class circleRound
		: public IBatchDrawable
	{
	public:
		circleRound(float r);
		virtual ~circleRound();

		bool applyTo(bmp::BatchBitmap24& p);

	private:
		float radius;
	};

}

#endif /* H_BASICDRAWABLE */
