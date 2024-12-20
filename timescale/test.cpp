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
        return value;
        break;
    case 7:
        return -value;
        break;
    case 8:
        return value+value2;
        break;
    case 9:
        return value-value2;
        break;
    case 10:
        return value*value2;
        break;
    case 11:
        if (value2 == 0) return -1;
        return value/value2;
        break;
    default:
        return 0;
        break;
    }
}

class Individu {
    public:
        int parameters[16] = {0};
    
        void randomize() {
            for (int i = 0; i < 16; i+=2) {
                parameters[i] = rand() % 16;
            }
            for (int i = 1; i < 16; i+=2) {
                parameters[i] = rand() % 11;
            }
        }

        int fitness() {
            bool taken[3][3] = {false};

            for (int i = 0; i < 9; i++) {
                int x = operation(operation(i, parameters[0], parameters[1]), parameters[2], parameters[3]);
                int y = operation(operation(i, parameters[4], parameters[5]), parameters[6], parameters[7]);
                x = operation(operation(x, parameters[8], parameters[9]), parameters[10], parameters[11]);
                y = operation(operation(y, parameters[12], parameters[13]), parameters[14], parameters[15]);

                if (x < -1 || 1 < x || y < -1 || 1 < y) continue;

                int dst2 = x*x + y*y;

                if (i == 0 && dst2 == 0) taken[y+1][x+1] = true;
                if (1 <= i && i <= 4 && dst2 == 1) taken[y+1][x+1] = true;
                if (5 <= i && i <= 8 && dst2 == 2) taken[y+1][x+1] = true;
            }

            int score = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (taken[i][j]) score++; 
                }
            }
            return score;
        }

        void crossover(Individu ind1, Individu ind2) {
            for (int i = 0; i < 16; i++) {
                parameters[i] = (rand() % 2 == 0) ? ind1.parameters[i]: ind2.parameters[i];
            }
        }

        void mutation() {
            if (rand() % 100 < 20) {
                int p = rand() % 16;
                int k = (p % 2 == 0) ? 16 : 11;
                parameters[p] = rand() % k;
            }
        }
};

void selection(Individu population[16], int order[16]) {
    for (int i = 1; i < 16; ++i) {
        int key = order[i];
        Individu store = population[i];
        int j = i - 1;

        while (j >= 0 && order[j] > key) {
            order[j+1] = order[j];
            population[j+1] = population[j];
            j--;
        }
        order[j+1] = key;
        population[j+1] = store;
    }
}

int main() {
    srand(time(0));

    Individu population[16];
    for (int i = 0; i < 16; i++) {population[i].randomize();}
    int fitness_score[16] = {0};

    int gen = 0;
    while (gen < 100000) {
        for (int i = 0; i < 16; i++) {
            fitness_score[i] = population[i].fitness();
        }

        selection(population, fitness_score);

        if (fitness_score[15] >= 6) break;

        population[13].crossover(population[13], population[12]);
        population[12].crossover(population[13], population[11]);
        population[11].crossover(population[13], population[10]);
        population[10].crossover(population[12], population[11]);
        population[9].crossover(population[12], population[10]);
        population[8].crossover(population[11], population[10]);

        for (int i = 0; i < 8; i++) {population[i].randomize();}
        for (int i = 8; i < 16; i++) {population[i].mutation();}

        gen++;
    }

    cout << "Last Generation: " << gen << endl;

    Individu best = population[15];
    cout << best.fitness() << endl;
    cout << best.parameters[0] << ":" << best.parameters[1] << endl;
    cout << best.parameters[2] << ":" << best.parameters[3] << endl;
    cout << best.parameters[4] << ":" << best.parameters[5] << endl;
    cout << best.parameters[6] << ":" << best.parameters[7] << endl;
    return 0;
}