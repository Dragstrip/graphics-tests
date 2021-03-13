/*This program was written by Zac Botkin.
Built for: Part of a GPU.
Description:
Last changed:
*/
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

int graphs[128][5][5];//Graphics chart.
int height=5,width=5;//Size of graphics.

char FB[80][80];//Frame Buffer.
int hSize=80,vSize=80;//Bounds of FB/Frame Buffer.

void graphsLoad();
//Loads graphics into Graphs from file.
void framebuffPointer(int code,int *row,int *column);
//Writes Graphs[code] to FB/Frame Buffer at position row*column.
void framebuffStraight(int code, int *row,int *column);
//
void print(int vPos,int hPos,int vView,int hView);
//Outputs FB/Frame Buffer to screen.

void wordPros(int *rowP,int *colummP);
//
int main()
{
    int row=0,column=0;
    int have;
    graphsLoad();
    wordPros(&row,&column);
    print(0,30,vSize,hSize);
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
                pos[vrt][hrz]=' ';
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

void print(int vPos,int hPos,int vView,int hView)
{
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
            putchar(FB[row][column]);
            //cout.put(FB[row][column]);
        }
        putchar('\n');//Return beam.
        //cout.put('\n');
    }

}
/*
{
    for(int row=0;row<vSize;row++)
    {
        for(int column=0;column<hSize;column++)
        {

        }
    }
    graphs[][][];
}
*/
void graphsLoad()
{
    char gFile[]="C:\\Users\\tbweb\\Data\\C++\\Tests\\txt_files\\graphics5x5.txt";//File with graphics.
    int code,have,num[3];
    char hold;
    FILE *fin;
    fin=fopen(gFile,"r");
    fscanf(fin,"%c",&hold);//Bounds checking.

    //printf("hold:%c\n",hold);
    while(hold!='E')//Has it reached the end of content.
    {
        fscanf(fin,"%1i%1i%1i",&num[0],&num[1],&num[2]);//Input address of graphic.
        code=(num[0]*100)+(num[1]*10)+num[2];
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
                column=column+5;
            }
            have=getchar();
        }
        print(0,0,hSize,vSize);
        have=getchar();
    }
    *rowP=row;
    *columnP=column;
    //SetConsoleMode(hstdin,mode);
    return;
}
