#include <iostream>
#include <limits.h>
#include<string>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<time.h>
#include<windows.h>
using namespace std;
const int V=58; //Currently function stations as number of nodes
struct station_code
{
    string name;
    int code;
    string color;
};
struct station_code station[V];
float djk_graph[V][V];

struct node1
{
    vector<float> p;
} P[V];

void drawbox(int, int, int, int, int);
void screen();
void clrscreen();
void delay(unsigned int ms);
void postition_x_y(int x,int y);
int timetaken(float dist);
int fare(float dist);

void Path(float dist,int e,int st,int inter);
int minDistance(float dist[], bool sptSet[]);
void dijkstra(float djk_graph[V][V], int src,int dest);
void printSolution(float dist[], int n,int src,int temp);
void take_input();
void logo(int x, int y);
void screen();
void UI();

COORD coord;
void clrscreen()
{
    system("cls");
    drawbox(1,0,117,29,0);
}

//To avoid station not found error
string makecapital(string str) 
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
}

void delay(unsigned int ms)
{
    clock_t goal=ms+clock();
    while(goal>clock());
}

void postition_x_y(int x,int y)
{
  coord.X=x;
  coord.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void drawbox(int x1, int y1, int x2, int y2, int d)
{
    postition_x_y(x1,y1);
    printf("+");
    delay(d);
    postition_x_y(x2,y2);
    printf("+");
    delay(d);
    int i;
    for(i=1;i<x2-x1;i++)
    {   postition_x_y(x1+i,y1);
        printf("-");
        printf("\a");
        delay(d);
        postition_x_y(x2-i,y2);
        printf("-");
        delay(d);
    }
    postition_x_y(x1,y2);
    printf("+");
    postition_x_y(x2,y1);
    printf("+");
    int j;
    for(j=1;j<y2-y1;j++)
        {
            postition_x_y(x2,y1+j);
            printf("|");
            delay(d);
            postition_x_y(x1,y2-j);
            printf("|");
            delay(d);
        }
}

int timetaken(float dist)
{
    float speed=0.55;
    return ceil(dist/speed);
}

int fare(float dist)
{
    if(dist<=2)
        return 10;
    else if(dist>2&&dist<=5)
        return 20;
    else if(dist>5&&dist<=12)
        return 30;
    else if(dist>12&&dist<=21)
        return 40;
    else if(dist>21&&dist<=32)
        return 50;
    else
        return 60; //maximum between miyapur and nagole
}


void Path(float d,int e,int st,int inter)
{
    int t=e,s;
    static float dist=0;
    dist+=d;

    postition_x_y(16,11);
    cout<<"THE SHORTEST PATH IS : ";

    static int pos_x=12;
    static int pos_y=15;
    vector <int> path;
    path.push_back(t);
    while(t!=st)
    {
        s=P[t].p.size();
        t=P[t].p[s-1];
        path.push_back(t);
    }
    vector <int>::iterator i=path.end();
    string str;
    string color;
    if(!inter){
    postition_x_y(44,13);
    cout<<"****** LOADING ******";
    delay(2000);
    postition_x_y(42,13);
    cout<<"****** ROUTE FOUND ******";
    }
    vector<int>::iterator i2=path.end();
    i2--;
    int n_of_stations=0;
    while(i!=path.begin())
    {
        i--;
        color=station[*i].color;
        if(color=="BLUE")
            system("color 09");
        else if(color=="RED")
            system("color 04");
        else if(color=="GREEN")
            system("color 02");

        if(i!=i2)
        {
        if(station[*(i2)].color!=station[*(i)].color)
        {
            pos_x=8;
            pos_y++;
            postition_x_y(pos_x,pos_y);
            cout<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}";
            pos_x=12;
            pos_y++;
            postition_x_y(pos_x,pos_y);
        }
        i2--;
        }
        str=station[*i].name;
        if(pos_x+5+str.size()<106)
        {
            postition_x_y(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        else
        {
            pos_x=12;
            pos_y++;
            postition_x_y(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        n_of_stations++;
        delay(700);
    }
    if(!inter)
    {
      postition_x_y(12,++pos_y);
      cout<<"INTERMEDIATE STATION";
      pos_y++;
      pos_x=12;
    }

    if(inter){
    delay(1000);
    postition_x_y(72,11);
    cout<<"PATH LENGTH IS :";
    postition_x_y(97,11);
    cout<<d<<" KM";
    delay(1000);
    postition_x_y(16,10);
    cout<<"AVERAGE TIME : ";
    postition_x_y(39,10);
    cout<<timetaken(d)<<" MIN";
    delay(1000);
    postition_x_y(72,10);
    cout<<"AVERAGE FARE : ";
    postition_x_y(94,10);
    cout<<" Rs. "<<fare(d);
    delay(1000);
    postition_x_y(72,12);
    cout<<"NO OF STATIONS : ";
    postition_x_y(92,12);
    cout<<n_of_stations-1;
    }
    else{
      delay(1000);
      postition_x_y(72,11);
      cout<<"PATH LENGTH IS :";
      postition_x_y(89,11);
      cout<<d<<" KM,";
      delay(1000);
      postition_x_y(16,10);
      cout<<"AVERAGE TIME : ";
      postition_x_y(32,10);
      cout<<timetaken(d)<<" MIN,";
      delay(1000);
      postition_x_y(72,10);
      cout<<"AVERAGE FARE : Rs. ";
      postition_x_y(91,10);
      cout<<fare(d)<<",";
      delay(1000);
      postition_x_y(72,12);
      cout<<"NO OF STATIONS : ";
      postition_x_y(89,12);
      cout<<n_of_stations-1<<",";
    }

    if(inter){
    delay(2500);
    postition_x_y(44,9);
    cout<<"WANT TO SEARCH AGAIN ?  ";
    string choice;
    pos_x=12; pos_y=15;
    cin>>choice;
    choice=makecapital(choice);
    if(choice=="Y"||choice=="YES")
        screen();
    postition_x_y(5,30);
    char ch;
    scanf("%c",&ch);
    cout<<endl;
  }
  return;
}

int minDistance(float dist[], bool sptSet[])
{
   float min = INT_MAX;
   int min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}

void printPath(float dist[], int n,int src,int temp,int inter)
{
    // Details(temp);
    Path(dist[temp],temp,src,inter);
}

void dijkstra_algo(float djk_graph[V][V], int src, int dest, int inter)
{
     float dist[V];
     bool sptSet[V];
     for (int i = 0; i < V; i++){
        dist[i] = INT_MAX, sptSet[i] = false;
     }
     dist[src] = 0;
     for (int count = 0; count < V-1; count++)
     {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && djk_graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+djk_graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + djk_graph[u][v];
                P[v].p.push_back(u);
            }
        }
     }
     printPath(dist, V,src,dest, inter);
}
int lcs( string X,string Y ) 
{ 
	int m=X.length();
	int n=Y.length();
    int L[m+1][n+1]; 
    int i, j; 
   
    for (i=0; i<=m; i++) 
    { 
        for (j=0; j<=n; j++) 
        { 
            if (i == 0 || j == 0) 
                L[i][j] = 0; 
            else if (X[i-1] == Y[j-1]) 
                L[i][j] = L[i-1][j-1] + 1; 
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]); 
        } 
    } 
    return L[m][n]; 
}

int sameMatch(string s){
	int max=0,maxi=-1;
	for(int i=0;i<58;i++){
		int val=lcs(s,station[i].name);
		if(val>max){
			maxi=station[i].code;
			max=val;
		}
	}
	if(max<station[maxi].name.length()/2)
		return -1;
	return maxi;
}

void take_input()
{		
    char ch;
    //scanf("%c",&ch);
    string start_s, end_s, inter_s, line, col;
    postition_x_y(16,3);
    cout<<"ENTER THE START STATION:";
    postition_x_y(20,5);
    getline(cin, start_s);
    postition_x_y(42,6);
    cout<<"ENTER THE INTERMEDIATE STATION:";
    postition_x_y(46,8);
    getline(cin,inter_s);
    postition_x_y(72,3);
    cout<<"ENTER THE DESTINATION STATION:";
    postition_x_y(76,5);
    getline(cin,end_s);

    //for(int i=0;i<V;i++)
    //cout<<station[i].name<<" "<<station[i].code<<" "<<station[i].color<<endl;

    start_s = makecapital(start_s);
    end_s = makecapital(end_s);
    inter_s = makecapital(inter_s);

    int startcode, endcode, intercode=-1;
    int startflag=0, endflag=0, interflag1=0, interflag2=0;
    if(!(inter_s=="NO"||inter_s=="N"))
        interflag1=1;
    startcode = sameMatch(start_s);
    endcode = sameMatch(end_s);
    intercode = sameMatch(inter_s);
    if(startcode==-1)
        startflag=1;
    if(endcode==-1)
        endflag=1;
    if(endcode==-1)
        interflag2=1;
    /*for(int i=0;i<58;i++)
    {
        if(station[i].name==start_s)
        {
            startcode=station[i].code;
            startflag=1;
        }
        if(station[i].name==end_s)
        {
            endcode=station[i].code;
            endflag=1;
        }
        if(interflag1&&station[i].name==inter_s)
        {
            intercode=station[i].code;
            interflag2=1;
        }
    }*/
    int fault=0;
    if(startflag==1)
    {
        postition_x_y(42,10);
        cout<<"WRONG STARTING STATION NAME ENTERED";
        fault=1;
    }
    if(endflag==1)
    {
        postition_x_y(40,11);
        cout<<"WRONG DESTINATION STATION NAME ENTERED";
        fault=1;
    }
    if(interflag1&&interflag2==1)
    {
        postition_x_y(39,12);
        cout<<"WRONG INTERMEDIATE STATION NAME ENTERED";
        fault=1;
    }
    //ch;
    scanf("%c",&ch);    
    if(fault)
    {
        screen();
        return;
    }
    if(interflag1){
        dijkstra_algo(djk_graph,startcode,intercode,0);
        dijkstra_algo(djk_graph,intercode,endcode,1);
        }
    else
        dijkstra_algo(djk_graph, startcode,endcode,1);
}

void logo(int x, int y)
{
    postition_x_y(x,y);
    printf("                                     ");
    postition_x_y(x,y+1);
    printf(" ||    ||  ||\\\\    //||  ||   \\\\ ");
    postition_x_y(x,y+2);
    printf(" ||    ||  || \\\\  // ||  ||    || ");
    postition_x_y(x,y+3);
    printf(" ||||||||  ||  \\\\//  ||  ||___// ");
    postition_x_y(x,y+4);
    printf(" ||    ||  ||        ||  ||  \\\\   ");
    postition_x_y(x,y+5);
    printf(" ||    ||  ||        ||  ||   \\\\  ");
}

void screen()
{
    clrscreen();
    postition_x_y(48,19);
    system("color 0C");
    delay(90);
    take_input();
}

void UI(){

    system("color 0A");
    drawbox(1,0,117,29,4);
    system("color 0C");
    delay(90);
    system("color 0A");
    delay(90);
    logo(37,4);
    system("color 0C");
    delay(90);
    drawbox(30,3,87,11,4);
    drawbox(28,2,89,12,4);
    system("color 0C");
    delay(90);
    system("color 0A");
    delay(90);
    postition_x_y(42,14);
    cout<<"WELCOME TO HYDERABAD METRO DESKTOP APP";
    system("color 0C");
    delay(90);
    system("color 0D");
    delay(90);
    postition_x_y(47,18);
    printf("PRESS ENTER TO CONTINUE");
    char ch;
    scanf("%c",&ch);
    screen();
}

int main()
{
    int temp,n1,n2;
    float dis;
    ifstream fin;
    fin.open("nodes.txt");
    for(int i=0;i<58;i++)
    {
       for(int j=0;j<58;j++)
        djk_graph[i][j]=0;
    }
    for(int i=1;i<=V;i++)
    {
        fin>>temp;
        fin>>n1;
        for( int j=0;j<temp;j++)
        {
           fin>>n2;
           fin>>dis;
           //cout<<" "<<n2<<" "<<dis<<endl;
           djk_graph[n1-1][n2-1]=dis;
        }
    }
    string line,col;
    ifstream code;
    ifstream color;
    code.open("stationnames.txt");
    color.open("colorcodes.txt");
    for(int i=0;i<V;i++)
    {
        getline(code, line);
        station[i].name=line;
        station[i].code=i;
        getline(color,col);
        station[i].color=col;
    }
    //Writing the matrix
    ofstream matrix;
    matrix.open("matrix.txt");
    matrix<<"  ";
    for(int i=0;i<V;i++)
        matrix<<i<<" ";
    matrix<<endl;
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            if(j==0)
                matrix<<i<<" ";
            matrix<<djk_graph[i][j]<<" ";
        }
        matrix<<endl;
    }
    UI();
    // screen();
}