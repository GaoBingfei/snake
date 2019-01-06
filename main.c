/*
　　　g++ *.cpp -lGL -lGLU -lglut
*/

#include<iostream>
#include <cstdio>
#include <unistd.h>
using namespace std;

#include<stdlib.h>
#include<time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <fstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPADDREES "127.0.0.1"	
class RGB{//颜色类
    public:
        RGB(const float a,const float b,const float c):R(a),G(b),B(c){}
        RGB():R(ran_number(10)/10.0f+0.1f),G(ran_number(10)/10.0f+0.1f),B(ran_number(10)/10.0f+0.1f){}
        float R;
        float G;
        float B;
    private:
        int ran_number(int num){
            return rand()%num;
        }
};
class snake_node{//蛇类
    public:
        snake_node(){}
        int Dir;//方向
        int X;
        int Y;
        RGB rgb;
        class snake_node *prev;
        class snake_node *next;

};

class Snak{
    public:
        Snak(RGB R,int x=7,int y=7,int nu=4):num(nu){
            for(int i=0;i<30;i++){
                for(int j=0;j<30;j++){
                    arr[i][j]=0;
                }
                game_score=0;
            }
         snake_node *node;
	 	 head=tail=&ch[0];
         head->X=x;
         head->Y=y;
         arr[x][y]=1;
         head->Dir=0;
         head->rgb=R;
         for(int i=0;i<nu-1;i++){
	    	node=&ch[i+1];
            node->X=tail->X;
            node->Y=tail->Y-1;
            arr[node->X][node->Y]=1;
            node->Dir=0;
            node->rgb=RGB();
            node->prev=tail;
            tail->next=node;
            tail=node;
            }
          head->prev=NULL;
          tail->next=NULL;
        }
        void Snak_init(RGB R,int x=7,int y=7,int nu=4){
          for(int i=0;i<30;i++){
                for(int j=0;j<30;j++){
                    arr[i][j]=0;
                }
            }
         game_score=0;
         snake_node *node;
	 	 head=tail=&ch[0];
         head->X=x;
         head->Y=y;
         arr[x][y]=1;
         head->Dir=0;
         head->rgb=R;
         for(int i=0;i<nu-1;i++){
	    	node=&ch[i+1];
            node->X=tail->X;
            node->Y=tail->Y-1;
            arr[node->X][node->Y]=1;
            node->Dir=0;
            node->rgb=RGB();
            node->prev=tail;
            tail->next=node;
            tail=node;
            }
          head->prev=NULL;
          tail->next=NULL; 
        
        }
        void Snak_move(){
        	snake_node *node=NULL;
        	node1=*tail;
            tail->Dir=head->Dir;
            switch(head->Dir){
            case 0:
                tail->X=head->X;
                head->Y==29?tail->Y=0:tail->Y=head->Y+1;
                arr[node1.X][node1.Y]=0;
                arr[tail->X][tail->Y]=1;
                break;
            case 1:
                tail->X=head->X;
                head->Y==0?tail->Y=29:tail->Y=head->Y-1;
                arr[node1.X][node1.Y]=0;
                arr[tail->X][tail->Y]=1;
                break;
            case 2:
                tail->Y=head->Y;
                head->X==0?tail->X=29:tail->X=head->X-1;
                arr[node1.X][node1.Y]=0;
                arr[tail->X][tail->Y]=1;
                break;
            case 3:
                tail->Y=head->Y;
                head->X==29?tail->X=0:tail->X=head->X+1;
                arr[node1.X][node1.Y]=0;
                arr[tail->X][tail->Y]=1;
                break;
            }
            tail->next=head;
            head->prev=tail;
            node1.prev->next=NULL;
            head=tail;
            tail=tail->prev;
            for(node=head;node->next!=NULL;node=node->next){
            	node->rgb=node->next->rgb;
            }
            node->rgb=node1.rgb;
            head->prev=NULL;
            tail->next=NULL;
        }
		void snak_add(){
			snake_node *node=&ch[num+1];
			node->X=-1;
			node->Y=-1;
			node->Dir=node1.Dir;
			node->rgb=RGB();
			node->next=NULL;
			node->prev=tail;
			tail->next=node;
			arr[node->X][node->Y]=1;
			num=num+1;
			tail=node;
		}
    int arr[30][30];
    int num;
    int game_score;
    snake_node *head;
    snake_node *tail;
    private:
    snake_node node1;
	snake_node ch[900];
};

class snake_food{
    public:
        snake_food(){
            for(int i=0;i<30;i++){
                for(int j=0;j<30;j++){
                    arr[i][j]=0;
                }
            }
            food_old=0;
        }
        void snake_init(){
            for(int i=0;i<30;i++){
                for(int j=0;j<30;j++){
                    arr[i][j]=0;
                }
            }
            food_old=0;
        }
        void Onfood( Snak & S1,int num=2){
        	number=num;
        	int snak_num=0;
        	for(int i=0;i<30;i++){
                for(int j=0;j<30;j++){
                    if(S1.arr[i][j]==1 || this->arr[i][j]==1){
                    	snak_num++;
                    }
                }
            }
            if(snak_num==900)return;
            for(int j=0;j<num;j++){
                int num=ran_number(900-snak_num-j);
                for(int i=0;i<=num;i++){
                    if(S1.arr[i/30][i%30]==1 || this->arr[i/30][i%30]==1){
                        num++;
                    }
                    if(i==num){
                        this->arr[i/30][i%30]=1;
						this->rgb[i/30][i%30]=RGB();
                    }
                }
            }
        }
        void Onfood( Snak & S1,Snak & S2,int num=2){
        	number=num;
        	int snak_num=0;
        	for(int i=0;i<30;i++){
                for(int j=0;j<30;j++){
                    if(S1.arr[i][j]==1 || this->arr[i][j]==1||S2.arr[i][j]==1){
                    	snak_num++;
                    }
                }
            }
            if(snak_num==900)return;
            for(int j=0;j<num;j++){
                int num=ran_number(900-snak_num-j);
                for(int i=0;i<=num;i++){
                    if(S1.arr[i/30][i%30]==1 || this->arr[i/30][i%30]==1||S2.arr[i/30][i%30]==1){
                        num++;
                    }
                    if(i==num){
                        this->arr[i/30][i%30]=1;
						this->rgb[i/30][i%30]=RGB();
                    }
                }
            }
        }
	void netfood(int x,int y){
		rgb[x][y]=RGB();
	}
    int arr[30][30];
    RGB rgb[30][30];
    int number;
    int food_old;
    private:
        int ran_number(int num){
            return rand()%num;
        }
};


namespace Draw{
	int pause=1;//暂停
	int finish=0;//游戏结束标记
	int timebase=350;//游戏时间间隔
	int mouse=1;//
	int mode=1;//模式
	string modes="Console Game";
   	int number=1;//蛇的个数
    string numbers="    Player 1";
	int win=0;//菜单句柄
	int window_game=0;//游戏句柄
        int old1_num;// 单机一条蛇的最高分
        int old2_num;//单机两条蛇的最高分
        int old3_num;//联网的最高分
	//联网模式变量
	struct sockaddr_in ser;
	int s_fd;
	int arr1[110][3]={-1};
	int arr2[110][3]={-1};
	//--------------------------------
	
	//函数申明
	void menu_init();
	void map_font(int x,int y,string ch,const RGB &RG);
	int read_num();//都最高分
        void write_num();//写最高分
	void sendToInter();//与服务器减缓信息
	void sendToInteri();
	
	const GLfloat Pi = 3.1415926536f;
	static const double RX1 = 2.0/38.0;
	static const double RY1 = 2.0/30.0;
	static const double RX = 1.0/38.0;
	static const double RY = 1.0/30.0;
	snake_food food;//定义食物
	Snak S2(RGB(1.0f,0.0f,0.0f));//蛇2初始化
	Snak S1(RGB(1.0f,0.0f,0.0f),21,7);//蛇1初始化
	void foodinit(){
		if(mode==2){
			if(number==1){food.Onfood(S1,S2,10);}
		}else{
			number==2?food.Onfood(S1,S2,5):food.Onfood(S1,2);
		}
	}//食物初始化
	void draw_end(){glutSwapBuffers();}//结束绘图
	void map_init(){//游戏地图初始化
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	    glLoadIdentity();// 复位
 	    //glColor3f(0.5f,0.5f,0.5f);
 	    //glRectf(-1.0f, -1.0f, 1.0f, 1.0f);
 	    //glColor3f(0.0f,0.0f,0.0f);
 	    //glRectf(-1.0f+RX1, -1.0f+RY1, RX1*10, RY1*14);
 	    glTranslatef(-1.0f, 1.0f, 0.0f);//初始化位置
 	    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//模式
 	    glBegin(GL_QUADS);
 	    glColor3f(0.1f,0.1f,0.1f);//线颜色
 		for (int i = 0; i < 30; ++i){
		for (int j = 0; j < 30; ++j){
 			glVertex3f((j ) * RX1, -(i ) * RY1, 0.0f);
 			glVertex3f((j+1) * RX1, -(i ) * RY1, 0.0f);
 			glVertex3f((j+1) * RX1, -(i+1) * RY1, 0.0f);
			glVertex3f((j ) * RX1, -(i+1) * RY1, 0.0f);
 		}
 	}
 	glEnd();
	}
	void onfood(){//绘制食物
	    for(int x=0;x<30;x++){
		for(int y=0;y<30;y++){
		    if(food.arr[x][y]==1){
		 	glLoadIdentity();				// 复位
			glTranslatef(-1.0f, -1.0f, 0.0f);
	 		glTranslatef(x*2*RX+RX, y*2*RY+RY, 0.0f);//初始化位置

			GLfloat a = RY;
			GLfloat bx = RX * cos(18 * Pi/180);
			GLfloat by = RX* sin(18 * Pi/180);
			GLfloat cy = -RY * cos(18 * Pi/180);
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glColor3f(food.rgb[x][y].R,food.rgb[x][y].G,food.rgb[x][y].B);
			glRotatef(360, 0, 0, 180.0);
			glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, a, 0.0f);
			glVertex3f( RY/2, cy , 0.0f);
			glVertex3f(-bx, by, 0.0f);
			glVertex3f(bx, by, 0.0f);
			glVertex3f(-RY/2, cy, 0.0f);
			glVertex3f(0.0f, a, 0.0f);
			glEnd();

		    }
		}
	   }
	   glFlush();
	   //glutSwapBuffers();
	}
	void snak_body(int x,int y,int z,RGB & rgb)//画蛇身，xy坐标z方向 0 上 1下 2左 3右
	{
		int i;
		int n = 360;
		double RZ;

 		glLoadIdentity();// 复位
		glTranslatef(-1.0f, -1.0f, 0.0f);
 		glTranslatef(x*2*RX+RX, y*2*RY+RY, 0.0f);//初始化位置
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_POLYGON);
		glColor3f(rgb.R, rgb.G, rgb.B);
		for(i=0; i<=360; i++){
			glVertex2f(RX*cos(2*Pi/n*i), RY*sin(2*Pi/n*i));
		}
		glEnd();


 		glLoadIdentity();				// 复位
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glTranslatef(x*2*RX+RX, y*2*RY+RY, 0.0f);
		if(z==0){
			glRotatef(270, 0, 0, 1.0);
		}else if(z==1){
			glRotatef(90, 0, 0, 1.0);
		}else if(z==3){
			glRotatef(180, 0, 0, 1.0);
		}
 		glTranslatef(-RX, 0, 0.0f);//初始化位置

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);
		if(z==0||z==1){
			for(i=0; i<=360; i++){
				glVertex2f(RY*sin(2*Pi/n*i),RX*cos(2*Pi/n*i));
			}
		}else{
			for(i=0; i<=360; i++){
				glVertex2f(RX*cos(2*Pi/n*i), RY*sin(2*Pi/n*i));
			}
		}
		glEnd();

	glFlush();
	}

	void snak_head(int x,int y,int z,RGB & rgb)//画蛇头,xy坐标z方向 0 上 1下 2左 3右
	{
		int i;
		int n = 360;
		double RZ;
		GLfloat dx,dy,ddx,ddy;
	 	glLoadIdentity();				// 复位
		glTranslatef(-1.0f, -1.0f, 0.0f);
	 	glTranslatef(x*2*RX+RX, y*2*RY+RY, 0.0f);//初始化位置
 		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_POLYGON);
		glColor3f(rgb.R, rgb.G, rgb.B);
		for(i=0; i<=360; i++){
			glVertex2f(RX*cos(2*Pi/n*i), RY*sin(2*Pi/n*i));
		}
		glEnd();
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glTranslatef(x*2*RX+RX, y*2*RY+RY, 0.0f);//初始化位置
		if(z==0||z==3){
			glRotatef(180, 0, 0, 1.0);
		}
		glTranslatef(-RX/2, -RY/2, 0.0f);//初始化位置
		if(z==1||z==0){
			dx = RY/3;
			dy = RX/3;
		}else{
			dx = RX/3;
			dy = RY/3;
		}
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);
		for(i=0; i<=360; i++){
			glVertex2f(dx*cos(2*Pi/n*i), dy*sin(2*Pi/n*i));
		}
		if(z==1||z==0){
			ddx = RY/5;
			ddy = RX/5;
		}else{
			ddx = RX/5;
			ddy = RY/5;
		}
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		for(i=0; i<=360; i++){
			glVertex2f(ddx*cos(2*Pi/n*i), ddy*sin(2*Pi/n*i));
		}
		glEnd();

		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glTranslatef(x*2*RX+RX, y*2*RY+RY, 0.0f);
		if(z==1||z==3){
			glRotatef(180, 0, 0, 1.0);
		}
		glTranslatef(-RX/2,RY/2, 0.0f);//初始化位置
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);
		for(i=0; i<=360; i++){
			glVertex2f(dx*cos(2*Pi/n*i), dy*sin(2*Pi/n*i));
		}

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		for(i=0; i<=360; i++){
			glVertex2f(ddx*cos(2*Pi/n*i), ddy*sin(2*Pi/n*i));
		}
		glEnd();

		glFlush();
	}
 	void OnDirection(int key, int x, int y) {//特殊按键
 		if(win==0){
			switch(key){
				case GLUT_KEY_UP:if (S1.head->Dir != 1 && S1.head->next->Dir == S1.head->Dir) {S1.head->Dir = 0;}
					break;
 				case GLUT_KEY_DOWN:if (S1.head->Dir != 0 && S1.head->next->Dir == S1.head->Dir) { S1.head->Dir = 1;}
 					break;
 				case GLUT_KEY_LEFT: if (S1.head->Dir != 3 && S1.head->next->Dir == S1.head->Dir){ S1.head->Dir = 2;}
					break;
				case GLUT_KEY_RIGHT:if (S1.head->Dir != 2 && S1.head->next->Dir == S1.head->Dir){S1.head->Dir = 3;}
					break;
				}
			}else{

				switch(key){
				case GLUT_KEY_UP:
						if(mouse==1){
							mouse=2;
						}else{
							mouse=1;
						}
					break;
 				case GLUT_KEY_DOWN:
 						if(mouse==1){
							mouse=2;
						}else{
							mouse=1;
						}
 					break;
 				case GLUT_KEY_LEFT:
 					if(mouse==1){
 						if(modes=="Console Game"){
 							modes="  LAN Game";
 							mode=2;
 							numbers="Create game";
 							number=1;
 						}else{
 							modes="Console Game";
 							mode=1;
 							numbers="    Player 1";
 							number=1;
 						}
 					}else{
 						if(mode==1){
							if(numbers=="    Player 1"){
 								numbers="    Player 2";
 								number=2;
 							}else{
 								numbers="    Player 1";
 								number=1;
 							}
 						}else{
 							if(numbers=="Create game"){
 								numbers=" Join game";
 								number=2;
 							}else{
 								numbers="Create game";
 								number=1;
 							}
 							}
 						}
					break;
				case GLUT_KEY_RIGHT:
 					if(mouse==1){
 						if(modes=="Console Game"){
 							modes="  LAN Game";
 							mode=2;
 							numbers="Create game";
 							number=1;
 						}else{
 							modes="Console Game";
 							mode=1;
 							numbers="    Player 1";
 							number=1;
 						}
 					}else{
 						if(mode==1){
							if(numbers=="    Player 1"){
 								numbers="    Player 2";
 								number=2;
 							}else{
 								numbers="    Player 1";
 								number=1;
 							}
 						}else{
 							if(numbers=="Create game"){
 								numbers=" Join game";
 								number=2;
 							}else{
 								numbers="Create game";
 								number=1;
 							}
 							}
 						}
					break;
				}

			}
	}

   	void die(){//判断死亡
		if(mode==1){
			if(number==1){
				for(snake_node *node=S1.head->next;node!=NULL;node=node->next){
					if(S1.head->X==node->X&&S1.head->Y==node->Y){
						finish=1;					
					}else if((S1.head->X==29 && S1.head->Dir==3)or(S1.head->X==0 && S1.head->Dir==2)or(S1.head->Y==0 && S1.head->Dir==1)or(S1.head->Y==29 && S1.head->Dir==0)){
						finish=1;
					}
				}
			}else{
				if(S1.head->X==S2.head->X&&S1.head->Y==S2.head->Y){
					finish=2;
				}
				for(snake_node *node=S1.head->next;node!=NULL;node=node->next){
					if(S2.head->X==node->X&&S2.head->Y==node->Y){
						finish=3;
					}
				}
				for(snake_node *node=S2.head->next;node!=NULL;node=node->next){
					if(S1.head->X==node->X&&S1.head->Y==node->Y){
						finish=4;
					}
				}
			}
		}else{
				if(S1.head->X==S2.head->X&&S1.head->Y==S2.head->Y){
					finish=2;
				}
				for(snake_node *node=S1.head->next;node!=NULL;node=node->next){
					if(S2.head->X==node->X&&S2.head->Y==node->Y){
						finish=3;
					}
				}
				for(snake_node *node=S2.head->next;node!=NULL;node=node->next){
					if(S1.head->X==node->X&&S1.head->Y==node->Y){
						finish=4;
					}
				}
		
		}
	}
	/*
	定时器响应函数
	*/
	 void OnTimer(int value) {
	 if(pause==1){
	  die();
	  if(finish==0){
              old1_num = read_num();
              old2_num = read_num();
              old3_num = read_num();
        if(mode==1){
	 	if(number==1){
	 		S1.Snak_move();
	 		if(food.arr[S1.head->X][S1.head->Y]==1){
	 			S1.game_score=S1.game_score+350-timebase+100;
	 			food.food_old++;
	 			if(food.food_old%10==0&& timebase!=75){
	 				timebase=timebase-25;
	 			}
	 			food.arr[S1.head->X][S1.head->Y]=0;
	 			food.Onfood(S1,1);
	 			S1.snak_add();
	 		}
	 	}
		if(number==2){
			S1.Snak_move();
			S2.Snak_move();
		 	if(food.arr[S1.head->X][S1.head->Y]==1){
		 		S1.game_score=S1.game_score+350-timebase+100;
		 		food.food_old++;
		 		if(food.food_old%10==0 && timebase!=75){
	 				timebase=timebase-25;
	 			}
		 		food.arr[S1.head->X][S1.head->Y]=0;
	 			food.Onfood(S1,S2,1);
	 			S1.snak_add();
		 	}
		 	 if(food.arr[S2.head->X][S2.head->Y]==1){
		 	 	S2.game_score=S2.game_score+350-timebase+100;
		 		food.food_old++;
		 		if(food.food_old%10==0 && timebase!=75){
	 				timebase=timebase-25;
	 			}
	 			food.arr[S2.head->X][S2.head->Y]=0;
	 			food.Onfood(S1,S2,1);
	 			S2.snak_add();

	 		}
		}
       }else{
             if(number==1){
            	  	S2.Snak_move();
            	  	if(food.arr[S2.head->X][S2.head->Y]==1){
			 			S2.game_score=S2.game_score+350-timebase+100;
		 			food.food_old++;
		 			if(food.food_old%10==0 && timebase!=75){
	 					timebase=timebase-25;
	 				}
		 			food.arr[S2.head->X][S2.head->Y]=0;
	 				food.Onfood(S1,S2,1);
	 				S2.snak_add();
		 		}
				//联网
				sendToInter();//与服务器交换信息
				
              }else{
              	
              	S1.Snak_move();
                if(food.arr[S1.head->X][S1.head->Y]==1){
		 	 		S1.game_score=S1.game_score+350-timebase+100;
		 		food.food_old++;
		 		if(food.food_old%10==0 && timebase!=75){
	 				timebase=timebase-25;
	 			}
	 			
	 			S1.snak_add();
	 			}
	 			sendToInteri();
	 			food.arr[S1.head->X][S1.head->Y]=0;
              }
              
     		 }
    	  }
 		}
 		if(win==0){
			glutTimerFunc(timebase,OnTimer,finish);
		}
}
	void draw_start(){//绘图开始
	    map_init();
	    
	    if(mode==1){
		snake_node *node = S2.tail;
		switch(number){
		    case 2:
				while(node != S2.head){
					snak_body(node->X,node->Y,node->Dir,node->rgb);
 					node = node->prev;
 				}
				snak_head(node->X,node->Y,node->Dir,node->rgb);
		    case 1:
                node = S1.tail;
				while(node != S1.head){
					snak_body(node->X,node->Y,node->Dir,node->rgb);
 					node = node->prev;
 				}
				snak_head(node->X,node->Y,node->Dir,node->rgb);
			}
			glLoadIdentity();// 复位
			glRectf(11*RX1, -1.0f,1.0f, 1.0f);

            }else{
                snake_node *node = S2.tail;
                while(node != S2.head){
                        snak_body(node->X,node->Y,node->Dir,node->rgb);
                        node = node->prev;
                }
                snak_head(node->X,node->Y,node->Dir,node->rgb);
                node = S1.tail;
                while(node != S1.head){
                        snak_body(node->X,node->Y,node->Dir,node->rgb);
                        node = node->prev;
                }
                snak_head(node->X,node->Y,node->Dir,node->rgb);
                glLoadIdentity();// 复位
                glRectf(11*RX1, -1.0f,1.0f, 1.0f);
            }
            char g_num[10];
            if( mode==2){
                map_font(10,4,"RED_Score",RGB(1.0f,0.0f,0.0f));
                sprintf(g_num,"%d",S2.game_score);
                map_font(11,3,g_num,RGB(0.0f,1.0f,0.0f));
                map_font(10,1,"RED_LV.",RGB(1.0f,0.0f,0.0f));
                sprintf(g_num,"%d",food.food_old/10);
                map_font(11,0,g_num,RGB(0.0f,1.0f,0.0f));
                sprintf(g_num,"%d",old3_num);
            }
            if(mode == 1 && number == 2){
                map_font(10,4,"RED_Score",RGB(1.0f,0.0f,0.0f));
                sprintf(g_num,"%d",S2.game_score);
                map_font(11,3,g_num,RGB(0.0f,1.0f,0.0f));
                map_font(10,1,"RED_LV.",RGB(1.0f,0.0f,0.0f));
                sprintf(g_num,"%d",food.food_old/10);
                map_font(11,0,g_num,RGB(0.0f,1.0f,0.0f));
                sprintf(g_num,"%d",old2_num);
            }
            if(mode == 1 && number == 1){

                sprintf(g_num,"%d",old1_num);
            }
            map_font(10,13,"History_Num",RGB(1.0f,0.5f,0.0f));
            map_font(11,12,g_num,RGB(0.0f,1.0f,0.0f));

            map_font(10,10,"PINK_Score",RGB(1.0f,0.0f,1.0f));
            sprintf(g_num,"%d",S1.game_score);
            map_font(11,9,g_num,RGB(0.0f,1.0f,0.0f));

            map_font(10,7,"PINK_LV.",RGB(1.0f,0.0f,1.0f));
            sprintf(g_num,"%d",food.food_old/10);
            map_font(11,6,g_num,RGB(0.0f,1.0f,0.0f));
            onfood();
                                if(finish==1){
                                        write_num();
                                        map_font(-5,1,"Game Over",RGB());
                                        map_font(-7,-1,"Press 'Enter' To Menu !",RGB());
                                }else if(finish==2){
                                        write_num();
                                        map_font(-5,1,"Play Even",RGB());
                                        map_font(-7,-1,"Press 'Enter' To Menu !",RGB());
                                }else if(finish==3){
                                        write_num();
                                        map_font(-5,1,"Play1 Win",RGB());
                                        map_font(-7,-1,"Press 'Enter' To Menu !",RGB());
                                }else if(finish==4){
                                        write_num();
                                        map_font(-5,1,"Play2 Win",RGB());
                                        map_font(-7,-1,"Press 'Enter' To Menu !",RGB());
                                }
                                if(pause==0){map_font(-4,1,"PAUSE !!!",RGB(0.0f,1.0f,0.0f));}


            draw_end();
	}
	void setinit(int window){//初始化变量
		win=window;
		//mode=x;
    	//number=y;
    	string modes="Console Game";
    	string numbers="    Player 1";
    	finish=0;
		timebase=350;
		//food=snake_food;
		S2.Snak_init(RGB(1.0f,0.0f,0.0f));
		S1.Snak_init(RGB(1.0f,0.0f,1.0f),21,7);
		food.snake_init();
	}
	void map_font(int x,int y,string ch,const RGB &RG){//绘制英文 xy坐标 ch字符串 RGB颜色
		static double unit_x = 2.0f/30;
 		static double unit_y = 2.0f/30;
		int i=0;
 		glLoadIdentity();				// 复位
		glColor3f(RG.R,RG.G,RG.B);
		glRasterPos3f(x*unit_x,y*unit_y,0.0);
		for(i=0;i<ch.size();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,ch[i]);
		}
	}

	void _map_init(){//主菜单初始化
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.4f,0.5f,0.4f,0.0f);
		//map_font(-6,6,"Snake Game",RGB());
		map_font(-6,0,"Snake League",RGB());
		if(mouse==1){
			map_font(-6,-5,modes,RGB(1.0f,0.0f,1.0f));
			map_font(-6,-9,numbers,RGB(0.0f,1.0f,1.0f));

		}else{
			map_font(-6,-5,modes,RGB(0.0f,1.0f,1.0f));
			map_font(-6,-9,numbers,RGB(1.0f,0.0f,1.0f));
		}
 		glutSwapBuffers();//显示
	}
 	void keyPressed(unsigned char key, int x, int y) {//普通按键
 	if(win==0){
		switch(key){
				case 119:if (S2.head->Dir != 1 && S2.head->next->Dir == S2.head->Dir) {S2.head->Dir = 0;}
					break;
 				case 115:if (S2.head->Dir != 0 && S2.head->next->Dir == S2.head->Dir) { S2.head->Dir = 1;}
 					break;
 				case 97: if (S2.head->Dir != 3 && S2.head->next->Dir == S2.head->Dir){ S2.head->Dir = 2;}
					break;
				case 100:if (S2.head->Dir != 2 && S2.head->next->Dir == S2.head->Dir){S2.head->Dir = 3;}
					break;
				case 87:if (S2.head->Dir != 1 && S2.head->next->Dir == S2.head->Dir) {S2.head->Dir = 0;}
					break;
 				case 83:if (S2.head->Dir != 0 && S2.head->next->Dir == S2.head->Dir) { S2.head->Dir = 1;}
 					break;
 				case 65: if (S2.head->Dir != 3 && S2.head->next->Dir == S2.head->Dir){ S2.head->Dir = 2;}
					break;
				case 68:if (S2.head->Dir != 2 && S2.head->next->Dir == S2.head->Dir){S2.head->Dir = 3;}
					break;
				case 13:
					if(finish!=0){
						glutDestroyWindow(window_game);
						menu_init();
					}
				}
			
		}else{
			switch(key){
				case 13:
					glutDestroyWindow(win);
						if(mode==2){
							s_fd=socket(AF_INET,SOCK_STREAM,0);//联网sock创建
	 						if(s_fd==-1){
								perror("socket");
								return;
	 						}
	 						ser.sin_family=AF_INET;
	 						ser.sin_port=htons(6666);
	 						inet_pton(AF_INET,IPADDREES,&ser.sin_addr);
	 						int c=connect(s_fd,(struct sockaddr *)&ser,sizeof(ser));
	 						if(c==-1){
								perror("connect");
								return;
						 	}
						 }
						 	//创建结束
					//glutHideWindow();
					glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    				glutInitWindowSize(760,600);
    				glutInitWindowPosition(100, 100);
    				window_game=glutCreateWindow("Snake");
    				win=0;
    				Draw::foodinit();
    				glutDisplayFunc(&draw_start);
    				glutIdleFunc(&draw_start);
    				glutKeyboardFunc(&keyPressed);
    				glutSpecialFunc(&OnDirection);
    				glutTimerFunc(350, &OnTimer,0);
    				glutMainLoop();

			}
		}

 	if (key == 27) {
		exit(0);
	 }
	if(mode==1&&key==32){
		pause==1?pause=0:pause=1;
	}
	
	}

	void menu_init(){//主菜单绘图
		
		
	 	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
 		glutInitWindowSize(300, 300);
 		glutInitWindowPosition(300, 200);//窗口起始位置
    	int window=glutCreateWindow("Snake Game");
    	Draw::setinit(window);
    	glutDisplayFunc(&_map_init);
		glutIdleFunc(&_map_init);
		glutKeyboardFunc(&keyPressed);
		glutSpecialFunc(&OnDirection);
 		glutMainLoop();
	}

        void write_num(){//写最高分
            //ofstream fs("history",ios::out|ios::binary);
            if(mode == 1 && number ==1){
                                old1_num = read_num();
                ofstream efs("history1",ios::out|ios::binary);
                if(efs){
                        if(S1.game_score > old1_num){
                            old1_num = S1.game_score;
                        }
                        if(old1_num >= S1.game_score){
                               old1_num = old1_num;
                        }
                        efs.write((char *)&old1_num,sizeof(old1_num));
                }
            }

            if(mode == 1 && number == 2){
                                old2_num = read_num();
                ofstream rfs("history2",ios::out|ios::binary);
                if(rfs){
                    if(S1.game_score > S2.game_score && S1.game_score > old2_num){
                        old2_num = S1.game_score;
                    }if(S2.game_score > S1.game_score && S2.game_score > old2_num){
                        old2_num = S2.game_score;
                    }if(old2_num >= S1.game_score && old2_num >= S2.game_score){

                        old2_num = old2_num;
                    }
                    rfs.write((char *)&old2_num,sizeof(old2_num));

                }
            }
            if(mode == 2){
                                old3_num = read_num();
                ofstream lfs("history3",ios::out);
                if(lfs){
                    if(S1.game_score > S2.game_score && S1.game_score > old2_num){
                        old3_num = S1.game_score;
                    }if(S2.game_score > S1.game_score && S2.game_score > old2_num){
                        old3_num = S2.game_score;
                    }if(old3_num >= S1.game_score && old2_num >= S2.game_score){

                        old3_num = old3_num;
                    }
                    lfs.write((char *)&old3_num,sizeof(old3_num));
                }
            }

        }

        int read_num(){//读最高分
            int num;
            if(mode == 1 && number == 1){
                ifstream efs("history1",ios::in|ios::binary);
                if(efs){
                    efs.read((char *)&old1_num,sizeof(old1_num));
                    num = old1_num;
                }
                else{
                    num = 0;
                }
            }

            if(mode == 1 && number == 2){
                ifstream rfs("history2",ios::in|ios::binary);
                if(rfs){
                    rfs.read((char *)&old2_num,sizeof(old2_num));
                    num = old2_num;
                }else{
                    num = 0;
                }
            }
            if(mode == 2){
                ifstream lfs("history3",ios::in|ios::binary);
                if(lfs){
                    lfs.read((char *)&old3_num,sizeof(old3_num));
                   num = old3_num;
                }else{
                    num = 0;
                }
            }

            return num;
        }

void sendToInter(){//房间与服务器端交换信息
	snake_node *node=S2.head;//？
	for(int i=0;node!=NULL;i++){
		arr1[i][0]=node->X;
		arr1[i][1]=node->Y;
		arr1[i][2]=node->Dir;
		node=node->next;
	}
	int temp=100;
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			if(food.arr[i][j]==1){
				arr1[temp][0]=i;
				arr1[temp][1]=j;
				temp++;
			}
		}
	}
	arr1[99][0]=S2.num;//蛇的节点个数  ?

	write(s_fd,arr1,1320);
	read(s_fd,arr2,1320);
	
	node=S1.head;
	for(int i=0;node;i++){
		node->X=arr2[i][0];
		node->Y=arr2[i][1];
		node->Dir=arr2[i][2];
		node=node->next;
	}
	
	if(food.arr[S1.head->X][S1.head->Y]==1){
		S1.game_score=S1.game_score+350-timebase+100;
		food.food_old++;
		if(food.food_old%10==0 && timebase!=75){
	 		timebase=timebase-25;
		}
		food.arr[S1.head->X][S1.head->Y]=0;
		//arr1[99][1]=S1.head->X;
		//arr1[99][2]=S1.head->Y;
		food.Onfood(S1,S2,1);
		S1.snak_add();
	}	


}

void sendToInteri(){//加入房间与服务器端交换信息
	snake_node *node=S1.head;//？
	for(int i=0;node!=NULL;i++){
		arr1[i][0]=node->X;
		arr1[i][1]=node->Y;
		arr1[i][2]=node->Dir;
		node=node->next;
	}

	arr1[99][0]=S1.num;//蛇的节点个数  ?

	write(s_fd,arr1,1320);
	read(s_fd,arr2,1320);
	
	node=S2.head;
	for(int i=0;node;i++){
		node->X=arr2[i][0];
		node->Y=arr2[i][1];
		node->Dir=arr2[i][2];
		node=node->next;
	}
	
	int temp=100;
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			if(food.arr[i][j]==1){
				arr1[temp][0]=i;
				arr1[temp][1]=j;
				temp++;
			}
		}
	}
	
	for(int i=0;i<10;i++){
			food.arr[arr2[100+i][0]][arr2[100+i][1]]=1;
	}
	
	//food.arr[arr2[99][1]][arr2[99][2]]=0;

	if(food.arr[S2.head->X][S2.head->Y]==1){
	S2.game_score=S2.game_score+350-timebase+100;
	food.food_old++;
	if(food.food_old%10==0 && timebase!=75){
	 	timebase=timebase-25;
	}
	food.arr[S2.head->X][S2.head->Y]=0;
	S2.snak_add();
	}	


}
//-------------------------------------------------

}






int main(int argc, char **argv){
	srand(time(0));
    glutInit(&argc,argv);
	Draw::menu_init();
	

	//close(s_fd);//关闭联网服务

    return 0;
}
