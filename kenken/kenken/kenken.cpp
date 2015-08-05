#include <stdio.h>
#include <time.h>
#include "iGraphics.h"
#define wx 520			// wx = windows size in x												
#define wy 520			// wy = windows size in y						
#define bl 100			// bl = button's length
#define bw 50			// bw = button's width
#define length 110		// length = cell's length
#define width 110		// width = cell's width
#define clue_x 5
#define clue_y 20

int page=0,move=-1,sec,g,min,n,ff=0,gg=0,f;

/* move = 900 means user click on (0,0) no. cell */
/* move = 1902 means here user enters 1 in (0,2) no. cell. 9 is an arbitary digit.  */

time_t start,end,endd;

int value3[3][3],value4[4][4];		// user enters values in 2D array
char z,tim[100],timer_min[100],timer_sec[100];
char str1[2],str2[2],str3[2],str4[2],str5[2],str6[2],str7[2],str8[2],str9[2],str10[3],str11[3],str12[3],str13[3],str14[3],str15[3],str16[3];

int solved31[3][3]={{2,3,1},{3,1,2},{1,2,3}};
int solved32[3][3]={{1,3,2},{2,1,3},{3,2,1}};
int solved33[3][3]={{1,2,3},{2,3,1},{3,1,2}};
int solved41[4][4]={{1,3,4,2},{3,1,2,4},{2,4,1,3},{4,2,3,1}};
int solved42[4][4]={{2,4,1,3},{3,1,4,2},{4,3,2,1},{1,2,3,4}};
int solved43[4][4]={{1,2,4,3},{2,4,3,1},{3,1,2,4},{4,3,1,2}};

void background()
{
	iClear();
	iSetColor(253,213,130);
	iFilledRectangle(0*wx,0*wy,wx,wy);
	iSetColor(0,0,0);
	iText(wx/2-200,wy-140,"  W E L C O M E   T O   K E N K E N  ",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(wx/2-70,wy-190,"Please Select One ->",GLUT_BITMAP_HELVETICA_18);
	iText(wx-138,10,"A TTSS Project",GLUT_BITMAP_9_BY_15);	
}

void startup()
{
	iClear();
	background();
	
	iSetColor(254,225,22);
	iFilledRectangle(wx/2-bl*.75,wy/2-bw/2,bl*1.5,bw);
	iFilledRectangle(wx/2-bl*.75,wy/4+bw/2,bl*1.5,bw);
	
	iSetColor(0,0,0);
	iText(wx/2-bl*.75+bl*1.5*.2,wy/2-bw/2+bw*.4,"New Game",GLUT_BITMAP_HELVETICA_18);
	iText(wx/2-bl*.75+bl*1.5*.18,wy/4+bw/2+bw*.4,"How to Play",GLUT_BITMAP_HELVETICA_18);
	
}

void back()
{
	iSetColor(254,225,22);
	iFilledRectangle(40,wy-60,bl,bw);
	iSetColor(0,0,0);
	iText(55,wy-60+bw*.4,"<- Back",GLUT_BITMAP_HELVETICA_18);
}

void instruction()
{
	iClear();
	iSetColor(253,213,130);
	iFilledRectangle(0*wx,0*wy,wx,wy);
	back();
	iSetColor(0,0,0);
	iText(15,wy-120400,"INSTRUCTIONS :",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(15,wy-160,"--> Put 1,2,3 for 3*3 and 1,2,3,4 for 4*4 in each row and  ",GLUT_BITMAP_HELVETICA_18);
	iText(52,wy-190,"column such that no digit is repeated in corresponding ",GLUT_BITMAP_HELVETICA_18);
	iText(52,wy-220,"row and column following the clues.",GLUT_BITMAP_HELVETICA_18);
	iText(52,wy-270,"Example: 3+  =1 and 2 or 2 and 1 depending on the ",GLUT_BITMAP_HELVETICA_18);
	iText(52,wy-290,"other digits of row and column.",GLUT_BITMAP_HELVETICA_18);
	iText(15,wy-360,"--> Click on a square and enter a number using keyboard.",GLUT_BITMAP_HELVETICA_18);
	iText(40,wy-420,"How fast you can solve that's your efficiency!",GLUT_BITMAP_TIMES_ROMAN_24);

}

void board ()
{
	iClear();
	background();
	back();
	iSetColor(254,225,22);
	iFilledRectangle(wx/2-180,wy/2-37,bl,bw);
	iFilledRectangle(wx/2+80,wy/2-37,bl,bw);
	
	iSetColor(0,0,0);
	iText(wx/2-180+bl*.2,wy/2-37+17," 3 * 3 ",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(wx/2+80+bl*.2,wy/2-37+17," 4 * 4 ",GLUT_BITMAP_TIMES_ROMAN_24);
}
void difficulty()
{
	iClear();
	background();
	back();
	iSetColor(254,225,22);
	iFilledRectangle(wx/4-(bl*1.2)/2,wy/2-127,bl,bw);
	iFilledRectangle(wx/2-bl/2,wy/2-127,bl*1.2,bw);
	iFilledRectangle(wx*.75-(bl*.6)/2,wy/2-127,bl,bw);
	
	iSetColor(0,0,0);
	iText(wx/4-(bl*1.2)/2+bl*.2,wy/2-127+bw*.4,"EASY",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(wx/2-bl/2+bl*.08,wy/2-127+bw*.4,"MEDIUM",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(wx*.75-(bl*.6)/2+bl*.15,wy/2-127+bw*.4,"HARD",GLUT_BITMAP_TIMES_ROMAN_24);
}
void stopwatch(int sec)
{
	if (g>=0)
		end=clock();
	g++;
	sec=(end-start)/CLOCKS_PER_SEC;
	min=sec/60;
	sec=sec%60;
	for (n=0;n<2;n++)
    {
        z=(min%10)+48;
        timer_min[1-n]=z;
        min=min/10;
    }
    timer_min[2]='\0';
	for (n=0;n<2;n++)
    {
        z=(sec%10)+48;
        timer_sec[1-n]=z;
        sec=sec/10;
    }
    timer_sec[2]='\0';
	iSetColor(0,0,0);
	iFilledRectangle(wx/2-(bl*1.20)/2,wy-10-bw,bl*1.20,bw);
	iSetColor(255,0,0);
	iText(wx/2-(bl*1.20)*.32,wy-10-bw+bl*1.20*.167,timer_min,GLUT_BITMAP_HELVETICA_18);
	iText(wx/2,wy-10-bw+bl*1.20*.167,":",GLUT_BITMAP_HELVETICA_18);
	iText(wx/2+(bl*1.20)*.167,wy-10-bw+bl*1.20*.167,timer_sec,GLUT_BITMAP_HELVETICA_18);
}
void puzzle(int n)
{
	iClear();
	iSetColor(253,213,130);
	iFilledRectangle(0*wx,0*wy,wx,wy);	
	
	iSetColor(254,225,22);
	iFilledRectangle((wx/2-bl*.6)/2-bl/2,wy-10-bw,bl,bw);
	iFilledRectangle(((wx/2+bl*.6)+(wx-bl*.6-10))/2-bl/2,wy-10-bw,bl,bw);
	iFilledRectangle(wx-bl*.6-10,wy-10-bw,bl*.6,bw);
	iSetColor(0,0,0);
	iText((wx/2-bl*.6)/2-bl/2+bl*.15,wy-10-bw+bw*.4,"CHECK",GLUT_BITMAP_HELVETICA_18);
	iText(((wx/2+bl*.6)+(wx-bl*.6-10))/2-bl/2+bl*.1,wy-10-bw+bw*.4,"RESTART",GLUT_BITMAP_HELVETICA_18);
	iText(wx-bl*.6-10+bl*.6*.2,wy-10-bw+bw*.4,"EXIT",GLUT_BITMAP_HELVETICA_18);
	if (ff==0)
		start=clock();
	
	ff++;
	int i,j;
	for ( i = 0 ; i < n ; i++ )
	{
		for ( j = 0 ; j < n ; j++)
		{
			if ((i==j)||(i==0 && j==2)||(i==2 && j==0)||(i==1 && j==3)||(i==3 && j==1))
			{
				iSetColor(252,214,171);
				iFilledRectangle(length*i,width*j,length,width);
			}
			else
			{
				iSetColor(255,255,255);
				iFilledRectangle(length*i,width*j,length,width);
			}
		}
	}
	stopwatch(start);
	
}

void puzzle33()
{
	iSetColor(0,0,0);
	
	iRectangle(0*length,0*width,1*length,2*width);
	iRectangle(0*length+1,0*width+1,1*length-2,2*width-2);
	iText(0*length+clue_x,2*width-clue_y,"2*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,2*width,2*length,1*width);
	iRectangle(0*length+1,2*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,3*width-clue_y,"2-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,2*width,2*length,1*width);
	iRectangle(0*length+1,2*width+1,2*length-2,1*width-2);
	iText(1*length+clue_x,2*width-clue_y,"8+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(2*length,1*width,1*length,2*width);
	iRectangle(2*length+1,1*width+1,1*length-2,2*width-2);
	iText(2*length+clue_x,3*width-clue_y,"2/",GLUT_BITMAP_HELVETICA_18);		
	
	iRectangle(0*length,0*width,3*length,3*width);
	iRectangle(0*length+1,0*width+1,3*length-2,3*width-2);

}

void puzzle32()
{
	iSetColor(0,0,0);
	
	iRectangle(0*length,0*width,1*length,2*width);
	iRectangle(0*length+1,0*width+1,1*length-2,2*width-2);
	iText(0*length+clue_x,2*width-clue_y,"2-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,2*width,2*length,1*width);
	iRectangle(0*length+1,2*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,3*width-clue_y,"1-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(2*length,1*width,1*length,2*width);
	iRectangle(2*length+1,1*width+1,1*length-2,2*width-2);
	iText(2*length+clue_x,3*width-clue_y,"3+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,0*width,3*length,3*width);
	iRectangle(0*length+1,0*width+1,3*length-2,3*width-2);
	iText(1*length+clue_x,2*width-clue_y,"6*",GLUT_BITMAP_HELVETICA_18);

}

void puzzle31()
{
	iSetColor(0,0,0);
	
	iRectangle(0*length,0*width,length,width);
	iRectangle(0*length+1,0*width+1,length-2,width-2);
	iText(0*length+clue_x,1*width-clue_y,"2",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,1*width,2*length,width);
	iRectangle(0*length+1,1*width+1,2*length-2,width-2);
	iText(0*length+clue_x,2*width-clue_y,"3*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,2*width,2*length,1*width);
	iRectangle(0*length+1,2*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,3*width-clue_y,"3+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(2*length,1*width,length,2*width);
	iRectangle(2*length+1,1*width+1,length-2,2*width-2);
	iText(2*length+clue_x,3*width-clue_y,"6*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(1*length,0*width,2*length,1*width);
	iRectangle(1*length+1,0*width+1,2*length-2,1*width-2);
	iText(1*length+clue_x,1*width-clue_y,"4+",GLUT_BITMAP_HELVETICA_18);	

}

void puzzle41()
{
	iSetColor(0,0,0);
	
	iRectangle(0*length,0*width,2*length,1*width);
	iRectangle(0*length+1,0*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,1*width-clue_y,"3*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(2*length,0*width,2*length,1*width);
	iRectangle(2*length+1,0*width+1,2*length-2,1*width-2);
	iText(2*length+clue_x,1*width-clue_y,"6+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,1*width,1*length,2*width);
	iRectangle(0*length+1,1*width+1,1*length-2,2*width-2);
	iText(0*length+clue_x,3*width-clue_y,"7+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(1*length,1*width,2*length,1*width);
	iRectangle(1*length+1,1*width+1,2*length-2,1*width-2);
	iText(1*length+clue_x,2*width-clue_y,"5+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(3*length,1*width,1*length,2*width);
	iRectangle(3*length+1,1*width+1,1*length-2,2*width-2);
	iText(3*length+clue_x,3*width-clue_y,"6*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(1*length,2*width,2*length,1*width);
	iRectangle(1*length+1,2*width+1,2*length-2,1*width-2);
	iText(1*length+clue_x,3*width-clue_y,"2*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,3*width,2*length,1*width);
	iRectangle(0*length+1,3*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,4*width-clue_y,"8*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(2*length,3*width,2*length,1*width);
	iRectangle(2*length+1,3*width+1,2*length-2,1*width-2);
	iText(2*length+clue_x,4*width-clue_y,"4+",GLUT_BITMAP_HELVETICA_18);	

}

void puzzle42()
{
	iSetColor(0,0,0);
	
	iRectangle(0*length,0*width,1*length-2,2*width);
	iRectangle(0*length+1,0*width+1,1*length-2,2*width-2);
	iText(0*length+clue_x,2*width-clue_y,"2-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(1*length,0*width,2*length,1*width);
	iRectangle(1*length+1,0*width+1,2*length-2,1*width-2);
	iText(1*length+clue_x,1*width-clue_y,"7+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(1*length,1*width,3*length,1*width);
	iRectangle(1*length+1,1*width+1,3*length-2,1*width-2);
	iText(1*length+clue_x,2*width-clue_y,"6*",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,2*width,2*length,1*width);
	iRectangle(0*length+1,2*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,3*width-clue_y,"5+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,3*width,2*length,1*width);
	iRectangle(0*length+1,3*width+1,2*length-2,1*width-2);
	iText(0*length+clue_x,4*width-clue_y,"1-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(2*length,2*width,1*length,2*width);
	iRectangle(2*length+1,2*width+1,1*length-2,2*width-2);
	iText(2*length+clue_x,4*width-clue_y,"3+",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(3*length,2*width,1*length,2*width);
	iRectangle(3*length+1,2*width+1,1*length-2,2*width-2);
	iText(3*length+clue_x,4*width-clue_y,"1-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(3*length,0*width,1*length,1*width);
	iRectangle(3*length+1,0*width+1,1*length-2,1*width-2);
	iText(3*length+clue_x,1*width-clue_y,"1",GLUT_BITMAP_HELVETICA_18);	

}

void puzzle43()
{
	iSetColor(0,0,0);
	
	iRectangle(0*length,0*width,4*length,4*width);
	iRectangle(0*length+1,0*width+1,4*length-2,4*width-2);
	
	iRectangle(2*length,1*width,1*length,2*width);
	iRectangle(2*length+1,1*width+1,1*length-2,2*width-2);
	iText(2*length+clue_x,3*width-clue_y,"1-",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(3*length,1*width,1*length,1*width);
	iRectangle(3*length+1,1*width+1,1*length-2,1*width-2);
	iText(3*length+clue_x,2*width-clue_y,"3",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(3*length,2*width,1*length,2*width);
	iRectangle(3*length+1,2*width+1,1*length-2,2*width-2);
	iText(3*length+clue_x,4*width-clue_y,"2/",GLUT_BITMAP_HELVETICA_18);
	
	iRectangle(0*length,3*width,3*length,1*width);
	iRectangle(0*length+1,3*width+1,3*length-2,1*width-2);
	iText(0*length+clue_x,4*width-clue_y,"12*",GLUT_BITMAP_HELVETICA_18);
	
	iLine(1*length,0*width,1*length,2*width);
	iLine(1*length+1,0*width+1,1*length+1,2*width+1);
	
	iLine(1*length,2*width,2*length,2*width);
	iLine(1*length+1,2*width+1,2*length+1,2*width+1);
	
	iText(0*length+clue_x,3*width-clue_y,"10+",GLUT_BITMAP_HELVETICA_18);
	
	iText(1*length+clue_x,2*width-clue_y,"96*",GLUT_BITMAP_HELVETICA_18);

}

void showText()
{
	iSetColor(0,0,0);
	iText(0*length+length*.4,0*width+width*.4,str1,GLUT_BITMAP_TIMES_ROMAN_24);		iText(0*length+length*.4,1*width+width*.4,str2,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(0*length+length*.4,2*width+width*.4,str3,GLUT_BITMAP_TIMES_ROMAN_24);		iText(1*length+length*.4,0*width+width*.4,str4,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1*length+length*.4,1*width+width*.4,str5,GLUT_BITMAP_TIMES_ROMAN_24);		iText(1*length+length*.4,2*width+width*.4,str6,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(2*length+length*.4,0*width+width*.4,str7,GLUT_BITMAP_TIMES_ROMAN_24);		iText(2*length+length*.4,1*width+width*.4,str8,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(2*length+length*.4,2*width+width*.4,str9,GLUT_BITMAP_TIMES_ROMAN_24);		iText(0*length+length*.4,3*width+width*.4,str10,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1*length+length*.4,3*width+width*.4,str11,GLUT_BITMAP_TIMES_ROMAN_24);	iText(2*length+length*.4,3*width+width*.4,str12,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(3*length+length*.4,3*width+width*.4,str13,GLUT_BITMAP_TIMES_ROMAN_24);	iText(3*length+length*.4,0*width+width*.4,str14,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(3*length+length*.4,1*width+width*.4,str15,GLUT_BITMAP_TIMES_ROMAN_24);	iText(3*length+length*.4,2*width+width*.4,str16,GLUT_BITMAP_TIMES_ROMAN_24);	
}

void assign(int n)
{
	int m,r,xc,yc;
	
	m=n/1000;
	r=((n%1000)-900);
	xc=r/10;
	yc=r%10;
	
	if (page>=31 && page <=33)
		value3[xc][yc]=m;
	else if (page>=41 && page <=43)
		value4[xc][yc]=m;
	
}

void error(int x,int y)
{
	iSetColor(255,0,0);
	iText(x*length+length/4,y*width+width/2.3,"wrong!",GLUT_BITMAP_TIMES_ROMAN_24);
}

void timer(int sec)
{
	iSetColor(254,233,80);
	iFilledRectangle(wx/2-1.5*length,wy/2-bw*1.2,3*length,bw*1.2);
	iSetColor(0,0,0);
	min=sec/60;
	sec=sec%60;
	for (n=0;n<2;n++)
    {
        z=(min%10)+48;
        timer_min[1-n]=z;
        min=min/10;
    }
    timer_min[2]='\0';
	for (n=0;n<2;n++)
    {
        z=(sec%10)+48;
        timer_sec[1-n]=z;
        sec=sec/10;
    }
    timer_sec[2]='\0';
	iSetColor(0,0,0);
	iText(wx/2-3*length*.09,wy/2-bw*1.2+bw*.8,timer_min,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(wx/2,wy/2-bw*1.2+bw*.8,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(wx/2+3*length*.04,wy/2-bw*1.2+bw*.81,timer_sec,GLUT_BITMAP_TIMES_ROMAN_24);
}
void congratz()
{
	iClear();
	iSetColor(253,213,130);
	iFilledRectangle(0*wx,0*wy,wx,wy);
	if (gg==0)
		endd=clock();
	gg++;
	sec=(endd-start)/CLOCKS_PER_SEC;
	iSetColor(254,233,80);
	iFilledRectangle(wx/2-1.5*length,wy/2,3*length,bw*1.2);
	iSetColor(0,0,0);
	iText(wx/2-1.5*length+3*length*.106,wy/2+.5*bw*1.2,"    W E L L    D O N E   ! ",GLUT_BITMAP_TIMES_ROMAN_24);
	timer(sec);

	iSetColor(254,225,22);
	iFilledRectangle(((wx/2+bl*.6)+(wx-bl*.6-10))/2-bl/2,wy-10-bw,bl,bw);
	iFilledRectangle(wx-bl*.6-10,wy-10-bw,bl*.6,bw);
	iSetColor(0,0,0);
	iText(((wx/2+bl*.6)+(wx-bl*.6-10))/2-bl/2+bl*.1,wy-10-bw+bw*.4,"RESTART",GLUT_BITMAP_HELVETICA_18);
	iText(wx-bl*.6-10+bl*.6*.2,wy-10-bw+bw*.4,"EXIT",GLUT_BITMAP_HELVETICA_18);

}
void check(int n)
{
	int count=0,i,j;
	if (n==3)
	{
		if (page==33)
			f=3;
		else if (page==32)
			f=2;
		else if (page==31)
			f=1;

		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				if (f==1)
				{	
					if (value3[i][j]!=solved31[i][j])
						error(i,j);
					else
						count++;
						
				}
				if(f==2)
				{
					if(value3[i][j]!=solved32[i][j])
						error(i,j);
					else
						count++;
				}
				if(f==3)
				{
					if(value3[i][j]!=solved33[i][j])
						error(i,j);
					else
						count++;
				}
			}
		}	if (count==9)
			congratz();
	}
	if (n==4)
	{
		if (page==43)
			f=3;
		else if (page==42)
			f=2;
		else if (page==41)
			f=1;

		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				if (f==1)
				{	
					if (value4[i][j]!=solved41[i][j])
						error(i,j);
					else
						count++;
						
				}
				if(f==2)
				{
					if(value4[i][j]!=solved42[i][j])
						error(i,j);
					else
						count++;
				}
				if(f==3)
				{
					if(value4[i][j]!=solved43[i][j])
						error(i,j);
					else
						count++;
				}
			}
		}	
		if (count==16)
			congratz();
	}
}
void restart()
{
	ff=0,gg=0,f=0;

	str1[0]='\0';	str2[0]='\0';	str3[0]='\0';	str4[0]='\0';
	str5[0]='\0';	str6[0]='\0';	str7[0]='\0';	str8[0]='\0';				
	str9[0]='\0';	str10[0]='\0';	str11[0]='\0';	str12[0]='\0';
	str13[0]='\0';	str14[0]='\0';	str15[0]='\0';	str16[0]='\0';
	
}

void iDraw()
{	
	iClear();
	
	if (page==0)
	{ 
		iClear();
		startup();
	}
	if (page==1)
	{ 
		iClear();
		board();
	}
	if (page==2)
	{
		iClear();
		instruction();
	}
	if ((page==3)||(page==4))
		difficulty();
	if (page>=31 && page<=33)					// page = 31 means it is 3*3 easy
	{
		puzzle(3);
		if (page==33)
			puzzle33();
		else if (page==32)
			puzzle32();
		else if (page==31)
			puzzle31();
	}
	if (page>=41 && page<=43)
	{
		puzzle(4);
		if(page==41)
			puzzle41();
		else if (page==42)
			puzzle42();
		else if (page==43)
			puzzle43();
	}
	if (move>1000)
		assign(move);
	if (move)
		showText();
	if(move==993)
		check(3);
	if(move==994)
		check(4);
	if(move==999)
		restart();
	
}
void iKeyboard(unsigned char key)
{
	if ((page>=31 && page<=33)||(page >=41 && page <=43))
	{
		if (move==900)
		{
			if (key == '1')
				move=1900;
			else if (key=='2')
				move=2900;
			else if (key=='3')
				move=3900;
			if (page >=41 && page <=43)
			{
				if (key=='4')
					move=4900;
			}
			str1[0]=key;
		}
		if (move==901)
		{
			if (key == '1')
				move=1901;
			else if (key=='2')
				move=2901;
			else if (key=='3')
				move=3901;
			if (page >=41 && page <=43)
			{
				 if (key=='4')
					move=4901;
			}
			str2[0]=key;
		}
		if (move==902)
		{
			if (key == '1')
				move=1902;
			else if (key=='2')
				move=2902;
			else if (key=='3')
				move=3902;
			if (page >=41 && page <=43)
			{
				 if (key=='4')
					move=4902;
			}
			str3[0]=key;
		}
		if (move==903)
		{
			if (key == '1')
				move=1903;
			else if (key=='2')
				move=2903;
			else if (key=='3')
				move=3903;
			else if (key=='4')
					move=4903;
			str10[0]=key;
		}
		if (move==910)
		{
			if (key == '1')
				move=1910;
			else if (key=='2')
				move=2910;
			else if (key=='3')
				move=3910;
			if (page >=41 && page <=43)
			{
				if (key=='4')
				move=4910;
			}
			str4[0]=key;
		}
		if (move==911)
		{
			if (key == '1')
				move=1911;
			else if (key=='2')
				move=2911;
			else if (key=='3')
				move=3911;
			if (page >=41 && page <=43)
			{
				if (key=='4')
					move=4911;
			}
			str5[0]=key;
		}
		if (move==912)
		{
			if (key == '1')
				move=1912;
			else if (key=='2')
				move=2912;
			else if (key=='3')
				move=3912;
			if (page >=41 && page <=43)
			{
				if (key=='4')
					move=4912;
			}
			str6[0]=key;
		}
		if (move==913)
		{
			if (key == '1')
				move=1913;
			else if (key=='2')
				move=2913;
			else if (key=='3')
				move=3913;
			else if (key=='4')
				move=4913;
			str11[0]=key;
		}
		if (move==920)
		{
			if (key == '1')
				move=1920;
			else if (key=='2')
				move=2920;
			else if (key=='3')
				move=3920;

			if (page >=41 && page <=43)
			{
				if (key=='4')
					move=4920;
			}
			str7[0]=key;
		}
		if (move==921)
		{
			if (key == '1')
				move=1921;
			else if (key=='2')
				move=2921;
			else if (key=='3')
				move=3921;
			if(page>=41 && page<=43)
			{
				if (key=='4')
					 move=4921;
			}
			str8[0]=key;
		}
		if (move==922)
		{
			if (key == '1')
				move=1922;
			else if (key=='2')
				move=2922;
			else if (key=='3')
				move=3922;
			if(page>=41 && page<=43)
			{
				if (key=='4')
					move=4922;
			}
			str9[0]=key;
		}
		if (move==923)
		{
			if (key == '1')
				move=1923;
			else if (key=='2')
				move=2923;
			else if (key=='3')
				move=3923;
			else if (key=='4')
				move=4923;
			str12[0]=key;
		}
		if (move==930)
		{
			if (key == '1')
				move=1930;
			else if (key=='2')
				move=2930;
			else if (key=='3')
				move=3930;
			else if (key=='4')
				move=4930;
			str14[0]=key;
		}
		if (move==931)
		{
			if (key == '1')
				move=1931;
			else if (key=='2')
				move=2931;
			else if (key=='3')
				move=3931;
			else if (key=='4')
				move=4931;
			str15[0]=key;
		}
		if (move==932)
		{
			if (key == '1')
				move=1932;
			else if (key=='2')
				move=2932;
			else if (key=='3')
				move=3932;
			else if (key=='4')
				move=4932;
			str16[0]=key;
		}
		if (move==933)
		{
			if (key == '1')
				move=1933;
			else if (key=='2')
				move=2933;
			else if (key=='3')
				move=3933;
			else if (key=='4')
				move=4933;
			str13[0]=key;
		}
	}
}
void iSpecialKeyboard(unsigned char){}
void iMouseMove(int,int){}
void iMouse(int button,int state,int mx,int my)
{
	if (page==0 && mx>=(wx/2-bl*.75) && mx<=(wx/2-bl*.75+bl*1.5))
	{
		if (my >= (wy/2-bw/2) && my <= (wy/2-bw/2+bw))
			page=1;
		else if (my >= (wy/4+bw/2) && my <= (wy/4+bw/2+bw))
			page=2;
	}	

	if (page==1 && my >= (wy/2-37) && my <= (wy/2-37+bw))
	{	
		if (mx >= (wx/2-180) && mx <= (wx/2-180+bl))
			page = 3;
		else if (mx >= (wx/2+80) && mx <= (wx/2+80+bl))
			page = 4;
	}
	if (mx>=40 && mx<=40+bl && my>=wy-60 && my<=wy-60+bw)
	{
		if (page==1 || page==2)
			page=0;	
	}
	if ( page==3 && my >= (wy/2-127) && my <= (wy/2-127+bw))
	{	
		if ( mx >= (wx/4-(bl*1.2)/2) && mx <= (wx/4-(bl*1.2)/2+bl) )
			page = 31;
		else if ( mx >= (wx/2-bl/2) && mx <= (wx/2-bl/2+bl*1.2) )
			page = 32;
		else if ( mx >= (wx*.75-(bl*.6)/2) && mx <= (wx*.75-(bl*.6)/2+bl) )
			page = 33;
	}
	if ( page == 4 && my >= 133 && my <= 183)
	{
		if ( mx >= (wx/4-(bl*1.2)/2) && mx <= (wx/4-(bl*1.2)/2+bl) )
			page = 41;
		else if ( mx >= (wx/2-bl/2) && mx <= (wx/2-bl/2+bl*1.2) )
			page = 42;
		else if ( mx >= (wx*.75-(bl*.6)/2) && mx <= (wx*.75-(bl*.6)/2+bl) )
			page = 43;
	}
	
	if ((page>=31 && page<=33)||(page>=41 && page<=43))
	{ 
		if( my >= (wy-10-bw) && my <= (wy-10-bw+bw) )
		{
			if ( mx >= (wx-bl*.6-10) && mx <= (wx-bl*.6-10)+bl*.6 )
				exit(0);
			else if( mx >=(((wx/2+bl*.6)+(wx-bl*.6-10))/2-bl/2) && mx <=(((wx/2+bl*.6)+(wx-bl*.6-10))/2-bl/2)+bl )
			{
				move = 999;			// restart
				page = 0;
			}
			else if (mx >= ((wx/2-bl*.6)/2-bl/2) && mx <= ((wx/2-bl*.6)/2-bl/2+bl) ) 
			{ 
				if (page>=31 && page <=33)
					move = 993;							// check in 3*3
				else if (page>=41 && page <=43)
					move = 994;							// check in 4*4
			}
		}
	
		else if (mx>=0*length && mx<=1*length)
		{
			if (my>=0*width && my<=1*width)
				move=900;
			else if (my>1*width && my<=2*width)
				move=901;
			else if (my>2*width && my<=3*width)
				move=902;
			else if ((page>=41 && page<=43) && (my>3*width && my<=4*width))
				move=903;
		}
		else if (mx>1*length && mx<=2*length)
		{
			if (my>=0*width && my<=1*width)
				move=910;
			else if (my>1*width && my<=2*width)
				move=911;
			else if (my>2*width && my<=3*width)
				move=912;
			else if ((page>=41 && page<=43) && (my>3*width && my<=4*width))
				move=913;
		}
		else if (mx>2*length && mx<=3*length)
		{
			if (my>=0*width && my<=1*width)
				move=920;
			else if (my>1*width && my<=2*width)
				move=921;
			else if (my>2*width && my<=3*width)
				move=922;
			else if ((page>=41 && page<=43) && (my>3*width && my<=4*width))
				move=923;
		}
		else if ((mx>3*length && mx<=4*length) && (page>=41 && page<=43)) 
		{
			if (my>=0*width && my<=1*width)
				move=930;
			else if (my>1*width && my<=2*width)
				move=931;
			else if (my>2*width && my<=3*width)
				move=932;
			else if (my>3*width && my<=4*width)
				move=933;
		}
	}
}
void main()
{	
	iInitialize(wx,wy,"kenken");
}