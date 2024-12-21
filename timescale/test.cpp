#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

int operation(int value, int value2, int index) {
    switch (index) {
    case 0:
        return value | value2;
    case 1:
        return value & value2;
    case 2:
        return value ^ value2;
    case 3:
        return ~value;
    case 4:
        return value << value2;
    case 5:
        return value >> value2;
    case 6:
        return value;
    case 7:
        return -value;
    case 8:
        return value+value2;
    case 9:
        return value-value2;
    case 10:
        return value*value2;
    case 11:
        if (value2 == 0) return 0x7FFFFFFF;
        return value/value2;
    default:
        return 0;
    }
}

class Individu {
    public:
        int parameters[16] = {0};
    
        void randomize() {
            int r;
            char sector;
            for (int i = 0; i < 16; i+=2) {
                sector = i % 4;
                if (sector == 0) {
                    r = rand();
                }
                parameters[i] = (r >> (sector*8)) & 15;
                parameters[i+1] = (r >> (sector*8+4)) & 15 % 11;
            }
        }

        int fitness() {
            bool taken[3][3] = {false};

            for (int i = 0; i < 9; i++) {
                int x = operation(i, parameters[0], parameters[1]) + operation(i, parameters[4], parameters[5]);
                int y = operation(i, parameters[2], parameters[3]) + operation(i, parameters[6], parameters[7]);
                int sx = x;
                x =  operation(x, parameters[8], parameters[9]) + operation(y, parameters[12], parameters[13]);
                y =  operation(y, parameters[10], parameters[11]) + operation(sx, parameters[14], parameters[15]);

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
            char r = rand() % 4;
            for (int i = 0; i < 16; i++) {
                parameters[i] = ((i+r) % 4 == 0 || (i-1+r) % 4) ? ind1.parameters[i]: ind2.parameters[i];
            }
        }

        void mutation() {
            if (rand() % 100 < 20) {
                int p = rand() % 16;
                int k = (p % 2 == 0) ? 16 : 11;
                parameters[p] = rand() % k;
            }
        }

        void show_order() {
            for (int i = 0; i < 9; i++) {
                int x = operation(operation(i, parameters[0], parameters[1]), parameters[2], parameters[3]);
                int y = operation(operation(i, parameters[4], parameters[5]), parameters[6], parameters[7]);
                x = operation(operation(x, parameters[8], parameters[9]), parameters[10], parameters[11]);
                y = operation(operation(y, parameters[12], parameters[13]), parameters[14], parameters[15]);

                cout << "(" << x << ", " << y << ")" << endl;
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
    int max_fitness = 0;
    while (gen < 100000) {
        for (int i = 0; i < 16; i++) {
            fitness_score[i] = population[i].fitness();
        }

        selection(population, fitness_score);

        if (fitness_score[15] > max_fitness) max_fitness = fitness_score[15];
        if (fitness_score[15] >= 6) break;

        int count = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i >= j) continue;
                population[count+4].crossover(population[i+9], population[j+9]);
                count++;
            }
        }

        for (int i = 0; i < 4; i++) {population[i].randomize();}
        for (int i = 4; i < 16; i++) {population[i].mutation();}

        gen++;
    }
    cout << endl;
    cout << "Last Generation: " << gen << endl;
    cout << "Best Fitness All Time: " << max_fitness << endl;

    Individu best = population[15];
    cout << "Last Best Individu: " << best.fitness() << endl;
    cout << endl;

    cout << "Parameters X:" << endl;
    cout << best.parameters[0] << ":" << best.parameters[1] << " ";
    cout << best.parameters[2] << ":" << best.parameters[3] << " ";
    cout << best.parameters[8] << ":" << best.parameters[9] << " ";
    cout << best.parameters[10] << ":" << best.parameters[11] << endl;
    cout << "Parameters Y:" << endl;
    cout << best.parameters[4] << ":" << best.parameters[5] << " ";
    cout << best.parameters[6] << ":" << best.parameters[7] << " ";
    cout << best.parameters[12] << ":" << best.parameters[13] << " ";
    cout << best.parameters[14] << ":" << best.parameters[15] << endl;

    //best.show_order();
    return 0;
}