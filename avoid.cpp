#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <windows.h>
using namespace std;
//global variables
int locx=25,locy=12;
int sensors[4];
string labels[4]={"North","West","South","East"};//labels
//functions headers
string getPos(){//funtion to get the compass position
    int x=locx*2;//scale
    int y=locy*4 ;
    string pos="\033[1;33m";//to display direction in custom color and boldness
    //set appropriate direction according to location
    if(y>50){//for south
        pos+="South ";
    }
    else if (y<50){//for north
        pos+="North ";
    }

    if(x>50){//for east add on
        pos+="East";
    }
    else if (x<50){//for west add on
        pos+="West";
    }
    else if(x==50){//for either just south or ust north
        pos+="";
    }
    pos+="\033[0;0m";//color back to normal
    return pos;
}
void scp(int x, int y)//function to set cursor to the position entered
{
    x++;//increment both co-ordinated to respect boundries of box
    y++;
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void getSensors(){//function to get sensor readings 
        sensors[0]=rand()%24+1;//get random sensor readin to go to
        sensors[1]=rand()%49+1;//sensor readings are scaled for dislay
        sensors[2]=25-sensors[0];//to make sure the sensor readings accurately fit the box space
        sensors[3]=50-sensors[1];
}
void draw(){//function to draw box space
    system("cls");
    for(int k=0;k<26;k++){//loop for dsiplaying top line
            cout<<"--";
        }
        cout<<endl;
        for(int i=0;i<25;i++){
            cout<<"|";//print start barrier
            for(int j=0;j<50;j++){
                cout<<" ";
            }
            cout<<"|\n";//print end barrier
        }
        for(int k=0;k<26;k++){//loop for dsiplaying bbottom line
            cout<<"--";
        }
}
void update(){//function to update sensor readings, positon and timer to screen
    scp(52,0);//sensor readings
    cout<<labels[0]<<" : "<<sensors[0]*4<<endl;
    scp(52,1);
    cout<<labels[1]<<" : "<<sensors[1]*2<<endl;;
    scp(52,2);
    cout<<labels[2]<<" : "<<100-sensors[0]*4<<endl;;
    scp(52,3);
    cout<<labels[3]<<" : "<<100-sensors[1]*2<<endl;;
    scp(52,5);//compassposition
    cout<<"Position : "<<getPos();
    scp(52,6);//timer
    cout<<"Update in : Updating...";
    for(int i=0;i<11;i++){
        cout<<"\b";
    }
    for(int i=0;i<11;i++){
        cout<<" ";
    }
    for(int i=0;i<11;i++){
        cout<<"\b";
    }
    for(int i=5;i>0;i--){ 
        cout<<"\033[1;32m"<<i<<"   ";
        Sleep(1000);
        cout<<"\b\b\b\b";
    }
    cout<<"Updating...\033[0;0m";
}
void place(string s){//function to go to a location and place character/string
    scp(locx,locy);
    cout<<s;
}
void move(){//function to move the character in x and y direction
     while(sensors[1]!=locx){//for x
         place(" ");//empty the prev spot
         locx=(sensors[1]>locx?locx+1:locx-1);//new spot as relevent to next location
         place("*");//move to new spot 
         Sleep(100);//delay for display
     }
     while(sensors[0]!=locy){//for y 
         place(" ");
         locy=(sensors[0]>locy?locy+1:locy-1);
         place("*");
         Sleep(150);//highier delay
    }
}

//main function
int main() {
    srand( time( 0 ));// initialize the random number generator
    draw();//draw the box
    while(true){ // simulate moves by the robot
        getSensors();// get values for all the sensors
        move();//move the robot around the box
        update();//update the position of robot
    }
} // end of main()
