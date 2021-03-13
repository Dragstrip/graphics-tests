/*This program was written by Zac Botkin.
Built for:
Description:
Last changed:
*/

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

int graphics[256][8][8];//Array holding characters.
int charList=256,charHeight=8,charWidth=8;//Bounds of array graphics.

int screenHeight=16,screenWidth=28;//

///Functions

void graphicsLoad(char gFile[]);//Loads characters into ram from file gFile.
int graphicsLoadpp(char gFile[]);//

class stringBeam//
{
    public:
    void load(int code);
    //std::vector<char> Vframe;//
    std::string Sframe;//[28800];
    int stringLength=0;
    int column=0;
}Beam;


void beam(int code);//

void display(int code);//
int rasterBuff[28];///<<<<<<
int lineNum,tile=0;

///Applications

    void testCharacters_c(int from,int to);//Shows characters for examination.

int main()
{
    //graphicsLoad("C:\\Users\\tbweb\\Data\\C++\\Tests\\dat_files\\ascii_graphics8x8.txt");
    graphicsLoadpp("C:\\Users\\tbweb\\Data\\C++\\Tests\\dat_files\\ascii_graphics8x8pp.dat");
    ///*
    for(int j=0;j<2;j++)
    {
        std::cout<<j<<"\n\n\n\n";
        for(int i=0;i<476;i++)
        {
            display((i%26)+65);
            //std::cout<<(i%26)+65<<"\n";
        }
    }
    //*/
    //display(65);display(66);display(67);display(68);display(69);display(70);display(71);display(72);
    //display(73);display(74);display(75);display(76);display(77);display(78);display(79);display(80);
    //testCharacters_c(32,95);
    return 0;
}

void display(int code)
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
                    //beam(graphics[rasterBuff[segment]][lineNum][hrz]);
                    Beam.load(graphics[rasterBuff[segment]][lineNum][hrz]);
                }
            }
            //putchar('\n');
        }
        //putchar('\n');
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

void stringBeam::load(int code)
{
    //std::cout<<stringLength<<"\n";
    if(stringLength<=28672)
    {
        if(column>=224)
        {
            //Vframe.push_back('\n');
            Sframe.push_back('\n');
            //frame[stringLength]='\n';
            column=0;
            std::cout<<"\n"<<stringLength<<"\n";
            stringLength++;
        }
        if(code==0)
        {
            //putchar();
        }
        else if(code==1)
        {
            //Vframe.push_back(32);
            //Vframe.push_back(32);
            Sframe.push_back(32);
            Sframe.push_back(32);
            //frame[stringLength]=32;
            //frame[stringLength]=32;
            column++;
        }
        else if(code==2)
        {
            //Vframe.push_back(219);//(177);
            Sframe.push_back(219);
            column++;
        }
        else //if(code==3)
        {
            //Vframe.push_back(219);
            Sframe.push_back(219);
            column++;
        }
        stringLength++;
        /*
        alexa play awemawa.
        The lion sleeps tonight, awemawa, by the tokens, starting now, on amazon music
        ...
        ee, de, de, de, de, de, ee, ee, de, de wema ma mewa.
        ee, ee, ee, ee, ee, ee, ee, ee, ee, weda ma mewa.
        awemawa, awemawa, awemawa, awemawa, awemawa, awemawa, awemawa, awemawa.
        awemawa, awemawa, awemawa, awemawa, awemawa, awemawa, awemawa, awemawa.
        in the jungle, the mighty jungle, the lion sleeps tonight.
        In the jungle, the quite jungle, the lion sleeps tonight.*/
    }
    else
    {
        //static_cast<std::string>(Vframe);
        /*
        std::string Sframe[(Vframe.size())+1];
        for(int count=0;count<Vframe.size();count++)
        {
            Sframe[count]=Vframe[count];
            //std::cout<<Sframe[count]<<"\n";
        }
        //*/
        std::cout<<Sframe;
        stringLength=0;
        std::cout<<"\nDONE\n";
    }
    return;
}

void testCharacters_c(int from,int to)
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
            putchar('\n');
        }
        putchar('|');
        putchar('\n');
    }
    return;
}
/*
void graphicsLoad(char gFile[])
{
    /*do
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
int graphicsLoadpp(char gFile[])
{
    char bin;
    int code;
    char pixel;
    char start,end;//Start and End of file.
    FILE *fin;//File with graphics.
    fin=fopen(gFile,"r");//Open file.
    fscanf(fin,"%c",&start);
    if(start!=1)
    {
        return 1;
    }
    fscanf(fin,"%c",&end);//Bounds checking.
    while(end!=4)//Has it reached the end of content.
    {
        fscanf(fin,"%1c",&bin);
        code=static_cast<int>(bin);
        for(int row=0;row<8;row++)
        {
            for(int column=0;column<8;column++)
            {
                fscanf(fin,"%1i",&graphics[code][row][column]);//Put graphic in array Graphics at address code.
            }
        }
        fscanf(fin,"%c",&end);//Bounds checking.
    }
    return 0;
}
