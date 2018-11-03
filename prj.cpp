

#include <stdio.h>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QTextStream>
#include <string.h>

FILE *file;
const int sqgrid = 32;
int breadth = 600;
int height = 600;
char single[3];
int curpos = 0;
int copyno;

bool moveselection=false;// for selection

FILE *testfile;
char filename[100];//for copy
char filename2[100];//for paste

char style[10]="c++";
char outputfile[100]="output.cpp";

char command[1000];//for commanding into system
char interfacing[1000];//multiple uses

char buffer[sqgrid*sqgrid];
int selection[sqgrid*sqgrid];
char projectname[100]="project.txt";

int selectionposx;
int selectionposy;
char compileroutput[1000];
int didwrong=0;

int scanner=0;
int maxshift=0;
int higher=0;
void readm();
void writing();
int MODE=1;//c++
//2=java


void compile (){
	FILE *pipes;
	char output[100];
	didwrong=0;
	printf("Before Compile\n");
	sprintf(command,"g++ -c %s",outputfile);
	if((pipes=popen(command,"rt"))!=NULL){
		//while(fgets(compileroutput,sizeof(compileroutput),pipes)){
		//	didwrong++;
		//	if(strlen(compileroutput)==0){
				//MessageBox(NULL,"Success","Compile Status",MB_OK);
		//		printf("%d %s",didwrong,compileroutput);
				//memset(compileroutput,0,sizeof(compileroutput));
		//	}
pclose(pipes);
		}
		//if (didwrong==0){
				printf("After Compilation\n");
	  	  //}	
	   	//sprintf(command,"g++ -c output.cpp");	
	   	//system(command);
	   	
	//}
	
	
}


void
inserttext (char wParam)
{

  memset (&buffer[curpos], wParam, 1);
  //sprintf(buffer,"%s%c",buffer,(char)wParam);
  curpos++;
  if (curpos >= sqgrid * sqgrid)
    {
      writing ();
    curpos -= 1;
//      memset (buffer, 0, sizeof (buffer));
    }
  //typer();

}

void
onStarting ()
{
  //buffer = getBuffer();
  file = fopen (projectname, "r");
  if (file == NULL)
    {
		memset(buffer,' ',sizeof(buffer));
    }
  else
    {
    	//while (fgets(pipe[pipectr],sizeof(pipe[pipectr]),file)!=NULL){
			
		//}
		
		//sprintf(buffer,"line count : %d",pipectr);
		//MessageBox(NULL,buffer,"Lines",MB_OK);
      //fgets (buffer, sizeof (buffer), file);
      fread(buffer,sizeof(buffer),1,file);
      fclose (file);
    }
  file = fopen (projectname, "w");

}

void
writing ()
{
  fwrite(buffer,sizeof(buffer),1,file);
//      fprintf(file,"%s",buffer);
  //fputs (buffer, file);
}
void
onClosing ()
{
  void writing ();
  writing ();
  fclose (file);

}



void reade(){//read END E
maxshift--;
		 sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
		 system (command);
}
void readb(){//read Block B
	while(scanner<sqgrid*sqgrid){
		//readingB
		if(buffer[scanner]=='s'){				
		 sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
		 system (command);
		}
		if(buffer[scanner]=='b'){
			readm();
		}
		//buffer[scanner]==' ' &&
		if( scanner>sqgrid && buffer[scanner-sqgrid]=='e'){
		 scanner=scanner-sqgrid;
		 while(buffer[scanner]==' ' && scanner<sqgrid*sqgrid){
		 	 scanner++;
		}
	 	 if(buffer[scanner]=='e' && scanner<sqgrid*sqgrid)
		  {
			  reade();
		  }
		 break;
		}
		
    scanner++;
	}	
	
}

void readm2(){//reading of TAG for F and adding  brace
//readM
maxshift++;
higher = higher > maxshift ? higher:maxshift;
sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
system (command);
sprintf(command,"echo { >> %s",outputfile);
system (command);


//now readb
scanner=scanner+sqgrid;
readb();
}

void readm(){ //reading of tag for B 
//readM
maxshift++;
higher = higher > maxshift ? higher:maxshift;
sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
system (command);
//sprintf(command,"echo { >> output.cpp");
//system (command);


//now readb
scanner=scanner+sqgrid;
readb();
}
void readp(){//reading of prototype and adding ;
//readM
//maxshift++;
sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
system (command);
sprintf(command,"echo ';' >> %s",outputfile);
system (command);


//now readb
//scanner=scanner+sqgrid;
//readb();
}

void output(){
	//sprintf(command,"echo off > %s",outputfile); //on windows
	sprintf(command,"echo > %s",outputfile);
	system (command);

//this is ZERO SCAN or RUN to generate PREPROCESSORS Properly
    scanner=0;
	while (scanner<sqgrid*sqgrid){
		
		if(buffer[scanner]=='h'){
			sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
			system (command);
		}
		scanner++;
	}
//this is ZERO SCAN or RUN to generate GLOBALS Properly
    scanner=0;
	while (scanner<sqgrid*sqgrid){
		
		if(buffer[scanner]=='g'){
			sprintf(command,"cat %.2d.txt >> %s",scanner,outputfile);
			system (command);
		}
		scanner++;
	}
	
	

	
		
//this is FIRST SCAN or RUN to generate function prototypes Headers Properly
    scanner=0;
	while (scanner<sqgrid*sqgrid){
		if(MODE==1)//only for c++
		if(buffer[scanner]=='f'){
			readp();

		}


//		sprintf(command,"type %.2d.txt >> output.cpp",scanner);
//		system (command);
		scanner++;
				
	}
	
	
//this is SECOND SCAN for generating functions
    scanner=0;
	while (scanner<sqgrid*sqgrid){
		if(buffer[scanner]==' '){
			
		}
		if(buffer[scanner]=='b'){
			readm();

		}
		if(buffer[scanner]=='f'){
			readm2();

		}

//		if(buffer[scanner]=='e'){
//			reade();

//		}
//		sprintf(command,"type %.2d.txt >> output.cpp",scanner);
//		system (command);
		scanner++;
			if(scanner%sqgrid==0 && higher!=0){
				//sprintf(interfacing,"%d",higher);
			   //MessageBox(NULL,interfacing,"scanner",MB_OK);
			   scanner+=sqgrid*higher;
			   //sprintf(interfacing,"%d-%d",higher,scanner);
			   //MessageBox(NULL,interfacing,"title",MB_OK);
			   maxshift=0;
			   higher=0;
		   }	
	}
}



class viewer : public QWidget{
	public:
	//QPen *red;
	QBrush *gray,*red,*white,*blue,*yellow,*green;
	QPen *whitepen,*blackpen;
	QFont *font;
	
	viewer();
	void paintEvent(QPaintEvent *e);
	void keyPressEvent(QKeyEvent *k);
	void typer(QPainter *p);
};

viewer *VIEWER;

void viewer :: paintEvent(QPaintEvent *e){
	Q_UNUSED(e);
	QPainter q(this);
	typer(&q);
}

void viewer :: typer(QPainter *p){
	p->setBrush(*white);
	p->setPen(*whitepen);
	p->setFont(*font);

	p->drawRect(0,0,600,600);


  //Drawing of bg boxes
  for (int y = 0; y < sqgrid; y++)
    {
      for (int x = 0; x < sqgrid; x++)
	{
		//Drawing of bg boxes
	
	p->setBrush(*gray);
	p->setPen(*whitepen);
	  p->drawRect ( x * 15, y * 15 + 6, //(x + 1) * 15,
		     //(y + 1) * 15 + 6);
		     15,15);
    //if the bg box has a file
    sprintf(filename,"%.2d.txt",sqgrid*x+y);
    if((testfile = fopen(filename,"r"))!=NULL){
    		p->setBrush(*red);
	  	  	  p->drawRect ( x * 15, y * 15 + 6, //(x + 1) * 15,
		     //(y + 1) * 15 + 6);
		     15,15);
		     if(sqgrid*x+y==curpos){
    			fread(interfacing,1,sizeof(interfacing),testfile);
			 }
		fclose(testfile);
			 
	}
	//SELECTIOn SHOWING
//	memset(probable,NULL,sizeof(probable));
	if(selection[sqgrid*x+y]!=0){
		p->setBrush(*yellow);
		p->drawRect ( x * 15, y * 15 + 6, //(x + 1) * 15,
		    // (y + 1) * 15 + 6);
		     15,15);
		     
    //SelectObject (bgdc, bgreen);
//if (selectionposx<x && selectionposy<y)
	//	Rectangle (bgdc, (x+selectionposx) * 15, (y+selectionposy) * 15 + 6,
	//	 ((x+selectionposx) + 1) * 15, ((y+selectionposy) + 1) * 15 + 6);
		     //probable[(sqgrid*(selectionposx)+(selectionposy))]=1;
//			 probable[(sqgrid*(x+selectionposx)+(y+selectionposy))]=1;
//			 probable[oldcurpos+curpos]=1;
	//sprintf(interfacing,"%d %d",(sqgrid*x+y)+(sqgrid*selectionposx+selectionposy),(y));
		 }

		//Cursor Display System , Highlight of Blue Color		 
	  if (sqgrid * x + y == curpos)
	    {
	      p->setBrush(*blue);
	      p->drawRect( x * 15, y * 15 + 6, //(x + 1) * 15,
			 //(y + 1) * 15 + 6);
			 15,15);
	    }

//for moving Selection in green doesnt work proper 
//works only for less than curpos, not greater than curpos		
//	if(selection[sqgrid*x+y]!=0){
// 
	 // if(probable[sqgrid*x+y]==1){
	 // 	SelectObject (bgdc, bgreen);
	 // 	Rectangle (bgdc, (x) * 15, (y) * 15 + 6,
	 // 	 ((x) + 1) * 15, ((y) + 1) * 15 + 6);
// 
	 // }
	// 	
		
			    
  		//Text(CHAR) display System on the Box
  		p->setPen(*whitepen);
	  sprintf (single, "%c", buffer[sqgrid * x + y]);  
  	  if (single[0] != NULL)
	    p->drawText( x * 15+2, y * 15+17, single);
	  if (single[0] == NULL)
	    p->drawText ( x * 15, y * 15, "X");

	}
    }








//Extra Display on UP DOWN KEYS
//  sprintf (filename, "%.2d.txt", curpos);
//sprintf(interfacing,"%d %d",selectionposx,selectionposy);
  //SetTextColor(bgdc,cblack);
  
  p->drawText( 0, 550, interfacing);
  memset(interfacing,0,sizeof(interfacing));
  p->drawText( 0, 525, compileroutput);
  //SHOWING OF TEXT on the CURSOR
  
  //	  if(curpos==i)
  //	  TextOut (bgdc,1,140,pipe[i],strlen(pipe[i]));
//showing of the green of probable copy position
	p->setPen(*blackpen);
    for (int y = 0; y < sqgrid; y++)
    {
      for (int x = 0; x < sqgrid; x++)
	{
		
		 if(selection[sqgrid*x+y]!=0){
	 		p->setBrush(*green);
	 		p->drawRect( (x+selectionposx) * 15, (y+selectionposy) * 15 + 6,
	 	 //((x+selectionposx) + 1) * 15, ((y+selectionposy) + 1) * 15 + 6);
			15,15);
			 }
		
	}
	}  
  
  





}

void setmodecpp(){
	sprintf(style,"C++");
	sprintf(outputfile,"output.cpp");
	VIEWER->setWindowTitle("FunktyperQt:CppMode");
	MODE=1;
}
void setmodejava(){
	sprintf(style,"Java");
	sprintf(outputfile,"MainActivity.java");
	VIEWER->setWindowTitle("FunktyperQt:JavaMode");
	MODE=2;
}

void viewer::keyPressEvent(QKeyEvent *k){
	int key = k->key();
	if (k->matches (QKeySequence::Copy)){
		copyno=curpos;
	}
	if (k->matches (QKeySequence::Cut)){
	}
	if (k->matches (QKeySequence::Paste)){
				  				  
		  	  //this is for normal copy paste
  			sprintf(filename,"%.2d.txt",curpos);
  			sprintf(filename2,"%.2d.txt",copyno);
  			 FILE *src;
  			 FILE *dest;
  			 char ch;
  			 src = fopen(filename2,"r");
  			 if (src!=NULL){
				   dest=fopen(filename,"w");
					  while((ch=fgetc(src))!=EOF){
						  fputc(ch,dest);
					  }
					  buffer[curpos]=buffer[copyno];
					  fclose(dest);
					  fclose(src);	   
			   
		  	  }

	}
	switch(key){
		case Qt::Key_Escape:
			qApp->quit();
		break;
		
	  case Qt::Key_B://statements
  	  case Qt::Key_E://end
  	  case Qt::Key_S:			 	
      case Qt::Key_F://functions
      case Qt::Key_H://headers
      case Qt::Key_G://globals
	case Qt::Key_Space:
	      inserttext (tolower(char(key)));

	  break;
	case Qt::Key_Return:
			sprintf(filename,"geany %.2d.txt",curpos);
			system(filename);
			//printf("heoolo");

	  break;
  case Qt::Key_C:
  	selection[curpos]=curpos;
  	
  break;  

case Qt::Key_D:
	memset(selection,NULL,sizeof(selection));
	
	moveselection=false;
	selectionposx=0;
	selectionposy=0;
break;

case Qt::Key_P:
	
	for (int y = 0; y < sqgrid; y++)
    {
      for (int x = 0; x < sqgrid; x++)
	{
		
		 if(selection[sqgrid*x+y]!=0){
	 		//SelectObject (bgdc, bgreen);
	 		//Rectangle (bgdc, (x+selectionposx) * 15, (y+selectionposy) * 15 + 6,
	 	 //((x+selectionposx) + 1) * 15, ((y+selectionposy) + 1) * 15 + 6);
//sprintf(command,"rename)
			sprintf(filename,"%.2d.txt",sqgrid*x+y);
			sprintf(filename2,"%.2d.txt",sqgrid*(x+selectionposx)+(y+selectionposy));
				 rename(filename,filename2);		 
				 buffer[sqgrid*(x+selectionposx)+(y+selectionposy)]=buffer[sqgrid*x+y];
				 buffer[sqgrid*x+y]=' ';
			 }
		
	}
	}  
  
	
	memset(selection,NULL,sizeof(selection));
	
	moveselection=false;
	selectionposx=0;
	selectionposy=0;	
break;
case Qt::Key_M:
	moveselection=!moveselection;
	
break;
	  
	case Qt::Key_Backspace:

	  break;

		case Qt::Key_Home:
			//if (buffer[curpos]==NULL){
				buffer[curpos]='m';
				buffer[curpos+1]='n';
				buffer[sqgrid+curpos+1]='b';
				buffer[sqgrid+sqgrid+curpos]='e';
			//}
			break;
	case Qt::Key_Up:
	
	
	  if (curpos > 0){
	    curpos--;
	    if (moveselection==true){
			selectionposy--;
		}
	  }
	
	
	
	  break;
	case Qt::Key_Down:
	

	  if (curpos < sqgrid * sqgrid - 1){
	    curpos++;
	    if (moveselection==true){
			selectionposy++;
		}
	  }

	  for (int i = 0; i <= curpos; i++){
	    if (buffer[i] == NULL){
	      buffer[i] = ' ';
		}
  	  }


	  break;
	case Qt::Key_Left:
      if (curpos >= sqgrid){
	    curpos -= sqgrid;
	    if (moveselection==true){
			selectionposx--;
		}
	  }
	  break;
	case Qt::Key_Right:
	  if (curpos < sqgrid * sqgrid - sqgrid){
	    curpos += sqgrid;
	    if (moveselection==true){
			selectionposx++;
		}
	  }

	  for (int i = 0; i <= curpos; i++){
	    if (buffer[i] == NULL){
	      buffer[i] = ' ';
		}
	  }

	  break;
	case Qt::Key_Delete:
//	  memset (buffer, 0, sizeof (buffer));
sprintf(filename,"%.2d.txt",curpos);
remove(filename);
buffer[curpos]=' ';

	  break;
  case Qt::Key_F11:
  	output();
  	compile();
  	break;
  case Qt::Key_F12:
  	output();
  	break;
  
  
  case Qt::Key_F1:
  
  //sprintf(style,"c++");
  //sprintf(outputfile,"output.cpp");
setmodecpp();  
	
  break;
  case Qt::Key_F2:
  //sprintf(style,"%s",filename);
  //sprintf(outputfile,"%s",filename);
	//VIEWER->setWindowTitle("Lock");
  setmodejava();
  break;



	}
	repaint();
	
}

viewer :: viewer(){
	//red = new QPen(Qt::red,1,Qt::SolidLine);
	gray = new QBrush("#4A4A4A");
	red = new QBrush("#FF0000");
	white = new QBrush("#FFFFFF");
	blue = new QBrush("#08C2EE");
	yellow = new QBrush("#EEE508");
	green = new QBrush("#27EE08");
	
	whitepen = new QPen(Qt::white,1,Qt::SolidLine);
	blackpen = new QPen(Qt::black,1,Qt::SolidLine);
	
	font = new QFont("Courier",8);
}

	





int main(int argc,char **argv)
{
  onStarting ();

	QApplication app(argc,argv);
	viewer hwnd;
	hwnd.resize(600,600);
	hwnd.setWindowTitle("FunktyperQT");
	hwnd.show();
	 VIEWER = &hwnd;
	
	app.exec();
	
	onClosing();
	
	return 0;
  
}
