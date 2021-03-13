/*This program was written by Zac Botkin.
Built for:
Description:
Last changed:
*/

#include <stdio.h>

int graphics[256][8][8];//Array holding characters.
int charList=256,charHeight=8,charWidth=8;//
#include "c:\users\tbweb\data\c++\includes\graphicsLoad\graphicsLoad.c"

int screenHeight=16,screenWidth=28;//

///Functions

void displayRow(int code);//Puts one row of characters on the screen.
int rasterBuff[28];
int lineNum,tile;

///Applications

    void wordPad();//Simple text editor.
    char text[476];//={32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
    int spot=0;
    void dPrintScreen();//Handles putting text on screen.

    void pong();//The game pong.

int main()
{
    graphicsLoadpp("C:\\Users\\tbweb\\Data\\C++\\Tests\\dat_files\\ascii_graphics8x8pp.dat");
    //text[465]=' ';
    //text[475]=' ';
    //wordPad();
    pong();
    return 0;
}

void pong()
{
    char field[476];
    int ballY,ballX;
    int moveY,moveX;
    int player1=0,player2=0;
    for(int c=0;c<476;c++)
    {
        field[c]=32;
    }
    ballY=10;
    ballX=15;
    moveY=1;
    moveX=1;
    for(int loop=0;loop<50;loop++)
    {
        field[(ballY*screenWidth)+ballX]=32;
        //
            ballX+=moveX;
            if(ballX<1)
            {
                moveX=1;
                player2++;
            }
            if(ballX+1>=screenWidth)
            {
                moveX=-1;
                player1++;
            }
            ///
            ballY+=moveY;
            if(ballY<3)
            {
                moveY=1;
            }
            if(ballY+3>screenHeight)
            {
                moveY=-1;
            }
        ///
        for(int bord=screenWidth;bord<(screenWidth*2);bord++)
        {
            field[bord]='-';
        }
        for(int bord=(screenWidth*15);bord<476;bord++)
        {
            field[bord]='-';
        }
        field[4]=player1+48;
        field[23]=player2+48;
        field[(ballY*screenWidth)+ballX]=66;
        ///
        for(int vrt=0;vrt<screenHeight;vrt++)
        {
            for(int hrz=0;hrz<screenWidth;hrz++)
            {
                displayRow(field[(vrt*screenWidth)+hrz]);
            }
        }
    }
    return;
}

void wordPad()
{
    char chr;
    for(int r=0;r<476;r++)
    {
        chr=getchar();//unbuffered
        //getchar();
        text[spot]=chr;
        dPrintScreen(text);
        spot++;
    }
    return;
}

void dPrintScreen(char text[])
{
    int textSize=476;
    for(int dot=0;dot<textSize;dot++)
    {
        if(text[dot]=='\n')
        {
            for(int fill=0;fill<(28-(dot%28));fill++)//<<<<<<
            {
                //displayRow('N');
                displayRow('L');
                textSize--;
            }
            textSize++;
        }
        else
        {
            displayRow(text[dot]);
        }
    }
    return;
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
                for(int hrz=0;hrz<charWidth;hrz++)//one segment
                {
                    if(graphics[rasterBuff[segment]][lineNum][hrz]==0)
                    {
                        putchar(177);
                    }
                    else if(graphics[rasterBuff[segment]][lineNum][hrz]==1)
                    {
                        putchar(32);
                        putchar(32);
                        //putchar(219);
                    }
                    else if(graphics[rasterBuff[segment]][lineNum][hrz]==2)
                    {
                        putchar(219);//(177);
                        //putchar(32);
                        //putchar(32);
                    }
                    else// if(graphics[rasterBuff[g]][lineNum][hrz]==3)
                    {
                        putchar(219);
                    }
                }
            }
            putchar('\n');
        }
        tile=0;
    }
    return;
}
