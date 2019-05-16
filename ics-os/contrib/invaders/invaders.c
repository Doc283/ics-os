/*
 * Source code provided for by ForwardSlashReality
 * Reference: 
 *	https://www.youtube.com/watch?v=k6rTH77tML0
 *  https://drive.google.com/file/d/0B0oXu1PhCuHpbVNpd29rc1Q2T3c/edit
 *
 * Jasper L. Cabigting
 * Carl Vincent P. Eusebio
 * CMSC 125 T-2L
 */

#include "../../sdk/dexsdk.h"
// #include "../../sdk/tccsdk.c"
// #include "../../sdk/time.h"

int main(){
	int sizey = 23;
	int sizex = 40;
	int x, y, yi;
	char world[sizey][sizex];
	char player = 'A';
	char playerLaser = '|';
	char enemy = '#';
	char enemyShielded = 'O';
	char enemyLaser = 'V';
	char explosion = 'X';
	int score = 0;
	int victory = 1;
	int laserReady = 1;
	int enemyReady = 0;

	srand(time());

	clrscr();

	/* Welcome screen */
	int c = 0;
	while(c < 4	){
		if(c == 0){
			printf("\n");
			textcolor(LIGHTBLUE); printf("\t \t \t+++++  ++   ++  +++++      +       +++++  +++++++\n");
			textcolor(LIGHTGRAY); printf("\t \t \t  +    + + + +  +    +    + +     +          +\n");
			textcolor(WHITE); printf("\t \t \t  +    +  +  +  +++++    +++++   +           +\n");
			textcolor(LIGHTGRAY); printf("\t \t \t  +    +     +  +       +     +   +          +\n");
			textcolor(LIGHTRED); printf("\t \t \t+++++  +     +  +      +       +   +++++     +\n");
			delay(50);
			clrscr();

		}

		if(c == 1){
			printf("\n\n");
			textcolor(LIGHTBLUE); printf("\t \t \t+++++  ++   ++  +++++      +       +++++  +++++++\n");
			textcolor(LIGHTGRAY); printf("\t \t \t  +    + + + +  +    +    + +     +          +\n");
			textcolor(WHITE); printf("\t \t \t  +    +  +  +  +++++    +++++   +           +\n");
			textcolor(LIGHTGRAY); printf("\t \t \t  +    +     +  +       +     +   +          +\n");
			textcolor(LIGHTRED); printf("\t \t \t+++++  +     +  +      +       +   +++++     +\n");
			delay(50);
			clrscr();
		}

		if(c == 2){
			printf("\n\n\n");
			textcolor(LIGHTBLUE); printf("\t \t \t+++++  ++   ++  +++++      +       +++++  +++++++\n");
			textcolor(LIGHTGRAY); printf("\t \t \t  +    + + + +  +    +    + +     +          +\n");
			textcolor(WHITE); printf("\t \t \t  +    +  +  +  +++++    +++++   +           +\n");
			textcolor(LIGHTGRAY); printf("\t \t \t  +    +     +  +       +     +   +          +\n");
			textcolor(LIGHTRED); printf("\t \t \t+++++  +     +  +      +       +   +++++     +\n");			
			delay(50);
			clrscr();
		}

		if(c == 3){
			printf("\n\n\n\n");
			textcolor(LIGHTRED); printf("\t \t \t+++++  ++   ++  +++++      +       +++++  +++++++\n");
			textcolor(YELLOW); printf("\t \t \t  +    + + + +  +    +    + +     +          +\n");
			textcolor(WHITE); printf("\t \t \t  +    +  +  +  +++++    +++++   +           +\n");
			textcolor(YELLOW); printf("\t \t \t  +    +     +  +       +     +   +          +\n");
			textcolor(LIGHTRED); printf("\t \t \t+++++  +     +  +      +       +   +++++     +\n");
			delay(80);
			printf("\n\n\n\n\t \t \t \t \tPress any key to start.");
			getch();
		}

		c++;
	}

	textcolor(WHITE);
	clrscr();
	/* HOW TO PLAY */
	printf("\n \t \t CONTROLS: \n \n");
	printf("\t \t A - left\n");
	printf("\t \t D - right\n");
	printf("\t \t F - fire\n");
	printf("\t \t X - pause\n");
	printf("\n \t \t MECHANICS: \n \n");
	printf("\t \t You win by eliminating all enemies.\n");
	printf("\t \t Don't let enemies hit you. You will die instantly.\n");
	printf("\n\t \t The game will start out slow but will pick up speed\n");
	printf("\t \t   as more enemies get destroyed.\n\n");
	printf("\t \t Good luck, have fun.\n");
	printf("\n \n \n \t \t Press any key to start.");
	getch();

	clrscr();

	textcolor(RED); printf("\n \n \n \n \n \n \t \t \tR E A D Y .");
	delay(50);
	clrscr();
	textcolor(LIGHTRED); printf("\n \n \n \n \n \n \t \t \tR E A D Y . .");
	delay(50);
	clrscr();
	textcolor(YELLOW); printf("\n \n \n \n \n \n \t \t \tR E A D Y . . .");
	delay(75);
	clrscr();

	textcolor(GREEN); printf("\n \n \n \n \n \n \t \t \tS T A R T !");
	delay(50);
	clrscr();	


	/* Initialize world */
	int totalEnemies = 0;
	
	for(x = 0; x < sizex; x++){
		for(y = 0; y < sizey; y++){
			
			if((y + 1) % 2 == 0 && y < 7 && x > 4 && x < sizex - 5 && x % 2 == 0){
				world[y][x] = enemy;
				totalEnemies++;	
			}

			else if((y + 1) % 2 == 0 && y >= 7 && y < 9 && x > 4 && x < sizex - 5 && x % 2 == 0){
				world[y][x] = enemyShielded;
				totalEnemies = totalEnemies + 2;
			}

			else{
				world[y][x] = ' ';
			}
		}
	}

	world[sizey-1][sizex/2] = player;
	int i = 1;
	char direction = 'l';
	char keypress;
	int currentEnemies = totalEnemies;

	int gameSpeed = 7;

	while(currentEnemies > 0 && victory == 1){
		int drop = 0;
		int enemySpeed = 1 + 10 * currentEnemies/totalEnemies;
		if(currentEnemies == 60) gameSpeed = 6;
		if(currentEnemies == 45) gameSpeed = 5;
		if(currentEnemies == 30) gameSpeed = 3;
		if(currentEnemies == 15) gameSpeed = 1;

		laserReady++;

		/* Display world */
		clrscr();
		textcolor(LIGHTMAGENTA); printf("\tSCORE:\t%d  Enemies left:\t%d\n", score, currentEnemies);

		for(y = 0; y < sizey; y++){
			textcolor(LIGHTCYAN); printf("|");
			for(x = 0; x < sizex; x++){
				if(world[y][x] == enemy) textcolor(YELLOW);
				if(world[y][x] == enemyShielded) textcolor(LIGHTRED);
				if(world[y][x] == player) textcolor(CYAN);
				if(world[y][x] == enemyLaser) textcolor(MAGENTA);
				if(world[y][x] == playerLaser) textcolor(LIGHTBLUE);
				printf("%c", world[y][x]);
			}
			textcolor(LIGHTCYAN); printf("|");
			printf("\n");
		}

		/* Laser */
		for(x = 0; x < sizex; x++){
			for(y = sizey-1; y >= 0; y--){
				if(i % 2 == 0 && world[y][x] == enemyLaser && (world[y+1][x] != enemy & world[y+1][x] != enemyShielded)){
					world[y+1][x] = enemyLaser;
					world[y][x] = ' ';
				}
				else if(i % 2 == 0 && world[y][x] == enemyLaser && (world[y+1][x] == enemy | world[y+1][x] == enemyShielded)){
					world[y][x] = ' ';
				}
			}
		}

		for(x = 0; x < sizex; x++){
			for(y = 0; y < sizey; y++){
				if(i % 5 == 0 && (world[y][x] == enemyShielded | world[y][x] == enemy) && (rand() % 15) > 13 && world[y+1][x] != playerLaser){
					for(yi = y + 1; yi < sizey; yi++){
						if(world[yi][x] == enemy | world[yi][x] == enemyShielded){
							enemyReady = 0;
							break;
						}
						enemyReady = 1;
					}
					if(enemyReady){
						world[y+1][x] = enemyLaser;
					}
				}

				/* if player hits enemy without shield */
				if(world[y][x] == playerLaser && world[y-1][x] == enemy){
					world[y][x] = ' ';
					world[y-1][x] = explosion;
					currentEnemies--;
					score = score + 50;
				}

				/* if player hits enemy with shield */
				else if(world[y][x] == playerLaser && world[y-1][x] == enemyShielded){
					world[y][x] = ' ';
					world[y-1][x] = enemy;
					currentEnemies--;
					score = score + 50;
				}

				/* if player laser and enemy laser made contact */
				else if(world[y][x] == playerLaser && world[y-1][x] == enemyLaser){
					world[y][x] = ' ';
				}

				/* if an explosion occured, vacant particular cell */
				else if(world[y][x] == explosion){
					world[y][x] = ' ';
				}

				/* if player get hit by enemy */
				else if((i+1) % 2 == 0 && world[y][x] == enemyLaser && world[y+1][x] == player){
					world[y+1][x] = explosion;
					world[y][x] = ' ';
					victory = 0;
					delay(100);
				}

				/* player laser */
				else if(world[y][x] == playerLaser && world[y-1][x] != enemyLaser){
					world[y][x] = ' ';
					world[y-1][x] = playerLaser;
				}
			}
		}

		/* Update enemy direction */
		for(y = 0; y < sizey; y++){
			if(world[y][0] == enemy){
				direction = 'r';
				drop = 1;
				break;
			}

			if(world[y][sizex-1] == enemy){
				direction = 'l';
				drop = 1;
				break;
			}
		}

		/* Update board */
		if(direction == 'l'){
			for(x = 0; x < sizex - 1; x++){
				for(y = 0; y < sizey; y++){
					if(world[y][x+1] == enemy || world[y][x+1] == enemyShielded){
						world[y][x] = world[y][x+1];
						world[y][x+1] = ' ';
					}
				}
			}
		}

		else{
			for(x = sizex; x > 0; x--){
				for(y = 0; y < sizey; y++){
					if(world[y][x-1] == enemy || world[y][x-1] == enemyShielded){
						world[y][x] = world[y][x-1];
						world[y][x-1] = ' ';
					}
				}
			}
		}

		/* When enemy crosses the threshold */
		for(x = 0; x < sizex; x++){
			if(world[sizey - 1][x] == enemy){
				victory = 0;
				delay(100);
			}
		}
		

		/* Player controls */
		if(kb_ready()){
			keypress = (char)getch();
		}

		else{
			keypress = ' ';
		}

		if(keypress == 'a'){
			for(x = 0; x < sizex; x = x + 1){
				if(world[sizey-1][x+1] == player){
					world[sizey-1][x] = player;
					world[sizey-1][x+1] = ' ';
				}
			}
		}


		if(keypress == 'd'){
			for(x = sizex - 1; x > 0; x = x - 1){
				if(world[sizey-1][x-1] == player){
					world[sizey-1][x] = player;
					world[sizey-1][x-1] = ' ';
				}
			}
		}		

		if(keypress == 'f' && laserReady > 2){
			for(x = 0; x < sizex; x = x + 1){
				if(world[sizey-1][x] == player){
					world[sizey-2][x] = playerLaser;
					laserReady = 0;
				}
			}
		}

		if(keypress == 'x'){
			clrscr();
			textcolor(WHITE); printf("\n\n\n\t\t\tP A U S E\n\n");
			printf("\t\t\t [1] Resume\n");
			printf("\t\t\t [2] Exit\n");
			keypress = (char)getchar();

			if(keypress == '1') continue;
			else if(keypress == '2'){
				victory = 2;
				clrscr();
				printf("\n \n \n \t \t \t \t \t \tYou quit? All right, bye~ \n \n \n");
				break;
			}
		}		

		i++;
		delay(gameSpeed);
	}

	textcolor(WHITE); 
	if(victory == 1){
		delay(100);
		clrscr();
		delay(30);
		printf("\n \n \n \t \t \t \t \t \tYOU WON! Congratulations!~ \n \n \n");
		delay(75);
		printf("\n \t \t \t \t \t \tScore: %d \n \n", score);
		delay(75);
		printf("\n\n\t \t \tI think you're ready should there be a full scale alien\n");
		printf("\t \t \t \tinvasion directed to Earth.\n \n");
		delay(75);
		printf("\t \t \tThanos, who?\n \n \n \n");
		delay(75);
	}

	else if(victory == 0){
		clrscr();
		printf("\n \n \n \t \t \t \t \t \tYOU LOST! T.T \n \n \n");
		delay(75);
		printf("\n \t \t \t \t \t \tScore: %d \n \n", score);
		delay(100);
		printf("\n\n\t \t \tThough you may have failed, you can always try again.\n \n");
		delay(75);
		printf("\t \t \tExcept when dealing with an alien invasion.\n \n");
		delay(75);
		printf("\t \t \tYeah. A failure of that scale would mean human extinction.\n \n");
		delay(95);
		printf("\t \t \tYikes.\n \n \n \n");
		delay(75);


	}

	printf("\t \t \tPress any key to continue.");
	getch();
	clrscr();
}