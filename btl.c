#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL   = 218;
const char TM   = 194;
const char TR   = 191;
const char BL   = 192;
const char BM   = 193;
const char BR   = 217;
const int numW  = 3;             // Width for writing out an integer
const int charW = 1;             // Width for writing out a character
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const char* inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const char* endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* invalidInput = "Illegal input, please try again: ";

enum Stone {NA, X, O};

struct Move {
    int row;
    int col;
    enum Stone stone;
};

static char* lineString( char left, char mid, char right, char horz, int wcell, int ncell ) {
    static char result[100];
    strcpy(result, "");
    char cell[10];
    for(int i = 0; i < wcell; i++){
        cell[i] = horz;
    }
    cell[wcell] = '\0';
    strncat(result,&left,1);
    char cellMid[20];
    strcpy(cellMid, cell);
    strncat(cellMid, &mid,1);
    for ( int i = 0; i < ncell - 1; i++ )
        strcat(result, cellMid);
    char cellRight[20];
    strcpy(cellRight, cell);
    strncat(cellRight, &right,1);
    strcat(result, cellRight);
    return result;
}

void displayBoard(enum Stone arr[][15], int size) {
    //UPPERLINE
    printf("   ");
    for(int i = 0; i < size; i++) {
        printf("  %c ", (char)(i + 'a'));
    }
    printf("\n");
    printf("   %s\n", lineString( TL, TM, TR, HORZ, 3, numPerLine ));

    //MIDDLE
    for(int i = 0; i < size; i++) {
        printf("%2d %c", size - i, VERT);
        for(int j = 0; j < size; j++) {
            if(arr[i][j] == NA) printf("   %c", VERT);
            if(arr[i][j] == X) printf(" X %c", VERT);
            if(arr[i][j] == O) printf(" O %c", VERT);
        }
        printf("\n");
        if(i != size - 1) printf("   %s\n", lineString( VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine ));
    }

    //UNDERLINE
    printf("   %s\n", lineString( BL, BM, BR, HORZ, 3, numPerLine ));
}

void displayBoardSimple(enum Stone arr[][15], int size) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++) {
            printf("%d", arr[i][j]);
        }
    }
    printf("\n");
}

int r,c;
bool makeMove(enum Stone board[][15], int size, char* playerMove, bool isFirstPlayerTurn){
    //BEGIN TODO
    // bang chay tu 0 den 14 
    c = playerMove[strlen(playerMove)-1]-97;
    
    if(strlen(playerMove)==2){
    	r=playerMove[0]-48;
    	r=15-r;
	}else if(strlen(playerMove)==3){
		r=playerMove[0]-48;
		r=r*10+playerMove[1]-48;
		r=15-r;
	}else{
	    return false;
	}
	
    
    if (r>=0 && r<15 && c>=0 && c<15 && board[r][c] == NA ) {
        if(isFirstPlayerTurn==true){
        	board[r][c] = 1;
        	return true;
		}else{
			board[r][c] = 2;
			return true;
		}		
    }else{
        return false ;
    }
    //END TODO
}

bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
    //BEGIN TODO
    bool check_ngang(int a,int b){
	    int dem;
	    int dem_trai=0,dem_phai=0;
	    int x=a+1;
	    while(x<=14 && board[x][b]==board[a][b]){
			dem_phai++;
			x++;
		}
		x=a-1;
	    while(x>=0 && board[x][b]==board[a][b]){
			dem_trai++;
			x--;
		}
		dem=1+dem_trai+dem_phai;
		if (dem>=6) {
			return false;
		}else if((dem==5 && board[a-1-dem_trai][b]==NA)||(dem==5 &&board[a+dem_phai+1][b]==NA)){
			return true;
		}else{
			return false;
		}
	}
    bool check_doc(int a,int b){
		int dem;
		int dem_tren=0,dem_duoi=0;
		int y=b+1;
		while(y<=14 && board[a][y]==board[a][b]){
			dem_tren++;
			y++;
		}
		y=b-1;
		while(y>=0 && board[a][y]==board[a][b]){
			dem_duoi++;
			y--;
		}
		dem=1+dem_duoi+dem_tren;
		if (dem>=6) {
			return false;
		}else if((dem==5 && board[a][b+1+dem_tren]==NA)||(dem==5 && board[a][b-1-dem_duoi]==NA)){
			return true;
		}else{
			return false;
		}
	}
	bool check_cheochinh(int a,int b){
		int dem;
		int dem_trai=0,dem_phai=0;
		int x=a+1;
		int y=b+1;
		while(x<=14 && y<=14 && board[a][b]==board[x][y]){
			dem_phai=dem_phai+1;
			x++;
			y++;
		}
		x=a-1;
		y=b-1;
		while(x>=0 && y>=0 && board[a][b]==board[x][y]){
			dem_trai=dem_trai+1;
			x--;
			y--;
		}
		dem=1+dem_trai+dem_phai;
		if (dem>=6) {
			return false;
		}else if((dem==5 && board[a+1+dem_phai][b+1+dem_phai]==NA)||(dem==5 && board[a-1-dem_trai][b-1-dem_trai]==NA)){
			return true;
		}else{
			return false;
		}
	}
	bool check_cheophu(int a,int b){
		int dem;
		int dem_trai=0,dem_phai=0;
		int x=a+1;
		int y=b-1;
		while(x<=14 && y>=0 && board[a][b]==board[x][y]){
			dem_trai=dem_trai+1;
			x++;
			y--;
		}
		x=a-1;
		y=b+1;
		while(x>=0 && y<=14 && board[a][b]==board[x][y]){
			dem_phai=dem_phai+1;
			x--;
			y++;
		}
		dem=1+dem_trai+dem_phai;
		if (dem>=6) {
			return false;
		}else if((dem==5 && board[a+1+dem_trai][b-1-dem_trai]==NA)||(dem==5 && board[a-1-dem_phai][b+1+dem_phai]==NA)){
			return true;
		}else{
			return false;
		}
	}
	bool total_check(int x,int y){
		if (check_ngang(x,y)==true || check_doc(x,y)==true || check_cheochinh(x,y)==true || check_cheophu(x,y)==true){
			return true;
		}else{
			return false;
		}
	}
	if (total_check(r,c)==true){
		return true;
	}else{
		return false;
	}

    //END TODO
}

void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
    char playerInput[10];
    enum Stone game[15][15];
    char phanso[700];
    char arr[700][5];
    int x=0,y=0,z=0;
    int nuocdihientai=-1;
	int row,col;
    //char history2[sizeof(char*)];
	//tao cac gia tri NA ban dau
	
	//memcpy(history2,&history,sizeof(char*));
    //tao 1 arr chua nuoc di sau do loc tu chuoi ki tu ra voi nuoc di dau la arr[0][];
    for(int i=0;i<(strlen(history));i++){
        if(history[i]>=48 && history[i]<=57){
            arr[x][y]=history[i];
            y=y+1;
            z=z+1;
            
        }else{
            arr[x][y]=history[i];
            phanso[x]=z;
            x=x+1;
            y=0;        
            z=0;
        }
    }
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            game[i][j] = NA;
        }
    }
	displayBoardSimple(game,15);
    printf("%s",inputCommand);

	while(true){
	    scanf("%s",playerInput);	
	    
	    if(playerInput[0] == 110){
		    if(nuocdihientai==numOfMoves-1){
			    printf("%s",endOfHistory);
		    }else{
			    nuocdihientai=nuocdihientai+1;
			    if(phanso[nuocdihientai]==2){
				    col = (int)arr[nuocdihientai][2]-97;	
    			    row = ((int)(arr[nuocdihientai][0])-48);
				    row=row*10+(int)(arr[nuocdihientai][1]-48);	
    			    row=15-row;
			    }else{
				    col = (int)arr[nuocdihientai][1]-97;
				    row = ((int)arr[nuocdihientai][0]-48);
			    	row=15-row;
		    	}
	    		if(nuocdihientai%2==0){
		    		game[row][col]=1;
	    		}else{
	    			game[row][col]=2;
	    		}	
    			displayBoardSimple(game,15);	
    			printf("%s",inputCommand);

    		}	
    	}else if(playerInput[0]==112){
    		if(nuocdihientai==-1){
    			printf("%s",startOfGame);
    		}else{
    		    if(phanso[nuocdihientai]==2){
				    col = (int)arr[nuocdihientai][2]-97;	
    			    row = ((int)(arr[nuocdihientai][0])-48);
				    row=row*10+(int)(arr[nuocdihientai][1]-48);	
    			    row=15-row;
			    }else{
				    col = (int)arr[nuocdihientai][1]-97;
				    row = ((int)arr[nuocdihientai][0]-48);
			    	row=15-row;
		    	}
    			game[row][col] = 0;
    			displayBoardSimple(game,15);
    			nuocdihientai=nuocdihientai-1;
    			printf("%s",inputCommand);

    		}
    	}else if(playerInput[0]==115){
    		exit(0);
    	}else{
    		printf("%s",invalidInput);
    		}
    	}
    //END TODO
}
void startGame() {
    enum Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoardSimple(game, MAX_SIZE);
    char playerMove[50];
    bool player1Turn = true;
    printf("Player 1 turn: ");
    while(true) {
        scanf("%s", playerMove);
        if(strcmp(playerMove,"ff") == 0) {
            printf("%s", ((player1Turn) ? "Player 2 won " : "Player 1 won "));
            break;
        }
        else if(makeMove(game, MAX_SIZE, playerMove, player1Turn)){
            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoardSimple(game, MAX_SIZE);
                printf("%s", ((player1Turn) ? "Player 1 won " : "Player 2 won "));
                return;
            }
            player1Turn = !player1Turn;
            displayBoardSimple(game, MAX_SIZE);
            printf("%s", ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: "));
        } else {
            printf("Illegal move, please try again: ");
        }
    }
}

int main()
{
    printf("Welcome to Gomoku!\n");
    printf("1. Play game\n");
    printf("2. History\n");
    printf("3. Exit\n");
    printf("Please select mode [1/2/3]: ");
    int mode;
    while(true){
        scanf("%d", &mode);
        if(mode == 1) {
            startGame();
            return 0;
        } else if (mode == 2) {
            int numOfMoves;
            printf("Please enter number of moves: ");
            scanf("%d", &numOfMoves);
            char history[700];
            printf("Please enter history: ");
            scanf("%s", history);
            displayHistory(history, numOfMoves);
            return 0;
        } else if (mode == 3) {
            return 0;
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid mode, please try again: ");
        }
    }

    return 0;
}