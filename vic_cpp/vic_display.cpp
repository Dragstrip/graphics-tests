/*This program was written by Zac Botkin.
For: Game engine.
Description: Simple background tile editor.
Last changed: 9/7/19
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

///graphics table
int graphics[256][8][8];//Table holding characters.
//using layout:[address][vertical pixel row][horizontal pixel row]

///load graphics
#include "c:\users\tbweb\data\c++\includes\graphicsLoad\graphicsLoad.c"

///write to frameBuffer
//ascii in frame out

///display frameBuffer

///output to screen

class buffer
{
public:
    buffer();

    void drawBackground(int address);//ascii in frame out
    //Precondition: int address set to possible address in graphics.
    //Postcondition: graphic at address inserted

    void displayScreen();//
    //Precondition: frameBuffer
    //Postcondition: frameBuffer has been output to screen.

    void rasterBeam(int color,int pixPos);
    //Precondition: color set to 0-3.
    //Postcondition: appended to frame

    void clearScreen();
    //Postcondition:

    int frameBuffer[1024][1792];//Array holding frame buffer.
    char frameAsString[1835009];


    int verticalInT;
    int horizontalInT;

    int tileRow;
    int tileColumn;
};

int main()
{
    std::cout<<"hi Mom.";
    graphicsLoadpp("C:\\Users\\tbweb\\Data\\C++\\vic_cpp\\ascii_graphics8x8pp.dat");
    buffer slide;
    slide.drawBackground(65);
    slide.displayScreen();
    return 0;
}

    buffer::buffer()
{
    tileRow=0;
    tileColumn=0;
}

void buffer::drawBackground(int address)
{
    for(verticalInT=0;verticalInT<8;verticalInT++)
    {
        for(horizontalInT=0;horizontalInT<8;horizontalInT++)
        {
            frameBuffer[tileRow+verticalInT][tileColumn+horizontalInT]=graphics[address][verticalInT][horizontalInT];
        }
    }
    if(tileColumn<8)
    {
        tileColumn++;
    }
    else
    {
        if(tileRow<8)
        {
            tileColumn=0;
            tileRow++;
        }
        else
        {
            tileColumn=0;
            tileRow=0;
        }
    }
    return;
}

void buffer::displayScreen()
{
    for(int bufferRow=0;bufferRow<1024;bufferRow++)
    {
        for(int bufferColumn=0;bufferColumn<1792;bufferColumn++)
        {
            rasterBeam((frameBuffer[bufferRow][bufferColumn]),(bufferRow*+bufferColumn));
        }
    }
    std::cout<<frameAsString;
    return;
}

void buffer::rasterBeam(int color,int pixPos)//pixel in, pixel out
{
    switch (color)
    {
        case 0:
            frameAsString[pixPos]=(32);//transparent
            break;
        case 1:
            frameAsString[pixPos]=(32);//base
            break;
        case 2:
            frameAsString[pixPos]=(177);//gray
            break;
        case 3:
            frameAsString[pixPos]=(219);//full
            break;
        default:
            frameAsString[pixPos]=(33);
            break;
    }
    return;
}

