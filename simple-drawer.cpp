#include "batchbmp.h"
#include "line.h"
//#include "test.h"

#include <iostream>


int main()
{
	bmp::BatchBitmap24 blackBitmap(200, 200);

	bmp::Color24 blue = {0, 0, 255};

	for(unsigned int iRow = 0; iRow < blackBitmap.getHeight(); ++iRow)
	{
		for(unsigned int iColumn = 0; iColumn < blackBitmap.getWidth(); ++iColumn)
		{
			blackBitmap.setPixel(iColumn, iRow, blue);
		}
	}

	bmp::Color24 red = {255, 0, 0};
	bmp::AbsoluteCoordinate end(blackBitmap);
	blackBitmap.setCurrentColor(red);
	if(!end.set(90, 50))
	{
		std::cout << "error!" << std::endl;
	}else
	{
		bmp::lineto myLine( end.convert() );
		myLine.applyTo(blackBitmap);
	}



	blackBitmap.save("foo.bmp");

	return 0;
}

