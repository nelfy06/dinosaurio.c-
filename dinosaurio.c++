include <iostream>
#include <conio.h> // Para _kbhit() y _getch()
#include <windows.h> // Para Sleep()

bool gameOver;
const int width = 20;
const int height = 5;
int x, y, obstacleX, obstacleY;
int score;
enum eDirecton { STOP = 0, LEFT, RIGHT, JUMP };
eDirecton dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = 1;
    y = height - 1;
    obstacleX = width - 2;
    obstacleY = height - 1;
    score = 0;
}

void Draw() {
    system("cls"); // Limpia la pantalla
    for (int i = 0; i < width + 2; i++)
        std::cout << " ";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << " "; // Paredes laterales
            if (i == y && j == x)
                std::cout << "R"; // Dinosaurio
            else if (i == obstacleY && j == obstacleX)
                std::cout << "+"; // Obstáculo
            else
                std::cout << " ";

           if (j == width - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "_";
    std::cout << std::endl;
    std::cout << "Puntuacion: " << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case ' ':
            if (dir != JUMP) {
                dir = JUMP;
                y--;
            }
            break;
        }
    }
}

void Logic() {
    switch (dir) {
    case JUMP:
        y--;
        if (y == 0) {
            dir = STOP;
        }
        break;
    default:
        break;
    }

    if (dir == STOP && y < height - 1) {
        y++;
    }

    if (obstacleX > 0) {
        obstacleX--;
    } else {
        obstacleX = width - 2;
        score++;
    }

    if (x == obstacleX && y == obstacleY) {
        gameOver = true;
    }
}

void Run() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(75); // Hace que el juego vaya más lento
    }
    std::cout << "Juego terminado" << std::endl;
std::cout << "Tu puntuacion final es: " << score << std::endl;

}

int main() {
    Run();
    return 0;
}
