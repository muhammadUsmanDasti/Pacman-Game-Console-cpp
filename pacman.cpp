#include<iostream>
#include<windows.h>
#include<fstream>
using namespace std;
void printMaze();
void moveUp();
void moveDown();
void moveRight();
void moveLeft();
void printScore();
void printLives();
void horizontalGhost();
void verticalGhost();
void gotoxy(int x,int y);
void livesUpdate();
void randomGhost();
void chasingGhost();
void loadMaze();
void lose();
void win();
void setColor(int colorCode);
void hideCursor();


char maze[24][71];
int pacmanX=4;
int pacmanY=5;
int score=0;
int lives=3;

int horiGhostX = 13;
int horiGhostY = 7;
int horiGhostDirection = 1;
char preserveUnderHoriGhost=' ';

int vertGhostX = 2;
int vertGhostY = 51;
int vertGhostDirection = 1;
char preserveUnderVertGhost=' ';

int randGhostX=13;
int randGhostY=37;
char preserveUnderRandGhost=' ';

int chasingGhostX=14;
int chasingGhostY=7;
char preserveUnderChasingGhost=' ';

bool superPower=false;
void powerEnergizer();
int altration=0;

int main(){
    hideCursor();
    bool gameRunning = true;
    loadMaze();
    system("cls");
    printMaze();
    gotoxy(pacmanY,pacmanX);
    setColor(10);
    cout<<"P";
    setColor(7);
        
    while(gameRunning&&score<=465&&lives>0){
        Sleep(100);
        printScore();

        if(GetAsyncKeyState(VK_UP)){
            moveUp();
        }
        if(GetAsyncKeyState(VK_DOWN)){
            moveDown();
        }
        if(GetAsyncKeyState(VK_LEFT)){
            moveLeft();
        }
        if(GetAsyncKeyState(VK_RIGHT)){
            moveRight();
        }
        if(GetAsyncKeyState(VK_ESCAPE)){
            gameRunning=false;
        }
        powerEnergizer();
        livesUpdate();
        horizontalGhost();
        verticalGhost();
        randomGhost();
        chasingGhost();
        livesUpdate();

        printLives();
    }
    if(score==466){
        system("cls");
        gotoxy(5,5);
        win();
    }
    else{
        system("cls");
        gotoxy(5,5);
        lose();
    }
    return 0;
}
void printMaze(){
    for(int x=0;x<24;x++){
        for(int y=0;y<71;y++){
            if(maze[x][y]=='#'||maze[x][y]=='%'||maze[x][y]=='|'){
                setColor(1);
                cout<<maze[x][y];
                setColor(7);
            }
            else if(maze[x][y]=='*'){
                setColor(14);
                cout<<maze[x][y];
                setColor(7);
            }
            else if(maze[x][y]=='.'){
                setColor(15);
                cout<<maze[x][y];
                setColor(7);
            }
            else{
                cout<<maze[x][y];
            }
            
        }
        cout<<endl;
    }
}
void moveUp(){
    if(maze[pacmanX-1][pacmanY]==' '||maze[pacmanX-1][pacmanY]=='.'||maze[pacmanX-1][pacmanY]=='*'){
        gotoxy(pacmanY,pacmanX);
        cout<<" ";
        pacmanX--;
        gotoxy(pacmanY,pacmanX);
        setColor(10);
        cout<<"P";
        setColor(7);
        if(maze[pacmanX][pacmanY]=='.'){
            maze[pacmanX][pacmanY]=' ';
            score++;
        }
    }
    
}
void moveDown(){
    if(maze[pacmanX+1][pacmanY]==' '||maze[pacmanX+1][pacmanY]=='.'||maze[pacmanX+1][pacmanY]=='*'){
        gotoxy(pacmanY,pacmanX);
        cout<<" ";
        pacmanX++;
        gotoxy(pacmanY,pacmanX);
        setColor(10);
        cout<<"P";
        setColor(7);
        if(maze[pacmanX][pacmanY]=='.'){
            maze[pacmanX][pacmanY]=' ';
            score++;
        }
    }
}
void moveLeft(){
    if(maze[pacmanX][pacmanY-1]==' '||maze[pacmanX][pacmanY-1]=='.'||maze[pacmanX][pacmanY-1]=='*'){
        gotoxy(pacmanY,pacmanX);
        cout<<" ";
        pacmanY--;
        gotoxy(pacmanY,pacmanX);
        setColor(10);
        cout<<"P";
        setColor(7);
        if(maze[pacmanX][pacmanY]=='.'){
            maze[pacmanX][pacmanY]=' ';
            score++;
        }
    }
}
void moveRight(){
    if(maze[pacmanX][pacmanY+1]==' '||maze[pacmanX][pacmanY+1]=='.'||maze[pacmanX][pacmanY+1]=='*'){
        gotoxy(pacmanY,pacmanX);
        cout<<" ";
        pacmanY++;
        gotoxy(pacmanY,pacmanX);
        setColor(10);
        cout<<"P";
        setColor(7);
        if(maze[pacmanX][pacmanY]=='.'){
            maze[pacmanX][pacmanY]=' ';
            score++;
        }
    }
}
void printScore(){
    gotoxy(73,1);
    setColor(5);
    cout<<"Score: "<<score;
    setColor(7);
}
void printLives(){
    gotoxy(73,2);
    setColor(5);
    cout<<"Lives: "<<lives;
    setColor(7);
}
void gotoxy(int x, int y){
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
void horizontalGhost(){
    if(maze[horiGhostX][horiGhostY+horiGhostDirection]==' '||maze[horiGhostX][horiGhostY+horiGhostDirection]=='.'){
    gotoxy(horiGhostY,horiGhostX);
    cout<<preserveUnderHoriGhost;
    horiGhostY+=horiGhostDirection;
    preserveUnderHoriGhost=maze[horiGhostX][horiGhostY];
    gotoxy(horiGhostY,horiGhostX);
    setColor(12);
    cout<<"G";
    setColor(7);

    }
    else{
        horiGhostDirection=horiGhostDirection*-1;
    }
    
}
void verticalGhost(){
    if(maze[vertGhostX+vertGhostDirection][vertGhostY]==' '||maze[vertGhostX+vertGhostDirection][vertGhostY]=='.'){
    gotoxy(vertGhostY,vertGhostX);
    cout<<preserveUnderVertGhost;
    vertGhostX+=vertGhostDirection;
    preserveUnderVertGhost=maze[vertGhostX][vertGhostY];
    gotoxy(vertGhostY,vertGhostX);
    setColor(12);
    cout<<"G";
    setColor(7);
    }
    else{
        vertGhostDirection=vertGhostDirection*-1;
    }
}
void randomGhost(){
    static int stepCounter=0;
    stepCounter++;
    gotoxy(randGhostY,randGhostX);
    cout<<preserveUnderRandGhost;
    int dx[4]={0,-1,0,1};    //right,up,left,down
    int dy[4]={1,0,-1,0};
    int random=(stepCounter+score+lives+randGhostX+randGhostY+pacmanX+pacmanY)%4;
    for(int i=0;i<4;i++){
        int dir=(random+i)%4;
        int newX=randGhostX+dx[dir];
        int newY=randGhostY+dy[dir];
        if(maze[newX][newY]==' '||maze[newX][newY]=='.'){
            randGhostX=newX;
            randGhostY=newY;
            preserveUnderRandGhost=maze[randGhostX][randGhostY];
            break;
        }
        
    }
    gotoxy(randGhostY,randGhostX);
    setColor(12);
    cout<<"G";
    setColor(7);


}
void chasingGhost(){
    gotoxy(chasingGhostY,chasingGhostX);
    cout<<preserveUnderChasingGhost;
    int dx=0;
    int dy=0;
    if(pacmanX>chasingGhostX){
        dx=1;
    }
    else if(pacmanX<chasingGhostX){
        dx=-1;
    }
    if(pacmanY>chasingGhostY){
        dy=1;
    }
    else if(pacmanY<chasingGhostY){
        dy=-1;
    }
    if((maze[chasingGhostX+dx][chasingGhostY]==' '||maze[chasingGhostX+dx][chasingGhostY]=='.')&&dx!=0){
        chasingGhostX+=dx;
    }
    else if((maze[chasingGhostX][chasingGhostY+dy]==' '||maze[chasingGhostX][chasingGhostY+dy]=='.')&&dy!=0){
        chasingGhostY+=dy;
    }
    preserveUnderChasingGhost=maze[chasingGhostX][chasingGhostY];
    gotoxy(chasingGhostY,chasingGhostX);
    setColor(14);
    cout<<"G";
    setColor(7);
    Sleep(50);
}
void livesUpdate(){
    if(pacmanX==horiGhostX&&pacmanY==horiGhostY){
        if(superPower){
            horiGhostX=13;
            horiGhostY=7;
        }
        else{
            lives--;
            gotoxy(pacmanY,pacmanX);
            cout<<" ";
            pacmanX=4;
            pacmanY=5;
            gotoxy(pacmanY,pacmanX);
            setColor(10);
            cout<<"P";
            setColor(7);
            horiGhostX = 13;
            horiGhostY = 7;
        }
    }
    if(pacmanX==vertGhostX&&pacmanY==vertGhostY){
        if(superPower){
            vertGhostX = 1;
            vertGhostY = 51;

        }
        else{
            lives--;
            gotoxy(pacmanY,pacmanX);
            cout<<" ";
            pacmanX=4;
            pacmanY=5;
            gotoxy(pacmanY,pacmanX);
            setColor(10);
            cout<<"P";
            setColor(7);
            vertGhostX = 1;
            vertGhostY = 51;
        }
    }
    if(pacmanX==randGhostX&&pacmanY==randGhostY){
        if(superPower){
            randGhostX=13;
            randGhostY=37;
        }
        else{
            lives--;
            gotoxy(pacmanY,pacmanX);
            cout<<" ";
            pacmanX=4;
            pacmanY=5;
            gotoxy(pacmanY,pacmanX);
            setColor(10);
            cout<<"P";
            setColor(7);
            randGhostX=13;
            randGhostY=37;
        }

    }
    if(pacmanX==chasingGhostX&&pacmanY==chasingGhostY){
        if(superPower){
            chasingGhostX=14;
            chasingGhostY=7;
        }
        else{
            lives--;
            gotoxy(pacmanY,pacmanX);
            cout<<" ";
            pacmanX=4;
            pacmanY=5;
            gotoxy(pacmanY,pacmanX);
            setColor(10);
            cout<<"P";
            setColor(7);
            chasingGhostX=14;
            chasingGhostY=7;
        }
    }
}

void loadMaze(){
    fstream newfile;
    newfile.open("maze.txt",ios::in);
    if(!newfile.is_open()){
        cout<<"File not found";
        exit(1);
    }
    string line;
    int row=0;
    while(getline(newfile,line)&&row<24){
        for(int col=0;col<71;col++){
            maze[row][col]=line[col];
        }
        row++;
    }
    newfile.close();

}
void powerEnergizer(){
    if(maze[pacmanX][pacmanY]=='*'){
        maze[pacmanX][pacmanY]=' ';
        superPower=true;
        altration=30;
    }
    if(superPower){
        gotoxy(73,3);
        setColor(14);
        cout<<"SUPERPOWER: "<<altration;
        setColor(7);
        altration--;
        if(altration<0){
            superPower=false;
            gotoxy(73,3);
            cout<<"                       ";
        }
    }
}
void setColor(int colorCode){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,colorCode);
}
void hideCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;  // Set cursor visibility to false
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}


void lose(){
    setColor(12);
    cout << R"(
       _____          __  __ ______    ______      ________ _____
      / ____|   /\   |  \/  |  ____|  / __ \ \    / /  ____|  __ \
     | |  __   /  \  | \  / | |__    | |  | \ \  / /| |__  | |__) |
     | | |_ | / /\ \ | |\/| |  __|   | |  | |\ \/ / |  __| |  _  /
     | |__| |/ ____ \| |  | | |____  | |__| | \  /  | |____| | \ \
      \_____/_/    \_\_|  |_|______|  \____/   \/   |______|_|  \_\
                                                               
                               YOU LOSE
)" << endl;
setColor(7);
}
void win(){
    setColor(10);
     cout << R"(
__     ______  _    _      __        __ ___ _   _ 
\ \   / / __ \| |  | |     \ \      / /|_ _| \ | |
 \ \_/ / |  | | |  | |      \ \ /\ / /  | ||  \| |
  \   /| |  | | |  | |       \ V  V /   | || |\  |
   |_|  \____/ \____/         \_/\_/   |___|_| \_|
                                                 
 
)" << endl;
setColor(7);
}