#include "header.h"



//Create the board. 
int** createBoard(int n) {
  int **Board;

  Board = calloc(n, sizeof(int *));
  if (Board == NULL) {
    printf("FATAL ERROR: out of memory: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < n; i++) {
    Board[i] = calloc(n, sizeof(int));
    if (Board[i] == NULL) {
      printf("FATAL ERROR: out of memory:%s\n",strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  return Board;
}

//Print the ship on the board 
void drawBoard(int **Board, int n){
  int a,b; 
  char alphabet[20];

  for(a = 0; a<20; a++){
      alphabet[a] = 'A'+ a;
    }

  printf("    ");
  for (int a = 0; a < n; a++) {
		printf("%c ", alphabet[a]);
	}

	printf("\n  +");
  
	for(b = 0; b < n*2; b++) {
   printf("-");
  }
  
	printf("\n");
	
  
  for (int i = 0; i < n; i++) {
    if(i<9) {
			printf("%d | ", (i+1));
		}else {
			printf("%d| ", (i+1));
		}
      for(int j =0; j < n; j++){
      
        if(Board[i][j] == 'c' || Board[i][j] == 'f' || Board[i][j] == 'b'){
        printf("- ");

    }else{
        printf( "%c ", Board[i][j]);
        }
      }
    printf("\n");
    }
  return;
 }

//Draw the original ship location 
void drawBoard1(int **Board, int n){
  int a,b; 
  char alphabet[20];

  for(a = 0; a<20; a++){
      alphabet[a] = 'A'+ a;
    }

  printf("    ");
  for (int a = 0; a < n; a++) {
		printf("%c ", alphabet[a]);
	}

	printf("\n  +");
  
	for(b = 0; b < n*2; b++) {
   printf("-");
  }
  
	printf("\n");
	
  
  for (int i = 0; i < n; i++) {
    if(i<9) {
			printf("%d | ", (i+1));
		}else {
			printf("%d| ", (i+1));
		}
      for(int j =0; j < n; j++){
      
        printf( "%c ", Board[i][j]);
        }
      
    printf("\n");
    }
  return;
  
  
  }


void deleteBoard(int **Board, int n){
  for(int i =0; i< n; i++){
    free(Board[i]);
  }
  free(Board);
  return;
}

//randomly generate the ship location 
void randGenLoc(int **Board,int n, struct Ship type){
  int isOccupied = 0;
	int x,y,i,direct;
	while(isOccupied == 0) {
		x = (rand()%n);
		y = (rand()%n);
		direct = (rand()%2);

    //checking for vertical 
		if(direct == 1) { 
			for (i = 0; i<type.size; i++) {
		  		if (Board[x+i][y] == '-') {
		  			isOccupied = 1;
		  		}
		  		else {
		  			isOccupied = 0;
		  			break;
		  		}
		  	}
		}

    //checking for horizontal 
		else if (direct == 0) { 
			for (i = 0; i<type.size; i++) {
		  		if (Board[x][y +i] == '-') {
		  			isOccupied = 1;
		  		}
		  		else {
		  			isOccupied = 0;
		  			break;
		  		}
		  	}
		}
		else {
			printf("Error ");
			}
	}

  //if vertical line is not occupied then add the ship
	if(direct == 1) { //vertical 
		for (i = 0; i<type.size; i++) {
		  	Board[x+i][y] = type.name;
		}
	}
	else if (direct ==0) { //horizontal 
		for (i = 0; i<type.size; i++) {
			Board[x][y+i] = type.name;
		}
	}
	else {
		printf("Error ");
	}
  
  }
    

//Load the ship on the board
void loadShips(int **Board, int n){
  int i, j;
  for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			Board[i][j] = '-';
		}
	}

  //Making ships name and type
  struct Ship carrier, battleship, frigate;
  carrier.name = 'c'; carrier.size = 5;
	battleship.name = 'b'; battleship.size = 4;
  frigate.name = 'f'; frigate.size = 2;
  


  //randomly put the ships on the board
  randGenLoc(Board,n,frigate);
  randGenLoc(Board,n,frigate);
  randGenLoc(Board,n,battleship);
  randGenLoc(Board,n,carrier);
  
  return;
}

//Check for location 
bool checkBoard(int **Board, int rows, int cols, int *sizeC, int *sizeB, int *sizeF ){
    bool isSunk = false; 
  printf("checking board at (%d, %d) \n", rows, cols);
  
  if(Board[rows][cols] ==  '-'){
    Board[rows][cols] = (int)'X';
    printf("Miss\n");
    return true;

  //checking for carrier  
  }else if(Board[rows][cols] == 'c'){
    Board[rows][cols] = 'C';
    printf("Hit!\n");
    (*sizeC) --;
    isSunk = true;
    printf("sink 1 C part. Remaing part of Carrier: %d\n\n", (*sizeC));
    if((*sizeC) == 1){
    printf("You sunk a Carrier\n");
    }
    return true;

  //checking for battleship  
  }else if(Board[rows][cols] == 'b'){
    Board[rows][cols] = 'B';
    printf("Hit!\n");
    (*sizeB) --;
     printf("Sink 1 B part. Remaining part of Battleship: %d\n\n",(*sizeB));
    if((*sizeB) == 1){
    printf("You sunk a Battleship\n");
      }
    isSunk = true;
    return true;

  //checking for frigate
  }else if(Board[rows][cols] == 'f'){
    Board[rows][cols] = 'F';
    printf("Hit!\n");
    isSunk = true;
    (*sizeF) --;
    printf("Sink 1 F part\n\n");
    if((*sizeF) ==0 || (*sizeF) == -2){
    printf("You sunk a Frigate\n");
  }
    return true;

  }else{
    printf("You already hit this spot\n");
    return false;
  }
}


int main(int argc, char *argv[]) {
    int **ship;
    int i,n,rows,Col,shot;
    
    bool gameOver = 0;
    char buffer[20];
    bool inputPass = 0;
    char cols;
  
   
    int* sizeC = (int*)calloc(1, sizeof(int));
    int * sizeB = (int*)calloc(1, sizeof(int));
    int * sizeF = (int*)calloc(1, sizeof(int));  
    *sizeC = 5;
    *sizeB = 4;
    *sizeF = 2 ;
    
  
  printf("Welcome to Frigate\n");
  
  //User input
  printf("How large do you want the board? (5 - 20) : ");

    //input checking 
    while(!inputPass){
        fgets(buffer, 19, stdin);
        sscanf(buffer, "%d *[^\n]", &n);

        if(n > 4 && n < 21){
            inputPass = true;
        }else{
            printf("Invalid choice, must be between (5-20)\n Board Size:  ");
        }
    }

 shot = (n/2)*(n/2);
  
  //Creates battlefield
  
  ship = createBoard(n);
  loadShips(ship,n);
  drawBoard1(ship,n);

  
  //Setting for winning condition
  while(shot != 0){
  printf("\nEnter the coordinate for your shot (%d shot remaining): ", shot);
    inputPass = false;
    while(!inputPass){
      bool charPass = false;
            //get input for player's move
            rows = 25;
            fgets(buffer, 20, stdin);
            //printf("\n input is : %c%c \n", input[0], input[1]);
            if (buffer[strlen(buffer)-1] != '\n') {
                for (int c; (c = getchar()) != EOF && c != '\n';)
                    ;
            }
            
            
            if(isalpha(buffer[0])){
                sscanf(buffer, " %c%d", &cols, &rows);
            }else{
                sscanf(buffer, " %d%c", &rows, &cols);
            }

            rows = rows -1;

            //validate character input
            if(cols >= 'a' && cols < 'a' + n){
                charPass = true;
                Col = (int) cols- 'a';
            }else if(cols >= 'A' && cols < 'A' + n){
                charPass = true;
                Col = (int) cols - 'A';

            }

            //validate digit input
            if(rows > -1 && rows < (n) && charPass){
                inputPass = true;
                shot --;
             }else{
                printf("Invalid choice, must be between (A - %c) (1 - %d) \n ", ('A' + n -1) ,  n);
             }
        }
        printf("your move : col %c, row %d \n", cols, (rows+1));
        checkBoard(ship, rows, Col, sizeC, sizeB, sizeF);
      drawBoard(ship,n);
      

    if(((*sizeC) == 1 || (*sizeC) ==0) && ((*sizeB) == 1 || (*sizeB) == 0) && ((*sizeF) == -2)){
        printf("\nYou win\n");
        break;
        }
    clearerr(stdin);
    
    }

  
  if(shot == 0 ) {
    printf("\n\nGame Over\n\n");
    printf("Here is the original ships location\n");
    drawBoard1(ship,n);
  }
  }



