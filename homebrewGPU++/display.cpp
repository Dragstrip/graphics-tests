/*This program was written by Zac Botkin.
Built for: Part of a GPU.
Description:
Last changed:
*/
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <string>

int graphs[128][5][5];//Graphics chart.
int height=5,width=5;//Size of graphics.

char FB[80][80];//Frame Buffer.
int hSize=80,vSize=80;//Bounds of FB/Frame Buffer.

std::string frame;//Frame as string.

void graphsLoad(char gFile[]);
//Loads graphics into Graphs from file.
void framebuffPointer(int code,int *row,int *column);
//Writes Graphs[code] to FB/Frame Buffer at position row * column.
void framebuffStraight(int code, int *row,int *column);
//Writes Graphs[code] to FB/Frame Buffer at position row * column.
void printBuffer(int vPos,int hPos,int vView,int hView);
//Outputs FB/Frame Buffer to screen.
bool printStraight(int code,int& row,int& column,int& vPos,int& hPos,int& vView,int& hView);
//Writes Graphs[code] to screen.
///row: Position of beam vertically, if it reaches vView new frame is started.
///column: Position of beam horizontally, if it reaches hView new line is started.
///vPos: Vertical scrolling controls.
///hPos: Horizontal scrolling controls.
///vView: Vertical size of frame.
///hView: Horizontal size of frame.

void wordPros(int *rowP,int *colummP);
//
int main()
{
    //graphsLoad("C:\\Users\\tbweb\\Data\\C++\\Tests\\txt_files\\image_graphs.txt");
    graphsLoad("C:\\Users\\tbweb\\Data\\C++\\Tests\\txt_files\\ascii_graphs.txt");
    int row=0,column=0;
    int vView=80,hView=80;
    int vPos=0,hPos=0;
    int have;
    /*
    int sheet[6479]={
'A','A','A','A','A','B','B','B','B','B','C','C','C','C','C','D','D','D','D','D','E','E','E','E','E','F','F','F','F','F','G','G','G','G','G','H','H','H','H','H','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','R','R','R','R','R','C',///1
'A','A','A','A','A','B','B','B','B','B','C','C','C','C','C','D','D','D','D','D','E','E','E','E','E','F','F','F','F','F','G','G','G','G','G','H','H','H','H','H','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','R','R','R','R','R','C',///2
'A','A','A','A','A','B','B','B','B','B','C','C','C','C','C','D','D','D','D','D','E','E','E','E','E','F','F','F','F','F','G','G','G','G','G','H','H','H','H','H','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','R','R','R','R','R','C',///3
'A','A','A','A','A','B','B','B','B','B','C','C','C','C','C','D','D','D','D','D','E','E','E','E','E','F','F','F','F','F','G','G','G','G','G','H','H','H','H','H','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','R','R','R','R','R','C',///4
'A','A','A','A','A','B','B','B','B','B','C','C','C','C','C','D','D','D','D','D','E','E','E','E','E','F','F','F','F','F','G','G','G','G','G','H','H','H','H','H','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','R','R','R','R','R','C',///5
'A','A','A','A','A','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///6
'A','A','A','A','A','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///7
'A','A','A','A','A','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///8
'A','A','A','A','A','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///9
'A','A','A','A','A','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///10
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///11
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///12
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///13
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///14
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///15
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///16
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///17
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///18
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///19
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///20
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///21
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///22
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///23
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///24
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///25
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///26
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///27
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///28
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///29
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///30
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///31
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///32
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///33
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///34
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///35
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///36
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///37
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///38
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///39
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///40
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///41
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///42
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///43
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///44
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///45
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///46
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///47
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///48
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///49
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///50
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///51
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///52
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///53
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///54
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///55
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///56
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///57
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///58
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///59
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///60
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///61
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///62
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///63
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///64
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///65
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///66
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///67
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///68
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///69
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///70
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///71
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///72
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///73
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///74
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///75
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///76
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///77
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///78
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',///79
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C'///80
};
    int off=0;//amount of vary.
    int strt;//position in frame.
    int line;//line number.
    int pos;//position of code to send.
    for(off=0;off<10;off++)
    {
        hPos=off;
        for(strt=0;strt<6480;strt++)
        {
            line=(strt%80)+1;
            pos=off+strt;
            if(pos>(80*line))
            {
                pos-=80;
            }
            printStraight(sheet[pos],row,column,vPos,hPos,vView,hView);
        }
        printStraight(0,row,column,vPos,hPos,vView,hView);
    }
    //*/
    //*
    //int sheet[16][16]={
    int sheet[16][16]={
'A','B','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'C','C','C','C','C','G','C','C','C','C','C','C','C','E','C','C',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','E','C',
'C','C','C','C','C','C','C','F','C','C','G','C','C','C','C','C',
'C','E','C','C','C','G','C','C','C','C','C','C','C','C','C','C',
'C','C','C','C','C','C','C','C','C','C','C','E','C','C','C','C',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'C','A','C','C','A','C','C','C','C','C','C','C','A','C','C','C',
'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B',
'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D',
'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D',
'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D'
};
    int off=1;//amount of vary.
    int strt;//position in frame.
    int line;//line number.
    int pos;//position of code to send.
    //for(off=0;off<10;off++)
    {
        hPos=off;
        for(strt=0;strt<272;strt++)
        {
            line=(strt/80)+1;//find what line it is
            pos=off+strt;
            //if(pos>(80*line))
            if(pos>80)
            {
                pos-=80;

            }
            std::cout<<sheet[line][pos]<<std::endl;
            printStraight(sheet[line][pos],row,column,vPos,hPos,vView,hView);
            //printStraight(0,row,column,vPos,hPos,vView,hView);
        }
        //std::cout<<"done";
        row=vView;
        printStraight(0,row,column,vPos,hPos,vView,hView);
    }
    //*/
    bool check=false;
    //char gFile[]=;//File with graphics.
    //wordPros(&row,&column);
    /*
    while(check==false)
        check=printStraight(65,row,column,vPos,hPos,vView,hView);
            hPos++;
        check=false;
    */

    //while((clock()%)!=0);
    //while(true)
    {

        /*
        while(check==false)
            check=printStraight(66,row,column);
        check=false;
        while(check==false)
            check=printStraight(67,row,column);
        check=false;
        while(check==false)
            check=printStraight(68,row,column);
        */
    }
    /*
    for(int off=0,count=0;count<800;off++,count++)
    {
        if(off>=hSize)
        {
            off-=hSize;
        }
        //while((clock()%20)!=0);
        printBuffer(0,off,vSize,hSize);
        //printf("%d",count);
    }
    //printBuffer(0,30,vSize,hSize);
    */
    return 0;
}

void framebuffPointer(int code,int *rowP,int *columnP)
{
    char pos[5][5];//Pointer.
    int row=*rowP,column=*columnP;
    for(int vrt=0;vrt<height;vrt++)
    {
        for(int hrz=0;hrz<width;hrz++)
        {
            if(graphs[code][vrt][hrz]==0)
            {
                //pos[vrt][hrz]=' ';
            }
            else
            {
                pos[vrt][hrz]=219;
            }
        }
    }
    for(int vrt=0;vrt<height;vrt++)
    {
        for(int hrz=0;hrz<width;hrz++)
        {
            if(row+vrt<vSize&&column+hrz<hSize)
            {
                FB[row+vrt][column+hrz]=pos[vrt][hrz];
            }
        }
    }
    return;
}

void framebuffStraight(int code,int *rowP,int *columnP)
{
    for(int vrt=0;vrt<height;vrt++)
    {
        for(int hrz=0;hrz<width;hrz++)
        {
            if(*rowP+vrt<vSize&&*columnP+hrz<hSize)
            {
                if(graphs[code][vrt][hrz]==0)
                {
                    //FB[*rowP+vrt][*columnP+hrz]=' ';
                }
                else if(graphs[code][vrt][hrz]==1)
                {
                    FB[*rowP+vrt][*columnP+hrz]=219;
                }
            }
        }
    }
    return;
}

void printBuffer(int vPos,int hPos,int vView,int hView)
{
    std::string frame;
    printf("Start.\n");
    //cout<<"Start.\n";
    for(int row=vPos,vCount=0;vCount<vView;row++,vCount++)
    {
        if(row>=vSize)
        {
            row=row-vSize;
        }
        for(int column=hPos,hCount=0;hCount<hView;column++,hCount++)
        {
            if(column>=hSize)
            {
                column=column-hSize;
            }
            //putchar(FB[row][column]);
            frame.push_back(FB[row][column]);
            //cout.put(FB[row][column]);
        }
        //putchar('\n');//Return beam.
        frame.push_back('\n');
        //cout.put('\n');
    }
    std::cout<<frame;
}
//*
///row: Position of beam vertically, if it reaches vView new frame is started.
///column: Position of beam horizontally, if it reaches hView new line is started.
///vPos: Vertical scrolling controls.
///hPos: Horizontal scrolling controls.
///vView: Vertical size of frame.
///hView: Horizontal size of frame.
bool printStraight(int code,int& row,int& column,int& vPos,int& hPos,int& vView,int& hView)
{
    int fast=1;
    if(row<vView)
    {
        if(vPos>vSize)
        {
            vPos-=vSize;//scroll offscreen.
        }
        if(column<hView)
        {
            if(hPos>hSize)
            {
                hPos-=hSize;//scroll offscreen.
            }
            //printf("%2d",code);
            if(graphs[code][vPos%height][hPos%width]==0)
            {
                if(fast>0)
                {
                    frame.push_back(32);//put blank.
                    frame.push_back(32);
                }
                else
                {
                    putchar(32);
                    putchar(32);
                }
            }
            else if(graphs[code][vPos%height][hPos%width]==1)
            {
                if(fast>0)
                {
                    frame.push_back(219);//put solid.
                    //frame.push_back(219);
                }
                else
                {
                    putchar(219);
                    //putchar(219);
                }

            }
            hPos++;
            column++;//move beam right.
            return 0;
        }
        if(fast>0)
        {
            frame.push_back('\n');
        }
        else
        {
            putchar('\n');
        }
        column=0;//return beam left.
        vPos++;
        row++;//move beam down.
        return 0;
    }
    row=0;//return beam up.
    column=0;//return beam left.
    if(fast>0)
    {
        std::cout<<frame;
        frame.clear();
    }
    return 1;
}
//*/
void graphsLoad(char gFile[])
{
    //*
    char abr;
    int code;
    int have,num[3];
    char hold;
    FILE *fin;
    fin=fopen(gFile,"r");
    fscanf(fin,"%c",&hold);//Bounds checking.

    //printf("hold:%c|\n",hold);
    while(hold!='E')//Has it reached the end of content.
    {
        //fscanf(fin,"%3i",&num);//Input address of graphic.
        //fscanf(fin,"%1i%1i%1i",&num[0],&num[1],&num[2]);
        fscanf(fin,"%1c",&abr);
        code=abr;
        //code=(num[0]*100)+(num[1]*10)+num[2];
        //printf("num[0]:%d num[1]:%d num[2]:%d",num[0],num[1],num[2]);
        //printf("code:%dgraph:\n",code);
        for(int row=0;row<height;row++)
        {
            for(int column=0;column<width;column++)
            {
                fscanf(fin,"%1i",&have);
                //printf("%d",have);
                graphs[code][row][column]=(have-1);//Put graphics in array Graphs at address code.
            }
            //printf("\n");
        }
        fscanf(fin,"%c",&hold);//Bounds checking.
        //printf("hold:%c\n",hold);
    }
    //*/
    /*
    graphs[][0][0]=,graphs[][0][1]=,graphs[][0][2]=,graphs[][0][3]=,graphs[][0][4]=;
    graphs[][1][0]=,graphs[][1][1]=,graphs[][1][2]=,graphs[][1][3]=,graphs[][1][4]=;
    graphs[][2][0]=,graphs[][2][1]=,graphs[][2][2]=,graphs[][2][3]=,graphs[][2][4]=;
    graphs[][3][0]=,graphs[][3][1]=,graphs[][3][2]=,graphs[][3][3]=,graphs[][3][4]=;
    graphs[][4][0]=,graphs[][4][1]=,graphs[][4][2]=,graphs[][4][3]=,graphs[][4][4]=;
    */
    /*
    ///A:
    graphs[65][0][0]=(0),graphs[65][0][1]=(0),graphs[65][0][2]=(1),graphs[65][0][3]=(0),graphs[65][0][4]=(0);///00100
    graphs[65][1][0]=0,graphs[65][1][1]=1,graphs[65][1][2]=0,graphs[65][1][3]=1,graphs[65][1][4]=0;///01010
    graphs[65][2][0]=0,graphs[65][2][1]=1,graphs[65][2][2]=1,graphs[65][2][3]=1,graphs[65][2][4]=0;///01110
    graphs[65][3][0]=0,graphs[65][3][1]=1,graphs[65][3][2]=0,graphs[65][3][3]=1,graphs[65][3][4]=0;///01010
    graphs[65][4][0]=0,graphs[65][4][1]=1,graphs[65][4][2]=0,graphs[65][4][3]=1,graphs[65][4][4]=0;///01010
    ///B:
    graphs[66][0][0]=0,graphs[66][0][1]=1,graphs[66][0][2]=1,graphs[66][0][3]=0,graphs[66][0][4]=0;///01100
    graphs[66][1][0]=0,graphs[66][1][1]=1,graphs[66][1][2]=0,graphs[66][1][3]=1,graphs[66][1][4]=0;///01010
    graphs[66][2][0]=0,graphs[66][2][1]=1,graphs[66][2][2]=1,graphs[66][2][3]=0,graphs[66][2][4]=0;///01100
    graphs[66][3][0]=0,graphs[66][3][1]=1,graphs[66][3][2]=0,graphs[66][3][3]=1,graphs[66][3][4]=0;///01010
    graphs[66][4][0]=0,graphs[66][4][1]=1,graphs[66][4][2]=1,graphs[66][4][3]=0,graphs[66][4][4]=0;///01100
    ///C:
    graphs[67][0][0]=0,graphs[67][0][1]=0,graphs[67][0][2]=1,graphs[67][0][3]=0,graphs[67][0][4]=0;///00100
    graphs[67][1][0]=0,graphs[67][1][1]=1,graphs[67][1][2]=0,graphs[67][1][3]=1,graphs[67][1][4]=0;///01010
    graphs[67][2][0]=0,graphs[67][2][1]=1,graphs[67][2][2]=0,graphs[67][2][3]=0,graphs[67][2][4]=0;///01000
    graphs[67][3][0]=0,graphs[67][3][1]=1,graphs[67][3][2]=0,graphs[67][3][3]=1,graphs[67][3][4]=0;///01010
    graphs[67][4][0]=0,graphs[67][4][1]=0,graphs[67][4][2]=1,graphs[67][4][3]=0,graphs[67][4][4]=0;///00100
    ///D:
    graphs[68][0][0]=0,graphs[68][0][1]=1,graphs[68][0][2]=1,graphs[68][0][3]=0,graphs[68][0][4]=0;///01100
    graphs[68][1][0]=0,graphs[68][1][1]=1,graphs[68][1][2]=0,graphs[68][1][3]=1,graphs[68][1][4]=0;///01010
    graphs[68][2][0]=0,graphs[68][2][1]=1,graphs[68][2][2]=0,graphs[68][2][3]=1,graphs[68][2][4]=0;///01010
    graphs[68][3][0]=0,graphs[68][3][1]=1,graphs[68][3][2]=0,graphs[68][3][3]=1,graphs[68][3][4]=0;///01010
    graphs[68][4][0]=0,graphs[68][4][1]=1,graphs[68][4][2]=1,graphs[68][4][3]=0,graphs[68][4][4]=0;///01100
    //*/
    /*
    ///E:
    graphs[69][0][0]=,graphs[69][0][1]=,graphs[69][0][2]=,graphs[69][0][3]=,graphs[69][0][4]=;
    graphs[69][1][0]=,graphs[69][1][1]=,graphs[69][1][2]=,graphs[69][1][3]=,graphs[69][1][4]=;
    graphs[69][2][0]=,graphs[69][2][1]=,graphs[69][2][2]=,graphs[69][2][3]=,graphs[69][2][4]=;
    graphs[69][3][0]=,graphs[69][3][1]=,graphs[69][3][2]=,graphs[69][3][3]=,graphs[69][3][4]=;
    graphs[69][4][0]=,graphs[69][4][1]=,graphs[69][4][2]=,graphs[69][4][3]=,graphs[69][4][4]=;
    ///F:
    graphs[70][0][0]=,graphs[70][0][1]=,graphs[70][0][2]=,graphs[70][0][3]=,graphs[70][0][4]=;
    graphs[70][1][0]=,graphs[70][1][1]=,graphs[70][1][2]=,graphs[70][1][3]=,graphs[70][1][4]=;
    graphs[70][2][0]=,graphs[70][2][1]=,graphs[70][2][2]=,graphs[70][2][3]=,graphs[70][2][4]=;
    graphs[70][3][0]=,graphs[70][3][1]=,graphs[70][3][2]=,graphs[70][3][3]=,graphs[70][3][4]=;
    graphs[70][4][0]=,graphs[70][4][1]=,graphs[70][4][2]=,graphs[70][4][3]=,graphs[70][4][4]=;
    ///G:
    graphs[71][0][0]=,graphs[71][0][1]=,graphs[71][0][2]=,graphs[71][0][3]=,graphs[71][0][4]=;
    graphs[71][1][0]=,graphs[71][1][1]=,graphs[71][1][2]=,graphs[71][1][3]=,graphs[71][1][4]=;
    graphs[71][2][0]=,graphs[71][2][1]=,graphs[71][2][2]=,graphs[71][2][3]=,graphs[71][2][4]=;
    graphs[71][3][0]=,graphs[71][3][1]=,graphs[71][3][2]=,graphs[71][3][3]=,graphs[71][3][4]=;
    graphs[71][4][0]=,graphs[71][4][1]=,graphs[71][4][2]=,graphs[71][4][3]=,graphs[71][4][4]=;
    ///H:
    graphs[72][0][0]=,graphs[72][0][1]=,graphs[72][0][2]=,graphs[72][0][3]=,graphs[72][0][4]=;
    graphs[72][1][0]=,graphs[72][1][1]=,graphs[72][1][2]=,graphs[72][1][3]=,graphs[72][1][4]=;
    graphs[72][2][0]=,graphs[72][2][1]=,graphs[72][2][2]=,graphs[72][2][3]=,graphs[72][2][4]=;
    graphs[72][3][0]=,graphs[72][3][1]=,graphs[72][3][2]=,graphs[72][3][3]=,graphs[72][3][4]=;
    graphs[72][4][0]=,graphs[72][4][1]=,graphs[72][4][2]=,graphs[72][4][3]=,graphs[72][4][4]=;
    ///I:
    graphs[73][0][0]=,graphs[73][0][1]=,graphs[73][0][2]=,graphs[73][0][3]=,graphs[73][0][4]=;
    graphs[73][1][0]=,graphs[73][1][1]=,graphs[73][1][2]=,graphs[73][1][3]=,graphs[73][1][4]=;
    graphs[73][2][0]=,graphs[73][2][1]=,graphs[73][2][2]=,graphs[73][2][3]=,graphs[73][2][4]=;
    graphs[73][3][0]=,graphs[73][3][1]=,graphs[73][3][2]=,graphs[73][3][3]=,graphs[73][3][4]=;
    graphs[73][4][0]=,graphs[73][4][1]=,graphs[73][4][2]=,graphs[73][4][3]=,graphs[73][4][4]=;
    ///J:
    graphs[74][0][0]=,graphs[74][0][1]=,graphs[74][0][2]=,graphs[74][0][3]=,graphs[74][0][4]=;
    graphs[74][1][0]=,graphs[74][1][1]=,graphs[74][1][2]=,graphs[74][1][3]=,graphs[74][1][4]=;
    graphs[74][2][0]=,graphs[74][2][1]=,graphs[74][2][2]=,graphs[74][2][3]=,graphs[74][2][4]=;
    graphs[74][3][0]=,graphs[74][3][1]=,graphs[74][3][2]=,graphs[74][3][3]=,graphs[74][3][4]=;
    graphs[74][4][0]=,graphs[74][4][1]=,graphs[74][4][2]=,graphs[74][4][3]=,graphs[74][4][4]=;
    ///K:
    graphs[75][0][0]=,graphs[75][0][1]=,graphs[75][0][2]=,graphs[75][0][3]=,graphs[75][0][4]=;
    graphs[75][1][0]=,graphs[75][1][1]=,graphs[75][1][2]=,graphs[75][1][3]=,graphs[75][1][4]=;
    graphs[75][2][0]=,graphs[75][2][1]=,graphs[75][2][2]=,graphs[75][2][3]=,graphs[75][2][4]=;
    graphs[75][3][0]=,graphs[75][3][1]=,graphs[75][3][2]=,graphs[75][3][3]=,graphs[75][3][4]=;
    graphs[75][4][0]=,graphs[75][4][1]=,graphs[75][4][2]=,graphs[75][4][3]=,graphs[75][4][4]=;
    ///L:
    graphs[76][0][0]=,graphs[76][0][1]=,graphs[76][0][2]=,graphs[76][0][3]=,graphs[76][0][4]=;
    graphs[76][1][0]=,graphs[76][1][1]=,graphs[76][1][2]=,graphs[76][1][3]=,graphs[76][1][4]=;
    graphs[76][2][0]=,graphs[76][2][1]=,graphs[76][2][2]=,graphs[76][2][3]=,graphs[76][2][4]=;
    graphs[76][3][0]=,graphs[76][3][1]=,graphs[76][3][2]=,graphs[76][3][3]=,graphs[76][3][4]=;
    graphs[76][4][0]=,graphs[76][4][1]=,graphs[76][4][2]=,graphs[76][4][3]=,graphs[76][4][4]=;
    ///M:
    graphs[77][0][0]=,graphs[77][0][1]=,graphs[77][0][2]=,graphs[77][0][3]=,graphs[77][0][4]=;
    graphs[77][1][0]=,graphs[77][1][1]=,graphs[77][1][2]=,graphs[77][1][3]=,graphs[77][1][4]=;
    graphs[77][2][0]=,graphs[77][2][1]=,graphs[77][2][2]=,graphs[77][2][3]=,graphs[77][2][4]=;
    graphs[77][3][0]=,graphs[77][3][1]=,graphs[77][3][2]=,graphs[77][3][3]=,graphs[77][3][4]=;
    graphs[77][4][0]=,graphs[77][4][1]=,graphs[77][4][2]=,graphs[77][4][3]=,graphs[77][4][4]=;
    ///N:
    graphs[78][0][0]=,graphs[78][0][1]=,graphs[78][0][2]=,graphs[78][0][3]=,graphs[78][0][4]=;
    graphs[78][1][0]=,graphs[78][1][1]=,graphs[78][1][2]=,graphs[78][1][3]=,graphs[78][1][4]=;
    graphs[78][2][0]=,graphs[78][2][1]=,graphs[78][2][2]=,graphs[78][2][3]=,graphs[78][2][4]=;
    graphs[78][3][0]=,graphs[78][3][1]=,graphs[78][3][2]=,graphs[78][3][3]=,graphs[78][3][4]=;
    graphs[78][4][0]=,graphs[78][4][1]=,graphs[78][4][2]=,graphs[78][4][3]=,graphs[78][4][4]=;
    ///O:
    graphs[79][0][0]=,graphs[79][0][1]=,graphs[79][0][2]=,graphs[79][0][3]=,graphs[79][0][4]=;
    graphs[79][1][0]=,graphs[79][1][1]=,graphs[79][1][2]=,graphs[79][1][3]=,graphs[79][1][4]=;
    graphs[79][2][0]=,graphs[79][2][1]=,graphs[79][2][2]=,graphs[79][2][3]=,graphs[79][2][4]=;
    graphs[79][3][0]=,graphs[79][3][1]=,graphs[79][3][2]=,graphs[79][3][3]=,graphs[79][3][4]=;
    graphs[79][4][0]=,graphs[79][4][1]=,graphs[79][4][2]=,graphs[79][4][3]=,graphs[79][4][4]=;
    ///P:
    graphs[80][0][0]=,graphs[80][0][1]=,graphs[80][0][2]=,graphs[80][0][3]=,graphs[80][0][4]=;
    graphs[80][1][0]=,graphs[80][1][1]=,graphs[80][1][2]=,graphs[80][1][3]=,graphs[80][1][4]=;
    graphs[80][2][0]=,graphs[80][2][1]=,graphs[80][2][2]=,graphs[80][2][3]=,graphs[80][2][4]=;
    graphs[80][3][0]=,graphs[80][3][1]=,graphs[80][3][2]=,graphs[80][3][3]=,graphs[80][3][4]=;
    graphs[80][4][0]=,graphs[80][4][1]=,graphs[80][4][2]=,graphs[80][4][3]=,graphs[80][4][4]=;
    ///Q:
    graphs[81][0][0]=,graphs[81][0][1]=,graphs[81][0][2]=,graphs[81][0][3]=,graphs[81][0][4]=;
    graphs[81][1][0]=,graphs[81][1][1]=,graphs[81][1][2]=,graphs[81][1][3]=,graphs[81][1][4]=;
    graphs[81][2][0]=,graphs[81][2][1]=,graphs[81][2][2]=,graphs[81][2][3]=,graphs[81][2][4]=;
    graphs[81][3][0]=,graphs[81][3][1]=,graphs[81][3][2]=,graphs[81][3][3]=,graphs[81][3][4]=;
    graphs[81][4][0]=,graphs[81][4][1]=,graphs[81][4][2]=,graphs[81][4][3]=,graphs[81][4][4]=;
    ///R:
    graphs[82][0][0]=,graphs[82][0][1]=,graphs[82][0][2]=,graphs[82][0][3]=,graphs[82][0][4]=;
    graphs[82][1][0]=,graphs[82][1][1]=,graphs[82][1][2]=,graphs[82][1][3]=,graphs[82][1][4]=;
    graphs[82][2][0]=,graphs[82][2][1]=,graphs[82][2][2]=,graphs[82][2][3]=,graphs[82][2][4]=;
    graphs[82][3][0]=,graphs[82][3][1]=,graphs[82][3][2]=,graphs[82][3][3]=,graphs[82][3][4]=;
    graphs[82][4][0]=,graphs[82][4][1]=,graphs[82][4][2]=,graphs[82][4][3]=,graphs[82][4][4]=;
    ///S:
    graphs[83][0][0]=,graphs[83][0][1]=,graphs[83][0][2]=,graphs[83][0][3]=,graphs[83][0][4]=;
    graphs[83][1][0]=,graphs[83][1][1]=,graphs[83][1][2]=,graphs[83][1][3]=,graphs[83][1][4]=;
    graphs[83][2][0]=,graphs[83][2][1]=,graphs[83][2][2]=,graphs[83][2][3]=,graphs[83][2][4]=;
    graphs[83][3][0]=,graphs[83][3][1]=,graphs[83][3][2]=,graphs[83][3][3]=,graphs[83][3][4]=;
    graphs[83][4][0]=,graphs[83][4][1]=,graphs[83][4][2]=,graphs[83][4][3]=,graphs[83][4][4]=;
    ///T:
    graphs[84][0][0]=,graphs[84][0][1]=,graphs[84][0][2]=,graphs[84][0][3]=,graphs[84][0][4]=;
    graphs[84][1][0]=,graphs[84][1][1]=,graphs[84][1][2]=,graphs[84][1][3]=,graphs[84][1][4]=;
    graphs[84][2][0]=,graphs[84][2][1]=,graphs[84][2][2]=,graphs[84][2][3]=,graphs[84][2][4]=;
    graphs[84][3][0]=,graphs[84][3][1]=,graphs[84][3][2]=,graphs[84][3][3]=,graphs[84][3][4]=;
    graphs[84][4][0]=,graphs[84][4][1]=,graphs[84][4][2]=,graphs[84][4][3]=,graphs[84][4][4]=;
    ///U:
    graphs[85][0][0]=,graphs[85][0][1]=,graphs[85][0][2]=,graphs[85][0][3]=,graphs[85][0][4]=;
    graphs[85][1][0]=,graphs[85][1][1]=,graphs[85][1][2]=,graphs[85][1][3]=,graphs[85][1][4]=;
    graphs[85][2][0]=,graphs[85][2][1]=,graphs[85][2][2]=,graphs[85][2][3]=,graphs[85][2][4]=;
    graphs[85][3][0]=,graphs[85][3][1]=,graphs[85][3][2]=,graphs[85][3][3]=,graphs[85][3][4]=;
    graphs[85][4][0]=,graphs[85][4][1]=,graphs[85][4][2]=,graphs[85][4][3]=,graphs[85][4][4]=;
    ///V:
    graphs[86][0][0]=,graphs[86][0][1]=,graphs[86][0][2]=,graphs[86][0][3]=,graphs[86][0][4]=;
    graphs[86][1][0]=,graphs[86][1][1]=,graphs[86][1][2]=,graphs[86][1][3]=,graphs[86][1][4]=;
    graphs[86][2][0]=,graphs[86][2][1]=,graphs[86][2][2]=,graphs[86][2][3]=,graphs[86][2][4]=;
    graphs[86][3][0]=,graphs[86][3][1]=,graphs[86][3][2]=,graphs[86][3][3]=,graphs[86][3][4]=;
    graphs[86][4][0]=,graphs[86][4][1]=,graphs[86][4][2]=,graphs[86][4][3]=,graphs[86][4][4]=;
    ///W:
    graphs[87][0][0]=,graphs[87][0][1]=,graphs[87][0][2]=,graphs[87][0][3]=,graphs[87][0][4]=;
    graphs[87][1][0]=,graphs[87][1][1]=,graphs[87][1][2]=,graphs[87][1][3]=,graphs[87][1][4]=;
    graphs[87][2][0]=,graphs[87][2][1]=,graphs[87][2][2]=,graphs[87][2][3]=,graphs[87][2][4]=;
    graphs[87][3][0]=,graphs[87][3][1]=,graphs[87][3][2]=,graphs[87][3][3]=,graphs[87][3][4]=;
    graphs[87][4][0]=,graphs[87][4][1]=,graphs[87][4][2]=,graphs[87][4][3]=,graphs[87][4][4]=;
    ///X:
    graphs[88][0][0]=,graphs[88][0][1]=,graphs[88][0][2]=,graphs[88][0][3]=,graphs[88][0][4]=;
    graphs[88][1][0]=,graphs[88][1][1]=,graphs[88][1][2]=,graphs[88][1][3]=,graphs[88][1][4]=;
    graphs[88][2][0]=,graphs[88][2][1]=,graphs[88][2][2]=,graphs[88][2][3]=,graphs[88][2][4]=;
    graphs[88][3][0]=,graphs[88][3][1]=,graphs[88][3][2]=,graphs[88][3][3]=,graphs[88][3][4]=;
    graphs[88][4][0]=,graphs[88][4][1]=,graphs[88][4][2]=,graphs[88][4][3]=,graphs[88][4][4]=;
    ///Y:
    graphs[89][0][0]=,graphs[89][0][1]=,graphs[89][0][2]=,graphs[89][0][3]=,graphs[89][0][4]=;
    graphs[89][1][0]=,graphs[89][1][1]=,graphs[89][1][2]=,graphs[89][1][3]=,graphs[89][1][4]=;
    graphs[89][2][0]=,graphs[89][2][1]=,graphs[89][2][2]=,graphs[89][2][3]=,graphs[89][2][4]=;
    graphs[89][3][0]=,graphs[89][3][1]=,graphs[89][3][2]=,graphs[89][3][3]=,graphs[89][3][4]=;
    graphs[89][4][0]=,graphs[89][4][1]=,graphs[89][4][2]=,graphs[89][4][3]=,graphs[89][4][4]=;
    ///Z:
    graphs[90][0][0]=,graphs[90][0][1]=,graphs[90][0][2]=,graphs[90][0][3]=,graphs[90][0][4]=;
    graphs[90][1][0]=,graphs[90][1][1]=,graphs[90][1][2]=,graphs[90][1][3]=,graphs[90][1][4]=;
    graphs[90][2][0]=,graphs[90][2][1]=,graphs[90][2][2]=,graphs[90][2][3]=,graphs[90][2][4]=;
    graphs[90][3][0]=,graphs[90][3][1]=,graphs[90][3][2]=,graphs[90][3][3]=,graphs[90][3][4]=;
    graphs[90][4][0]=,graphs[90][4][1]=,graphs[90][4][2]=,graphs[90][4][3]=,graphs[90][4][4]=;
    */
    return;
}

void wordPros(int *rowP,int *columnP)
{
    //HANDLE hstdin;
    //DWORD mode;
    //hstdin=GetStdHandle(STD_INPUT_HANDLE);
    //GetConsoleMode(hstdin,&mode);
    //SetConsoleMode(hstdin,0);
    int row=*rowP;
    int column=*columnP;
    int have;
    have=getchar();
    while(have!='`')
    {
        //while(have!='.')
        {
            if(have=='\n')
            {
                row=row+5;
                column=0;
            }
            else
            {
                //while(getchar()!='\n');
                framebuffStraight(have,&row,&column);
                //framebuffPointer(have,&row,&column);
                column=column+5;
            }
            have=getchar();
        }
        printBuffer(0,0,hSize,vSize);
        have=getchar();
    }
    *rowP=row;
    *columnP=column;
    //SetConsoleMode(hstdin,mode);
    return;
}
