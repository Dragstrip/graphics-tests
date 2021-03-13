/*This program was written by Zac Botkin.
Built for:
Description:
Last changed:
*/

#include <stdio.h>
#include <windows.h>

int graphics[256][8][8];//Array holding characters.
int charList=256,charHeight=8,charWidth=8;//Bounds of array graphics.
#include "c:\users\tbweb\data\c++\includes\graphicsLoad\graphicsLoad.c"//Function to fill array graphics.

int screenHeight=16,screenWidth=28;//

///Functions

void graphicsLoad(char gFile[]);//Loads characters into ram from file gFile.

void beam(int code);//
#include "C:\Users\tbweb\Data\C++\includes\composite\composite.c"

void displayRow(int code);//Puts one row of characters on the screen.
int rasterBuff[28];
int lineNum,tile=0;

///Applications

    void testCharacters(int from,int to);//Shows characters for examination.

    void wordPad();//Simple text editor.
    char text[476];//={32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
    int spot=0;
    void dPrintScreen();//Handles putting text on screen.

    void pong();//The game pong.

int main()
{
    //graphicsLoad("C:\\Users\\tbweb\\Data\\C++\\Tests\\dat_files\\ascii_graphics8x8.txt");

    graphicsLoadpp("C:\\Users\\tbweb\\Data\\C++\\Tests\\dat_files\\ascii_graphics8x8pp.dat");
    //*
    for(int i=0;i<476;i++)
    {
        displayRow((i%64)+32);
    }
    pong();
    //wordPad();
    //*/
    //display(65);display(66);display(67);display(68);display(69);display(70);display(71);display(72);
    //display(73);display(74);display(75);display(76);display(77);display(78);display(79);display(80);
    //testCharacters(32,90);
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
        composite(0);
    }
    return;
}

void wordPad()
{

    HANDLE hstdin;
    DWORD mode;
    hstdin=GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hstdin,&mode);
    SetConsoleMode(hstdin,0);
    //////
    char chr;
    for(int r=0;r<476;r++)
    {
        text[spot]=getchar();//unbuffered
        //putchar(text[spot]);
        dPrintScreen(text);
        spot++;
    }
    SetConsoleMode(hstdin,mode);
    return;
}
/*
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
//*/
///*
void dPrintScreen(char text[])
{
    //for(int i=0;i<476;i++)
    //{
    //    putchar(text[i]);
    //}
    for(int vrt=0;vrt<screenHeight;vrt++)
    {
        //for(int hrz=screenWidth;hrz>=0;hrz--)
        for(int hrz=0;hrz<=screenWidth;hrz++)
        {
            if(text[(vrt*screenWidth)+hrz]=='\n')
            {
                for(;hrz>0;hrz--)
                {
                    displayRow('L');
                }
            }
            else
            {
                //printf("(%d)%d%c",hrz,vrt*screenWidth+hrz,text[vrt*screenWidth+hrz]);
                displayRow(text[(vrt*screenWidth)+hrz]);
            }
        }
    }
    return;
}
//*/

void testCharacters(int from,int to)
{
    for(int roundL=from;roundL<to;roundL++)
    {
        printf("%d\n",roundL);
        for(int roundH=0;roundH<charHeight;roundH++)
        {
            for(int roundW=0;roundW<charWidth;roundW++)
            {
                beam(graphics[roundL][roundH][roundW]);
            }
            //putchar('\n');
        }
        //putchar('|');
        //putchar('\n');
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
                for(int hrz=0;hrz<charWidth;hrz++)
                {
                    //putchar(67);
                    beam(graphics[rasterBuff[segment]][lineNum][hrz]);
                    //composite(graphics[rasterBuff[segment]][lineNum][hrz]);
                }
            }
            putchar('\n');
            //composite(0);
        }
        tile=0;
    }
    return;
}

void beam(int code)
{
    if(code==0)
    {
        //putchar();
    }
    else if(code==1)
    {
        putchar(32);
        putchar(32);
    }
    else if(code==2)
    {
        putchar(219);//(177);
    }
    else// if(code==3)
    {
        putchar(219);
    }
    return;
}

/*
void graphicsLoad(char gFile[])
{
    /\*do
    {
        fin.get();
        place++;
    }while(!=32);*\/
    char start,end,space,crlf,go,data,bin,hold;
    int place,code,pixel=0,chunk;
    int depth=0,height=0,width=0,block=0,list=0;
    std::ifstream fin;
    fin.open(gFile);

    fin.get(start);///<<<<<<<<<<<<<<<<<<< start heading
    //start=='\soh';
    place=0;
    for(place=0,fin.get(hold);hold!=32;place++)//Get depth. Color depth.
    {
        depth+=(std::pow(10,place))*(hold-48);
        fin.get(hold);
    }
    for(place=0,fin.get(hold);hold!=32;place++)//Get height. Vertical size of characters.
    {
        height+=std::pow(10,place)*(hold-48);
        fin.get(hold);
    }
    for(place=0,fin.get(hold);hold!=32;place++)//Get width. Horizontal size of characters.
    {
        width+=std::pow(10,place)*(hold-48);
        fin.get(hold);
    }
    for(place=0,fin.get(hold);hold!=32;place++)//Get block. How large is the array for characters.
    {
        block+=std::pow(10,place)*(hold-48);
        fin.get(hold);
    }
    for(place=0,fin.get(hold);hold!='\n';place++)//Get list. Number of characters.
    {
        list+=std::pow(10,place)*(hold-48);
        fin.get(hold);
    }//Get list.
    fin.get(go);///<<<<<<<<<<<<<<<<<< end heading/start data
    //go=='\stx';

    for(int graf=0;graf<list;graf++)//Check end.
    {
        fin.get(data);///<<<<<<<<<<<<<<<< start of non ascii data for block amount of bytes

        for(place=0;place<block;place++)
        {
            fin.get(bin);//Get part of code.
            //std::cout.put(bin);//Show the part.
            //code+bin^place//Add the part. 256 256 256 256
        }
        code=static_cast<int>(bin);
        //std::cout.put(code);

        for(int vrt=0;vrt<height;vrt++)//height
        {
            for(int hrz=0;hrz<width;hrz++)//width
            {
                chunk=(depth/10);
                if((depth%10)>0)
                {
                    chunk++;
                }
                for(place=0,fin.get(bin);place<chunk;)
                {
                    //putchar(bin);
                    if(bin>47&&bin<59)
                    {
                        //pixel+=std::pow(10,place)*(bin-48);
                        pixel=bin;
                        place++;
                    }
                    fin.get(bin);
                }
                std::cout.put(pixel);
                graphics[code][vrt][hrz]=pixel;
            }
        }
        fin.get(end);///<<<<<<<<<<<<<< end of each character's data
    }
    return;
}
*/
