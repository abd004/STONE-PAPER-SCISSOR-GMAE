#include <bits/stdc++.h>
#include <windows.h>
#define MA7SERE ios_base::sync_with_stdio(NULL); cin.tie(0); cout.tie(0);
using namespace std;

enum enTools{Stone=1 , Paper=2 , Scissor=3};
enum enWinner{Player=1 , Computer=2 , Draw=3};

struct stRoundinfo{
    int roundnumber=0;
    enTools playerchoice;
    enTools computerchoice;
    string playertoolname;
    string computertoolname;
    enWinner winner;
    string winnername;
};
struct stgameresult{
    int gamerounds=0;
    enWinner winner;
    string winnername;
    int playerwins=0,compueterwins=0,draw=0;
};

///////////////////////functions////////////////////

int readpositivenum(){
    int num;
    do{
        cin>>num; }
    while(num<1||num>10);
    return num;
}

int randnum(int from,int to){
    int num=rand()%(to-from+1)+from;
    return num;
}

enTools getplayerchoice(){
    cout<<"\t  please choose your tool: "<<endl;
    cout<<"\t [1]stone    [2]paper    [3]scissor"<<endl;
    int choice=0;
    do{
        choice=readpositivenum();
    }while(choice<1 || choice>3);
    return enTools(choice);
}

enTools getcomputerchoice(){
    int choice= randnum(1,3);
    return  enTools(choice);
}

string toolname(enTools tool){
    string toolname[3]={"Stone","Paper","Scissor"};
    return toolname[tool-1];
}

enWinner whoiswinround(stRoundinfo roundinfo){
    if(roundinfo.playerchoice== roundinfo.computerchoice){return enWinner::Draw;}
    switch (roundinfo.playerchoice) {
        case enTools::Paper:
            if(roundinfo.computerchoice==enTools::Scissor){return enWinner::Computer;}break;
        case enTools::Scissor:
            if(roundinfo.computerchoice==enTools::Stone){return enWinner::Computer;}break;
        case enTools::Stone:
            if(roundinfo.computerchoice==enTools::Paper){return enWinner::Computer;}break;
    }
    return enWinner::Player;
}

string winnername(enWinner winner){
    string name[3]={"Player","Computer","Draw"};
    return name[winner-1];
}

void printsceencolor(enWinner winner){
    switch (winner) {
        case enWinner::Player:
            system("color 2F");
            break;
        case enWinner::Computer:
            system("color 4F");
            break;
        case enWinner::Draw:
            system("color 6F");
            break;
    }
}

void printroundresult(stRoundinfo Roundinfo){
    printsceencolor(Roundinfo.winner);
    cout<<"___________________ROUND ["<<Roundinfo.roundnumber<<"]___________________\n";
    cout<<"Player choice: "<<Roundinfo.playertoolname<<"\n";
    cout<<"Computer Choice: "<<Roundinfo.computertoolname<<"\n";
    cout<<"WINNER IS: "<<Roundinfo.winnername<<"\n";
    cout<<"_________________________________________________________________________\n";
}

enWinner whoiswingame(stgameresult gameresult){
    if(gameresult.playerwins==gameresult.compueterwins){return enWinner::Draw;}
    else{
        if(gameresult.playerwins>gameresult.compueterwins){return enWinner::Player;}
    }
    return enWinner::Computer;
}

void printgameover(){
    cout << "=========================" << endl;
    cout << "        GAME OVER        " << endl;
    cout << "=========================" << endl;
}

void resetscreen(){
    system("color 0F");
}

stgameresult fillgameresult(int rounds,int playerwins , int computerwins , int draw){
    stgameresult gameresult;
    gameresult.compueterwins=computerwins;
    gameresult.playerwins=playerwins;
    gameresult.draw=draw;
    gameresult.winner= whoiswingame(gameresult);
    gameresult.gamerounds=rounds;
    gameresult.winnername= winnername(gameresult.winner);
    return gameresult;
}

void printgameresult(stgameresult gameresult){
    printgameover();
    cout<<"ROUNDS PLAYED: "<<gameresult.gamerounds<<endl;
    cout<<"Player win times: "<<gameresult.playerwins<<endl;
    cout<<"Computer win times: "<<gameresult.compueterwins<<endl;
    cout<<"Draw times: "<<gameresult.draw<<endl;
}


stgameresult gameplay(int roundnumbers){
    int playerwins=0,computerwins=0,draw=0;
    stgameresult gameresult;
    for(int i=1 ; i<=roundnumbers ; i++){
         cout<<"ROUND ["<<i<<"] is begin :"<<endl;
        stRoundinfo Round;
        Round.roundnumber=i;
        Round.playerchoice=getplayerchoice();
        Round.computerchoice=getcomputerchoice();
        Round.playertoolname= toolname(Round.playerchoice);
        Round.computertoolname= toolname(Round.computerchoice);;
        Round.winner= whoiswinround(Round);
        Round.winnername= winnername(Round.winner);
        printroundresult(Round);
        switch (Round.winner) {
            case Player:playerwins++;break;
            case Computer:computerwins++;break;
            default:draw++;
        }
    }
    return fillgameresult(roundnumbers,playerwins,computerwins,draw);
}

void gamestart(){
    char play='Y';
    do {
        resetscreen();
        cout<<"HOW MANY ROUNDS YOU WANT TO PLAY?"<<endl;
        int x=0;
        cin>>x;
         stgameresult gameresult =  gameplay(x);
        cout<<"\n";
        printgameresult(gameresult);
        cout<<"\n DO YOU WANT TO PLAY ANOTHER GAME? "<<endl;
        cin>>play;
    }while(play=='y'||play=='Y');
}


int main(){
    MA7SERE
    srand((unsigned)time(NULL));
    gamestart();
    return 0;
}
