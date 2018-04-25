#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#include <string.h>
#include <stdio.h>
void thesec();
char daynumberchar[42][3];
int thedayn[42]={0};
int thechangemonth,thechangeyear,nowyear,nowmonth;
void GetMonth(int D, int md, int n);
void puttheday();
void intchange();
void thesecforchange();
void sxchange();
void subiao();
void ymcc();

DWORD WINAPI ThreadProc2( LPVOID lpParam )
{
	MOUSEMSG m;
	while(true)
	{
	m = GetMouseMsg();	
	if(m.x>=260 && m.x<=300 && m.y>=109 && m.y<=140){
	if(m.uMsg==WM_LBUTTONDOWN){
	thechangemonth--;
	if(thechangemonth==0){
		thechangemonth=12;
		thechangeyear--;
	}
	clearrectangle(0,105,120,140);
	clearrectangle(0,180,380,480);
	GetMonth(thechangeyear,thechangemonth , 0);
	puttheday();
	ymcc();
	}
	}else if(m.x>=320 && m.x<=360 && m.y>=109 && m.y<=140){
	if(m.uMsg==WM_LBUTTONDOWN){
	thechangemonth++;
	if(thechangemonth==13){
		thechangemonth=1;
		thechangeyear++;
	}
	clearrectangle(0,105,120,140);
	clearrectangle(0,180,380,480);
	GetMonth(thechangeyear,thechangemonth , 0);
	puttheday();
	ymcc();
	}
	}else if(m.x>=320 && m.x<=380 && m.y>=480 && m.y<=520){
	if(m.uMsg==WM_LBUTTONDOWN){
	thechangemonth=nowmonth;
	thechangeyear=nowyear;
	clearrectangle(0,105,120,140);
	clearrectangle(0,180,380,480);
	GetMonth(thechangeyear,thechangemonth , 0);
	puttheday();
	ymcc();
	}
	}
	}
	return 0;
}
void main()
{
    initgraph(380, 520);
	setbkcolor(RGB(31,31,31));
	cleardevice();	

	thesec();
	GetMonth(nowyear, nowmonth, 0);
	CreateThread( NULL,0, ThreadProc2, NULL , 0, NULL);
	puttheday();
	while(1){
	thesecforchange();
	Sleep(1000);
	clearrectangle(0,0,270,90);
	}
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}

void thesec(){
	time_t nowtime;
	struct tm *timeinfo;
	time( &nowtime );
	timeinfo = localtime( &nowtime );
	int sec,min,hour; 
	int year, month, day;
	char aa[6][2],bb[12][1],bb1[12][1],bb2[12][1],str[20];
	hour = timeinfo->tm_hour;
	min = timeinfo->tm_min;
	sec = timeinfo->tm_sec;
	year = timeinfo->tm_year + 1900;
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;
	nowyear=year;nowmonth=month;
	thechangemonth=month;thechangeyear=year;
	int m=month,d=day,y=year;
	if(m==1||m==2) {
	m+=12;
	y--;
	}
	int iWeek=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	switch(iWeek)
	{
	case 0: strcpy(str,"星期一\0"); break;
	case 1: strcpy(str,"星期二\0"); break;
	case 2: strcpy(str,"星期三\0"); break;
	case 3: strcpy(str,"星期四\0"); break;
	case 4: strcpy(str,"星期五\0"); break;
	case 5: strcpy(str,"星期六\0"); break;
	case 6: strcpy(str,"星期日\0"); break;
	}
	 aa[0][0]='0'+(hour-hour%10)/10;
	 aa[0][1]='0'+ hour%10;
	 aa[1][0]=':';
	 aa[1][1]=' ';
	 aa[2][0]='0'+(min-min%10)/10;
	 aa[2][1]='0'+min%10;
	 aa[3][0]=':';
	 aa[3][1]=' ';
	 aa[4][0]='0'+(sec-sec%10)/10;
	 aa[4][1]='0'+sec%10;
	 aa[5][0]='\0';
	bb[0][0]='0'+year/1000;
	bb[1][0]='0'+((year-year%100)/100)%10;
	bb[2][0]='0'+((year-year%10)/10)%10;
	bb[3][0]='0'+year%10;
	bb[4][0]='\0';


	bb1[0][0]='0'+(month-month%10)/10;
	bb1[1][0]='0'+month%10;
	bb1[2][0]='\0';


	bb2[0][0]='0'+(day-day%10)/10;;
	bb2[1][0]='0'+day%10;
	bb2[2][0]='\0';

	LOGFONT r;
	gettextstyle(&r);                
	r.lfHeight = 44;   
	r.lfEscapement = 0;
	r.lfOrientation = 0;
	_tcscpy(r.lfFaceName, _T("黑体"));   
	r.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&r);                    
	outtextxy(15, 10,_T(aa[0]));

	LOGFONT fr;
	gettextstyle(&fr);                
	fr.lfHeight = 35;   
	fr.lfEscapement = 900;
	fr.lfOrientation = 900;
	_tcscpy(fr.lfFaceName, _T("黑体"));   
	fr.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&fr);                    
	outtextxy(260, 130,_T(">"));

	LOGFONT fr1;
	gettextstyle(&fr1);                
	fr1.lfHeight = 35;   
	fr1.lfEscapement = -900;
	fr1.lfOrientation = -900;
	_tcscpy(fr1.lfFaceName, _T("黑体"));   
	fr1.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&fr1);                    
	outtextxy(360, 112,_T(">"));


	char ya[10]="年\0",ma[10]="月\0",da[10]="日,\0";
	LOGFONT r1;
	gettextstyle(&r1);                
	r1.lfHeight = 18;   
	r1.lfEscapement = 0;
	r1.lfOrientation = 0;
	_tcscpy(r1.lfFaceName, _T("黑体"));   
	r1.lfQuality = DEFAULT_QUALITY;	
	settextcolor(RGB(141,205,49));
	setbkmode(TRANSPARENT);
	settextstyle(&r1);                    
	outtextxy(15, 60,_T(bb[0]));
	outtextxy(55, 60,_T(ya));
	outtextxy(75, 60,_T(bb1[0]));
	outtextxy(95, 60,_T(ma));
	outtextxy(115, 60,_T(bb2[0]));
	outtextxy(135, 60,_T(da));
	outtextxy(160, 60,_T(str));

	LOGFONT r2;
	gettextstyle(&r2);                
	r2.lfHeight = 20;   
	r2.lfEscapement = 0;
	r2.lfOrientation = 0;
	_tcscpy(r2.lfFaceName, _T("黑体"));   
	r2.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&r2);                    
	outtextxy(15, 110,_T(bb[0]));
	outtextxy(55, 110,_T(ya));
	outtextxy(75, 110,_T(bb1[0]));
	outtextxy(95, 110,_T(ma));

	char theday[50]="日    一     二     三     四     五    六\0";
	LOGFONT ra;
	gettextstyle(&ra);                
	ra.lfHeight = 16;   
	ra.lfEscapement = 0;
	ra.lfOrientation = 0;
	_tcscpy(ra.lfFaceName, _T("黑体"));   
	ra.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&ra);
	outtextxy(20, 150,_T(theday));

	LOGFONT fh;
	gettextstyle(&fh);                
	fh.lfHeight = 30;   
	fh.lfEscapement = 0;
	fh.lfOrientation = 0;
	_tcscpy(fh.lfFaceName, _T("黑体"));   
	fh.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&fh);
	outtextxy(320, 480,_T("Back"));

}

void intchange(){
	int j;
	char c[3];
	for(j=0;j<42;j++){
		if(thedayn[j]==0){
			strcpy(daynumberchar[j]," ");
		}else if(1<=thedayn[j] && thedayn[j]<=31){
			if(0<thedayn[j] && thedayn[j]<=9){
			c[0]='0';
			c[1]=thedayn[j]+'0';
			c[2]='\0';
			}else{
			c[0]=thedayn[j]/10+'0';
			c[1]=thedayn[j]%10+'0';
			c[2]='\0';
			}
			strcpy(daynumberchar[j],c);
		}
		if(strlen(daynumberchar[j])<=1){
			strcpy(daynumberchar[j]," ");
		}
	}
}
void GetMonth(int D, int md, int n)
{
 int fuck;
 for(fuck=0;fuck<42;fuck++)
 thedayn[fuck]=0;
 int N ,m,d,y,c,Wd;
 int i,maxday,i1; 
 int j1c=0;
 if(md>=13||md<=0)  //判断月份
  printf("出错咯!"); 
 else
 {
  for(i1=0;;md++,i1++) 
  {
   if(md==0) 
   { 
    md=12; 
    D-=1; 
   } 
   else 
    if(md==13) 
    {
     md=1; 
     D+=1; 
    } 
    m=md; 
    
    if(0<m&&m<=12) 
    { 
     switch(m) 
     { 
     case 1:maxday=31;break; 
     case 2:if(D%4==0&&D%100!=0||D%400==0) 
          maxday=29; 
         else 
          maxday=28; 
     break; 
     case 3:maxday=31;break; 
     case 4:maxday=30;break; 
     case 5:maxday=31;break; 
     case 6:maxday=30;break; 
     case 7:maxday=31;break; 
     case 8:maxday=31;break; 
     case 9:maxday=30;break; 
     case 10:maxday=31;break; 
     case 11:maxday=30;break; 
     case 12:maxday=31;break; 
     default:printf("HAVE WRONG"); 
     } 
     if(0<m&&m<=2) 
     { 
      N=D-1; 
      m=m+10; 
     } 
     else 
     { 
      N=D; 
      m=m-2; 
     } 
     c=N/100; 
     y=N%100; 
     Wd=((1+(13*m-1)/5+y+y/4+c/4-2*c)%7+7)%7; 
     
     for(i=0,j1c=0;i<Wd;i++,j1c++) 
		thedayn[j1c]=0;
     for(d=1;d<=maxday;d++,j1c++) { 
		thedayn[j1c]=d;
		Wd=(Wd+1)%7; 
	 }

    if(i1==n) 
     break; 
  } 
 } 
	
}
intchange();
}

void puttheday()
{
	int ij=0;
	LOGFONT day;
	gettextstyle(&day);                
	day.lfHeight = 18;   
	day.lfEscapement = 0;
	day.lfOrientation = 0;
	_tcscpy(day.lfFaceName, _T("黑体"));   
	day.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&day);                    
	
	outtextxy(18, 190,_T(thedayn[0]));ij++;
	outtextxy(60, 190,_T(thedayn[1]));ij++;
	outtextxy(118, 190,_T(daynumberchar[ij]));ij++;
	outtextxy(174, 190,_T(daynumberchar[ij]));ij++;
	outtextxy(230, 190,_T(daynumberchar[ij]));ij++;
	outtextxy(285, 190,_T(daynumberchar[ij]));ij++;
	outtextxy(334, 190,_T(daynumberchar[ij]));ij++;

	outtextxy(18, 238,_T(daynumberchar[ij]));ij++;
	outtextxy(60, 238,_T(daynumberchar[ij]));ij++;
	outtextxy(118, 238,_T(daynumberchar[ij]));ij++;
	outtextxy(174, 238,_T(daynumberchar[ij]));ij++;
	outtextxy(230, 238,_T(daynumberchar[ij]));ij++;
	outtextxy(285, 238,_T(daynumberchar[ij]));ij++;
	outtextxy(334, 238,_T(daynumberchar[ij]));ij++;

	outtextxy(18, 288,_T(daynumberchar[ij]));ij++;
	outtextxy(60, 288,_T(daynumberchar[ij]));ij++;
	outtextxy(118, 288,_T(daynumberchar[ij]));ij++;
	outtextxy(174, 288,_T(daynumberchar[ij]));ij++;
	outtextxy(230, 288,_T(daynumberchar[ij]));ij++;
	outtextxy(285, 288,_T(daynumberchar[ij]));ij++;
	outtextxy(334, 288,_T(daynumberchar[ij]));ij++;

	outtextxy(18, 328+10,_T(daynumberchar[ij]));ij++;
	outtextxy(60, 328+10,_T(daynumberchar[ij]));ij++;
	outtextxy(118, 328+10,_T(daynumberchar[ij]));ij++;
	outtextxy(174, 328+10,_T(daynumberchar[ij]));ij++;
	outtextxy(230, 328+10,_T(daynumberchar[ij]));ij++;
	outtextxy(285, 328+10,_T(daynumberchar[ij]));ij++;
	outtextxy(334, 328+10,_T(daynumberchar[ij]));ij++;

	outtextxy(18, 378+10,_T(daynumberchar[ij]));ij++;
	outtextxy(60, 378+10,_T(daynumberchar[ij]));ij++;
	outtextxy(118, 378+10,_T(daynumberchar[ij]));ij++;
	outtextxy(174, 378+10,_T(daynumberchar[ij]));ij++;
	outtextxy(230, 378+10,_T(daynumberchar[ij]));ij++;
	outtextxy(285, 378+10,_T(daynumberchar[ij]));ij++;
	outtextxy(334, 378+10,_T(daynumberchar[ij]));ij++;

	outtextxy(18, 428+10,_T(daynumberchar[ij]));ij++;
	outtextxy(60, 428+10,_T(daynumberchar[ij]));ij++;
	outtextxy(118, 428+10,_T(daynumberchar[ij]));ij++;
	outtextxy(174, 428+10,_T(daynumberchar[ij]));ij++;
	outtextxy(230, 428+10,_T(daynumberchar[ij]));ij++;
	outtextxy(285, 428+10,_T(daynumberchar[ij]));ij++;
	outtextxy(334, 428+10,_T(daynumberchar[ij]));ij++;
}

void ymcc(){
	char bb[12][1],bb1[12][1],bb2[12][1],str[20];

	bb[0][0]='0'+thechangeyear/1000;
	bb[1][0]='0'+((thechangeyear-thechangeyear%100)/100)%10;
	bb[2][0]='0'+((thechangeyear-thechangeyear%10)/10)%10;
	bb[3][0]='0'+thechangeyear%10;
	bb[4][0]='\0';

	bb1[0][0]='0'+(thechangemonth-thechangemonth%10)/10;
	bb1[1][0]='0'+thechangemonth%10;
	bb1[2][0]='\0';
	char ya[10]="年\0",ma[10]="月\0";
	LOGFONT r2;
	gettextstyle(&r2);                
	r2.lfHeight = 20;   
	r2.lfEscapement = 0;
	r2.lfOrientation = 0;
	_tcscpy(r2.lfFaceName, _T("黑体"));   
	r2.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&r2);                    
	outtextxy(15, 110,_T(bb[0]));
	outtextxy(55, 110,_T(ya));
	outtextxy(75, 110,_T(bb1[0]));
	outtextxy(95, 110,_T(ma));
}
void thesecforchange(){
	time_t nowtime;
	struct tm *timeinfo;
	time( &nowtime );
	timeinfo = localtime( &nowtime );
	int sec,min,hour; 
	int year, month, day;
	char aa[6][2],bb[12][1],bb1[12][1],bb2[12][1],str[20];
	hour = timeinfo->tm_hour;
	min = timeinfo->tm_min;
	sec = timeinfo->tm_sec;
	year = timeinfo->tm_year + 1900;
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;
	int m=month,d=day,y=year;
	if(m==1||m==2) {
	m+=12;
	y--;
	}
	int iWeek=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	switch(iWeek)
	{
	case 0: strcpy(str,"星期一\0"); break;
	case 1: strcpy(str,"星期二\0"); break;
	case 2: strcpy(str,"星期三\0"); break;
	case 3: strcpy(str,"星期四\0"); break;
	case 4: strcpy(str,"星期五\0"); break;
	case 5: strcpy(str,"星期六\0"); break;
	case 6: strcpy(str,"星期日\0"); break;
	}

	 aa[0][0]='0'+(hour-hour%10)/10;
	 aa[0][1]='0'+ hour%10;
	 aa[1][0]=':';
	 aa[1][1]=' ';
	 aa[2][0]='0'+(min-min%10)/10;
	 aa[2][1]='0'+min%10;
	 aa[3][0]=':';
	 aa[3][1]=' ';
	 aa[4][0]='0'+(sec-sec%10)/10;
	 aa[4][1]='0'+sec%10;
	 aa[5][0]='\0';
	bb[0][0]='0'+year/1000;
	bb[1][0]='0'+((year-year%100)/100)%10;
	bb[2][0]='0'+((year-year%10)/10)%10;
	bb[3][0]='0'+year%10;
	bb[4][0]='\0';


	bb1[0][0]='0'+(month-month%10)/10;
	bb1[1][0]='0'+month%10;
	bb1[2][0]='\0';


	bb2[0][0]='0'+(day-day%10)/10;;
	bb2[1][0]='0'+day%10;
	bb2[2][0]='\0';

	LOGFONT r;
	gettextstyle(&r);                
	r.lfHeight = 44;   
	r.lfEscapement = 0;
	r.lfOrientation = 0;
	_tcscpy(r.lfFaceName, _T("黑体"));   
	r.lfQuality = DEFAULT_QUALITY;	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(&r);                    
	outtextxy(15, 10,_T(aa[0]));

	char ya[10]="年\0",ma[10]="月\0",da[10]="日,\0";
	LOGFONT r1;
	gettextstyle(&r1);                
	r1.lfHeight = 18;   
	r1.lfEscapement = 0;
	r1.lfOrientation = 0;
	_tcscpy(r1.lfFaceName, _T("黑体"));   
	r1.lfQuality = DEFAULT_QUALITY;	
	settextcolor(RGB(141,205,49));
	setbkmode(TRANSPARENT);
	settextstyle(&r1);                    
	outtextxy(15, 60,_T(bb[0]));
	outtextxy(55, 60,_T(ya));
	outtextxy(75, 60,_T(bb1[0]));
	outtextxy(95, 60,_T(ma));
	outtextxy(115, 60,_T(bb2[0]));
	outtextxy(135, 60,_T(da));
	outtextxy(160, 60,_T(str));
}