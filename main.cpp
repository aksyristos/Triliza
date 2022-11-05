#include <iostream>
using namespace std;

char s[3][3]={'_','_','_','_','_','_','_','_','_'};                 //state
//X->player
//O->AI
char checkWinner();
int eval(char K);
int minmax(int depth,bool isMAX,int alpha,int beta);


int *bestMove(){
    int bestscore=-20;
    int score,alpha=-20,beta=20;
    int mv[2];
    for (int i=0;i<3;i++)                                           //AI plays
        for (int j=0;j<3;j++)
            if (s[i][j]=='_'){
                s[i][j]='O';
                score=minmax(0,false,alpha,beta);
                s[i][j]='_';
                if (score>bestscore) {
                    alpha = score;
                    bestscore = alpha;
                    mv[0]=i;mv[1]=j;
                }
               // if (alpha>=beta) break;
            }
    int *a=mv;
    return a;
}

int minmax(int depth,bool isMAX,int alpha,int beta){
    char result=checkWinner();
    if (result!='\0')
        return eval(result);
    if (isMAX) {
        int bestscore = -20;
        int score;
        //struct ID b;
        for (int i = 0; i < 3; i++)                                           //AI plays
            for (int j = 0; j < 3; j++)
                if (s[i][j] == '_') {
                    s[i][j] = 'O';
                    score = minmax(depth+1, false, alpha, beta);
                    s[i][j] = '_';
                    if (score > bestscore)
                        bestscore = score;
                    if (bestscore >= beta)
                        return bestscore;
                    if (alpha > bestscore)
                        alpha = bestscore;
                }
        //b.score=bestscore;
        return bestscore;
    }else{
        int bestscore = 20;
        int score;
        //struct ID c;
        for (int i = 0; i < 3; i++)                                           //Human plays
            for (int j = 0; j < 3; j++)
                if (s[i][j] == '_') {
                    s[i][j] = 'X';
                    score = minmax(depth + 1, true, alpha, beta);
                    s[i][j] = '_';
                    if (score < bestscore)
                        bestscore = score;
                    if (bestscore <= alpha)
                        return bestscore;
                    if (beta > bestscore)
                        beta = bestscore;
                }
        //c.score=bestscore;
        return bestscore;
    }

}

int checkavai() {
    //int empty = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (s[i][j] == '_')
                return 1;
    return 0;
}

int eval(char K){
    if(K=='X')return -10;
    if(K=='O')return 10;
    if(K=='T')return 0;
}


int equal3(char a, char b, char c){
    if( a==b && b==c && a!='_') return 1;
    return 0;
}

char checkWinner(){
    char win='\0';
    if (equal3(s[0][2],s[1][1],s[2][0]))                                    //diagonal
        return s[1][1];
    //win=s[1][1];                                                     

    if (equal3(s[0][0],s[1][1],s[2][2]))
        return s[1][1];
    //win=s[1][1];

    for (int i=0;i<3;i++) {                                             //vertical
        if (equal3(s[0][i],s[1][i],s[2][i])){
            return s[0][i];
            //win=s[0][i];
            //break;
        }
    }
    for (int i=0;i<3;i++) {                                             //horizontical
        if (equal3(s[i][0],s[i][1],s[i][2])){
            return s[i][0];
            //win=s[i][0];
            //break;
        }
    }

/*
    int empty=0;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (s[i][j]=='.'){
                empty=1;
                break;
            }
*/
    //if (win=='\0'&& !checkavai()){
    if (!checkavai()){
        return 'T';
    }else{
        return win;
    }

}


void printState(){
    cout << s[0][0] << s[0][1] << s[0][2] << endl << s[1][0] << s[1][1] << s[1][2] << endl << s[2][0] << s[2][1] << s[2][2] << endl<<endl;
}

int main() {
    //char state[3][3]={'_','_','_','_','_','_','_','_','_'};
    printState();
    int wincond=0;
    int x,y;
    do{
        do{
            cout << "You play" << endl;                     //TODO not overwrite
            cin >> x >> y;
        }while(x<1||x>3||y<1||y>3||s[x-1][y-1]!='_');
        s[x-1][y-1]='X';
        printState();
        switch (checkWinner()){
            case 'X':
                cout << "YOU WON\n";
                wincond=1;
                break;
            case  'O':
                cout << "YOU LOST\n";
                wincond=1;
                break;
            case  'T':
                cout << "TIE\n";
                wincond=1;
                break;
            default:
                break;
        }
        if (wincond) break;

        int *mv=bestMove();
        s[mv[0]][mv[1]]='O';
        printState();
        switch (checkWinner()){
            case 'X':
                cout << "YOU WON\n";
                wincond=1;
                break;
            case  'O':
                cout << "YOU LOST\n";
                wincond=1;
                break;
            case  'T':
                cout << "TIE\n";
                wincond=1;
                break;
            default:
                break;
        }
    }while(checkavai()&&!wincond);
    return 0;
}
