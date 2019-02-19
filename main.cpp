#include "peintre.h"
#include "jeu.h"
#include "GL/glut.h"

#include<iostream>
#include<cstring>
#include<cstdio>
#include <ctime>
#include<cstdlib>
using namespace std;
Jeu jeu;

int flagPause; //Oyunu beklemeye almak için kullanılacak bayrak.
int flagTick; //Yılanın bir engele veya kendisine çarptığı bilgisini tutan bayrak.
int flagLevel2; // Oyunda 2. seviyeye geçildiğini belirten bayrak.
int flagFinish; //2. seviyenin tamamlandığını belirten bayrak.
int highScore; //En yüksek skora ulaşıldığında set edilecek bayrak.
int snakeSpeed; //Yılanın hareket hızını belirleyen değişken.
int flagL2; //2. seviyeye geçmeden önce bir süre bekleme yapılmasını sağlayan bayrak.
void printtext(int x, int y, string String);

enum Level {
	LEVEL1, LEVEL2
};
//Oyunun seviyelerini belirlemek için kullanılır.

Level level;
void drawBorder() { //Ekrana yılanın hareket edebileceği bir sınır çizer.

	double w = 167, h = 167;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.2, 0.2);
	glVertex2f(0.2, h);
	glVertex2f(w, h);
	glVertex2f(w, 0.2);
	glEnd();
}
void level2Start(){
	level = LEVEL2;

	jeu.constructor(); //2. seviyede 1. seviyedeki sınırların(engellerin) da aynı kalmasını sağlar.

	jeu.setlevel2(); //engeller ekrana çizdirilir.
	snakeSpeed = 190; //yılanın hızı arttırılır.
}
void display() {
	int score;

	drawBorder();

	char str[64];

	score = jeu.lengthOfSnake();			//yılanın kaç kutudan oluştuğu bilgisini yani uzunluğunu verir.

	if (!score)
		score = 1;

	if (level == LEVEL1) { //Eğer 1. seviyedeyse yılanın yediği her yiyecek için 20 puan skora eklenir.
		score = (score - 1) * 20;
		sprintf(str, "Niveau : 1");

	} else if (level == LEVEL2) { //2.seviyeye geçildiğinde 1. seviyedeki skorun üzerine, yenilen her yiyecek için 40 puan eklenir.
		score = 140 + (score - 1) * 40;
		sprintf(str, "Niveau : 2");
	}

	printtext(170, 120, str);
	sprintf(str, "Score le plus eleve: %d", highScore);
	printtext(170, 80, str);
	sprintf(str, "Votre Score : %d ", score);
	printtext(170, 100, str);

	if (score == 140 && !flagLevel2) { //Skor 140 ise 1. seviye tamamlanmış olur ve 2. seviyeye geçilir.

		flagL2 = 1; //2. seviye bayrağı set edilir.

		sprintf(str, "Felicitations! Vous avez termine le niveau 1!");
		printtext(55, 185, str);
		flagLevel2=1;
		}

	if (score == 460) { //2. seviye tamamlanmış olur.

		flagFinish = 1; //bitiş bayrağı set edilir.

		sprintf(str, "Felicitations, vous avez termine tous les niveaux!");
		printtext(55, 185, str);
		sprintf(str,"Appuyez sur 'e' ou 'E' pour quitter le jeu ou attendez que le jeu recommence.");
		printtext(50, 195, str);


		//oyunu yeniden başlatmak için ayarları sıfırla.
		flagLevel2 = 0;
		snakeSpeed = 200;
		score = 1;
		level = LEVEL1;

	}

	//Eğer yılan bir engele veya ekranın kenarına çarptıysa oyunu bitir ve sonuçları ekrana bastır.
	if (flagTick == 1)
	{
		sprintf(str, "Votre Score : %d ", score);
		printtext(70, 175, str);

		if (score > highScore) {
			highScore = score;
			sprintf(str, "Felicitations! Vous avez le meilleur score.");
			printtext(55, 185, str);
		}

		sprintf(str,
				"Appuyez sur 'e' ou 'E' pour quitter le jeu ou attendez que le jeu recommence. ");
		printtext(50, 195, str);


		//Oyunu yeniden başlatmak için ayarları resetler.
		flagLevel2 = 0;
		snakeSpeed = 200;
		score = 1;
		level = LEVEL1;
	}

	Peintre p;

	jeu.draw(p);

	glutSwapBuffers();

}

//Parametre olarak verilen String'i, belirtilen (x,y) koordinatlarından başlayarak ekrana yazan fonksiyon.
void printtext(int x, int y, string String) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2i(x, y);
	for (int i = 0; i < String.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

//Oyunun çeşitli durumlarda bir süre beklemesini sağlayan fonksiyon.
void timer(int x = 0) {
	flagTick = jeu.tick();
	display();
	if (flagTick == 1) {
		jeu.constructor();
		flagTick = 0;
		sleep(5);
	}
	if (flagFinish) {
		flagFinish = 0;
		jeu.constructor();
		flagTick = 0;
		sleep(5);
	}
	if(flagL2){
		flagLevel2=1;
		//jeu.constructor();
		flagTick=0;
		level2Start();
		flagL2=0;
		sleep(3);
	}
	if (flagPause == 0)
		glutTimerFunc(snakeSpeed, timer, 0);

}

//Yön tuşlarına basıldığında yılanın o yönde hareket etmesini sağlayan fonksiyon.
void specialEvent(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT:
		jeu.keyEvent(Snake::LEFT);
		break;
	case GLUT_KEY_UP:
		jeu.keyEvent(Snake::UP);
		break;
	case GLUT_KEY_RIGHT:
		jeu.keyEvent(Snake::RIGHT);
		break;
	case GLUT_KEY_DOWN:
		jeu.keyEvent(Snake::DOWN);
		break;
	}
}

//Klavyeden e veya E harfine basıldığında oyun penceresini kapatan; p tuşuna basıldığında ise oyunu bekleme moduna alan fonksiyon.
void keyboardEvent(unsigned char key, int a, int b){

	switch (key) {
	case 'E': //Oyundan çık.
	case 'e':
		exit(-1);
		break;
	case 'p':
		flagPause = 1;							//Oyunu beklemeye al
		break;
	default:
		if (flagPause) {
			flagPause = 0;						//Oyunu devam ettir.
			glutTimerFunc(snakeSpeed, timer, 0);
		}
		break;

	}
}


void Initialize(void) {
	glMatrixMode(GL_PROJECTION);
	glClearColor(0, 0, 0, 1);

}

//Ekran boyutunun başlangıçtaki ile aynı kalmasını sağlar.
void reshape() {

	glutReshapeWindow(1600, 800);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //Bit mask to select a double buffered window or RGB Window
	glutInitWindowSize(1600, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Snake Game v1.0");
	glClearColor(0, 0, 0, 1.0); // opaque
	glMatrixMode(GL_PROJECTION); // Applies subsequent matrix operations to the projection matrix stack
	gluPerspective(10.0f, 1, 0.0f, 35.0f);
	glLoadIdentity();
	glOrtho(0, 200, 200, 0, -1.0, 1.0);
	glutDisplayFunc(display);
	glutSpecialFunc(specialEvent);
	glutKeyboardFunc(keyboardEvent);
	Initialize();
	level = LEVEL1; //başlangıç seviyesi set edilir.
	snakeSpeed = 200; //başlangıç hızı set edilir.
	timer();
	srand(time(NULL));
	glutMainLoop();
}

