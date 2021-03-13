
//Test composite.

#include <stdio.h>
#include "C:\Users\tbweb\Data\C++\Tests\includes\composite\composite.c"

int graphics[256][8][8];
#include "c:\users\tbweb\data\c++\tests\includes\graphicsLoad\graphicsLoad.c"

int charHeight=8,charWidth=8;

int screenHeight=16,screenWidth=28;

int rasterBuff[28];
int lineNum,tile;

int main()
{
    graphicsLoadpp("C:\\Users\\tbweb\\Data\\C++\\Tests\\dat_files\\ascii_graphics8x8pp.dat");

    displayRow(65);//1
    displayRow(65);//2
    displayRow(65);//3
    displayRow(65);//4
    displayRow(65);//5
    displayRow(65);//6
    displayRow(65);//7
    displayRow(65);//8
    displayRow(65);//9
    displayRow(65);//10
    displayRow(65);//11
    displayRow(65);//12
    displayRow(65);//13
    displayRow(65);//14
    displayRow(65);//15
    displayRow(65);//16
    displayRow(65);//17
    displayRow(65);//18
    displayRow(65);//19
    displayRow(65);//20
    displayRow(65);//21
    displayRow(65);//22
    displayRow(65);//23
    displayRow(65);//24
    displayRow(65);//25
    displayRow(65);//26
    displayRow(65);//27
    displayRow(65);//28
    composite(0);
    return 0;
}

void displayRow(int code)
{
    rasterBuff[tile]=code;
    tile++;
    if(tile>=screenWidth)
    {
        for(lineNum=0;lineNum<charHeight;lineNum++)//one row
        {
            for(int segment=0;segment<screenWidth;segment++)//one line
            {
                for(int hrz=0;hrz<charWidth;hrz++)
                {
                    composite(graphics[rasterBuff[segment]][lineNum][hrz]);
                    //printf("%d",graphics[rasterBuff[segment]][lineNum][hrz]);
                }
            }
            //putchar('\n');
            //composite();
        }
        tile=0;
        //composite(0);
    }
    return;
}
