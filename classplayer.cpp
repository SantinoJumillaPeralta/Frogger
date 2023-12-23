#include <iostream>
#include <conio2.h>
#include <ctime>
#include <windows.h>



const int bordeSup = 1;
const int bordeIzq = 1;
const int bordeDer = 80;
const int bordeInf = 20;

class Jugador {
	clock_t tempo;
	clock_t paso;
	int direccionX;
	int direccionY;
	int col;
	int x, y;
	
	void borrar();
	void dibujar();
	void mover();
	void controlTeclado();
	void mostrarMensaje(); // Nueva función para mostrar el mensaje
	
public:
	Jugador(double velocidad, int color);
	void start();
};

Jugador::Jugador(double velocidad, int color = WHITE) {
	paso = CLOCKS_PER_SEC / velocidad;
	tempo = clock();
	col = color;
	direccionX = 1;
	direccionY = 1;
	x = rand() % 20 + 1;
	y = rand() % 20 + 1;
}

void Jugador::start() {
	textcolor(col);
	
	controlTeclado();
	
	if (tempo + paso < clock()) {
		borrar();
		mover();
		dibujar();
		mostrarMensaje(); // Mostrar el mensaje junto al movimiento
		tempo = clock();
	}
}

void Jugador::borrar() {
	gotoxy(x, y);
	textcolor(7);
	std::cout << ' ';
	textcolor(col);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Jugador::dibujar() {
	gotoxy(x, y);
	std::cout << 'O';
}

void Jugador::mover() {
	if (x >= bordeDer) {
		direccionX = -1;
	}
	if (x <= bordeIzq) {
		direccionX = 1;
	}
	if (y <= bordeSup) {
		direccionY = 1;
	}
	if (y >= bordeInf) {
		direccionY = -1;
	}
	x = x + (1 * direccionX);
	y = y + (1 * direccionY);
}

void Jugador::controlTeclado() {
	if (kbhit()) {
		int tecla = getch();
		
		switch (tecla) {
		case 75: // Izquierda
			direccionX = -1;
			direccionY = 0;
			break;
		case 77: // Derecha
			direccionX = 1;
			direccionY = 0;
			break;
		case 72: // Arriba
			direccionX = 0;
			direccionY = -1;
			break;
		case 80: // Abajo
			direccionX = 0;
			direccionY = 1;
			break;
		case 'z':
			exit(0);
			break;
		}
	}
}

void Jugador::mostrarMensaje() {
	// Mostrar el mensaje en la posición (30, 10)
	gotoxy(30, 10);
	std::cout << "¡Soy una rana!";
}

int main(int argc, char *argv[]) {
	double velocidadPorSegundo = 1.0; // Un movimiento por segundo
	int velocidad = static_cast<int>(velocidadPorSegundo);
	
	Jugador j1(velocidadPorSegundo, 1);
	Jugador j2(velocidadPorSegundo * 2, 14);
	
	while (true) {
		j1.start();
		j2.start();
	}
	
	return 0;
}
