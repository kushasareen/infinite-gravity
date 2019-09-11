//imports
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
#include "Player.h"
#include "Character.h"
#include "global.h"

using namespace std;


// initialize OpenGL graphics
void initGL() {
	// background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black opaque
}


void print_to_file(FILE *f, score s1) { //prints a score to file

	if (fwrite(&s1, sizeof(s1), 1, f) != 1) {

		printf("Error writing file\n");
		exit(0);
	}

}

score read_from_file(FILE *f, score s1) { //reads a score from the file

	if ((fread(&s1, sizeof(score), 1, f) != 1) && !feof(f)) {

		printf("Error reading file\n");
		exit(0);

	}

	s1.username[score_size-1]  = '\0';

	return s1;

}

void recordScore(score s1, int new_score){
	s1.game_score = new_score;

	FILE *fPtr;


	score my_score = {123, "kusha"};

	if ((fPtr = fopen("C:\\Users\\kusha\\OneDrive\\Documents\\hello.bin", "r+b")) == NULL) { //opens file for reading and writing

		cout << "Writing new file..." << endl;

		if ((fPtr = fopen("C:\\Users\\kusha\\OneDrive\\Documents\\hello.bin", "w+b")) == NULL) { //creates new file

			printf("Error opening file\n");
			exit(0);

		}

		print_to_file(fPtr, my_score); //prints my score to file

	}


	if (fseek(fPtr, 0, SEEK_END) == -1) {

		printf("Error seeking\n");
		exit(0);

	}

	print_to_file(fPtr, s1); //user score at end of file

	if (fclose(fPtr) != 0) {
		printf("Error closing file\n");
		exit(0);
	}

	cout << "Your score (" << s1.game_score << " points) has been saved. Play again to try to beat your score!" << endl;

}

void collision(float x, float y, float h, float w, int m1[3][17][50], float a, int m_n, score a_score, int end) { //goes through map array and checks collision for each block
	//iterates through map array
	for (int i = 0; i < end; i++) //end continually increases as the player gets further in the game
		for (int j = 0; j < 17; j++)
			if (m1[m_n][j][i % 50] == 1){ //if block exists at given position (i % 50 is used to infinite loop the x coordinates of the map)
				if (x < -1.0f + 0.1f*i + 0.1f &&
						x + w > -1.0f + 0.1f*i &&
						y < 0.7f - 0.1f*j + 0.1f &&
						y + h > 0.7f - 0.1f*j) { //standard collision detection code (x, y, width, height of specific blocks are entered as positions on the screen dependent on position in map array)
					//recordScore(a_score, -100*a); //writes score to file
					exit(0);
				}
			}

}



void prompt(const char *prompt, char *buffer, int buffer_size) { //prompt for text input

	printf("%s: ", prompt);
	fflush(stdout);
	fgets(buffer, buffer_size, stdin);

	buffer[strlen(buffer) - 1] = '\0';

}

void bubbleSort(score arr[], int size) { //sorts scores using modified bubble sort

	score tmp;
	int pass = 0;
	int swap_done;

	do {
		swap_done = 0;

		for (int i = 0; i < size - 1 - pass; i++)

			if (arr[i].game_score > arr[i + 1].game_score ) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;

				swap_done = 1;
			}
		pass++;

	} while (swap_done);

}



//initialize static variables of game class


int main(int argc, char** argv) {

	Game g;

	char tmp[score_size];

	//prompt ("Welcome to Kusha's infinite sidescrolling game 'Gravity'! Enter a 10 character username so that your score can be recorded and saved on our prestigous high scores list", tmp, 10 );

	g.setUsername(tmp);

	char input[20];
	//prompt ("What would you like to do? (play/check high scores)", input, 20 );

	//if (strcmp(input, "play") == 0) {

		prompt ("Which map would you like to play? (1/2/3)", input, 20 );

		g.setM_num(atoi(input) - 1); //allows user to choose map


		cout << "The 'W' key is used to jump, 'A' is used to move left, 'D' is used to move right, and 'S' is used to flip gravity. " << endl <<  "You can ride on both the top and bottom of the map but the game will end if you come into contact with any geometry. Good luck!"  << endl;
		glutInit(&argc, argv);          // Initialize GLUT
		glutCreateWindow("Gravity");  // Create window with the given title
		glutFullScreen();
		glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
		initGL();                       // Our own OpenGL initialization
		glutDisplayFunc(g.display);       // Register callback handler for window re-paint event
		glutKeyboardFunc(g.keyboard);
		g.update(0);
		glutMainLoop();                 // Enter the event-processing loop

	//} else if (strcmp(input, "check high scores") == 0) {

		FILE *fPtr;


		if ((fPtr = fopen("C:\\Users\\kusha\\OneDrive\\Documents\\hello.bin", "r+b")) == NULL) {

			cout << "No high scores yet!" << endl;
			exit(0);

		}


		if (fseek(fPtr, 0, SEEK_END) == -1) {

			printf("Error seeking\n");
			exit(0);

		}

		int num_scores = ftell(fPtr)/sizeof(score); //scores number of scores in file

		if (fseek(fPtr, 0, SEEK_SET) == -1) {

			printf("Error seeking\n");
			return 0;

		}

		score all_scores[num_scores];

		for (int i = 0; i < num_scores; i++){ //stores scores in array
			all_scores[i] = read_from_file(fPtr, all_scores[i]);

		}

		if (fclose(fPtr) != 0) {
			printf("Error closing file\n");
			exit(0);
		}

		bubbleSort(all_scores, num_scores); //sorts array

		for (int i = num_scores; i > 0; i--) //prints top 10 scores
			cout << num_scores - i + 1 << ". " << all_scores[i - 1].username << " scored " << all_scores[i - 1].game_score << " points!" << endl;


	//} else
		cout << "Invalid Input" << endl;

	return 0;
}
