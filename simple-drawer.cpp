#include "batchbmp.h"
//#include "line.h"
#include "basicDrawables.h"
//#include "test.h"

#include <iostream>


int main()
{
	//Bitmap anlegen und Farben definieren
	bmp::BatchBitmap24 sampleBitmap(200, 200);

	bmp::Color24 blue = {0, 0, 255};
	bmp::Color24 red = {255, 0, 0};
	bmp::Color24 green = {0, 255, 0};


	//Bitmap einfärben mit aktueller Farbe = blau
	sampleBitmap.setCurrentColor(blue);
	bmp::fillBitmap fuellung;
	fuellung.applyTo(sampleBitmap);


	//Linie zum Endpunkt "end" in aktueller Farbe = blau malen
	bmp::AbsoluteCoordinate end(sampleBitmap);
	sampleBitmap.setCurrentColor(red);
	if(!end.set(90, 50))
	{
		std::cout << "error!" << std::endl;
	}
	else
	{
		bmp::lineto myLine( end.convert() );
		if (!myLine.applyTo(sampleBitmap))
		{
			std::cout << "error!" << std::endl;
		}
	}


	//Kreis mit grün malen
	bmp::AbsoluteCoordinate mittelpunkt(sampleBitmap);
	if(!mittelpunkt.set(100,100))
	{
		std::cout << "error!" << std::endl;
	}
	else
	{
		sampleBitmap.setCurrentPos(mittelpunkt);
		sampleBitmap.setCurrentColor(green);
		bmp::circleRound kreis(50.00f);

		if(!(kreis.applyTo(sampleBitmap)))
		{
			std::cout << "error!" << std::endl;
		}
	}


	//Bitmap abspeichern
	sampleBitmap.save("foo.bmp");

	return 0;
}

