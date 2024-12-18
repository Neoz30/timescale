#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

int operation(int value, int value2, int index) {
    switch (index) {
    case 0:
        return value | value2;
        break;
    case 1:
        return value & value2;
        break;
    case 2:
        return value ^ value2;
        break;
    case 3:
        return ~value;
        break;
    case 4:
        return value << value2;
        break;
    case 5:
        return value >> value2;
        break;
    case 6:
        return -value;
        break;
    default:
        return 0;
        break;
    }
}

class Individu {
    public:
        int parameters[8] = {0};
    
        void randomize() {
            for (int i = 0; i < 8; i+=2) {
                parameters[i] = rand() % 7;
            }
            for (int i = 1; i < 8; i+=2) {
                parameters[i] = rand() % 8;
            }
        }

        // A verifier pour donnar les meilleur resultat
        int fitness() {
            int score = 0;
            for (int i = 0; i < 9; i++) {
                int x = operation(operation(i, parameters[0], parameters[1]), parameters[2], parameters[3]);
                int y = operation(operation(i, parameters[4], parameters[5]), parameters[6], parameters[7]);

                x = abs(x); y = abs(y);

                if (i == 0 && x == 0 && y == 0) score++;
                if (1 <= i && i <= 4 && ((x == -1 && x == 1) ^ (y == -1 && y == 1))) score++;
                if (5 <= i && i <= 8 &&  ((x == -1 && x == 1) && (y == -1 && y == 1))) score++;
            }
            return score;
        }

        void mutation() {
            if (rand() % 100 < 60) {
                parameters[rand() % 4 * 2] = rand() % 7;
                parameters[rand() % 4 * 2 + 1] = rand() % 8;
            }
        }
};

void selection(Individu population[16], int order[16]) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < 15; i++) {
            if (order[i] > order[i+1]) {
                int s0 = order[i];
                order[i] = order[i+1];
                order[i+1] = s0;
                Individu s1 = population[i];
                population[i] = population[i+1];
                population[i+1] = s1;

                swapped = true;
            }
        }
    }
}

int main() {
    srand(time(0));

    Individu population[16];
    for (int i = 0; i < 16; i++) {population[i].randomize();}
    int fitness_score[16] = {0};

    int gen = 0;
    while (gen < 100000) {
        cout << gen << endl;
        for (int i = 0; i < 16; i++) {
            fitness_score[i] = population[i].fitness();
        }

        selection(population, fitness_score);

        if (fitness_score[15] == 9) break;

        for (int i = 0; i < 16; i++) {population[i].mutation();}
        for (int i = 8; i < 16; i++) {population[i].randomize();}

        gen++;
    }

    Individu best = population[15];
    cout << best.fitness() << endl;
    cout << best.parameters[0] << ":" << best.parameters[1] << endl;
    cout << best.parameters[2] << ":" << best.parameters[3] << endl;
    cout << best.parameters[4] << ":" << best.parameters[5] << endl;
    cout << best.parameters[6] << ":" << best.parameters[7] << endl;
    return 0;
}