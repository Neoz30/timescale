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
        return value/value2;
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
                parameters[i] = rand() % 16;
            }
            for (int i = 1; i < 8; i+=2) {
                parameters[i] = rand() % 12;
            }
        }

        int fitness() {
            int score = 0;
            for (int i = 0; i < 9; i++) {
                int x = operation(operation(i, parameters[0], parameters[1]), parameters[2], parameters[3]);
                int y = operation(operation(i, parameters[4], parameters[5]), parameters[6], parameters[7]);

                int dst2 = x*x + y*y;

                if (i == 0 && dst2 == 0) score++;
                if (1 <= i && i <= 4 && dst2 == 1) score++;
                if (5 <= i && i <= 8 &&  dst2 == 2) score++;
            }
            return score;
        }

        void crossover(Individu ind1, Individu ind2) {
            for (int i = 0; i < 16; i++) {
                parameters[i] = (rand() % 2 == 0) ? ind1.parameters[i]: ind2.parameters[i];
            }
        }

        void mutation() {
            if (rand() % 100 < 60) {
                parameters[rand() % 4 * 2] = rand() % 16;
                parameters[rand() % 4 * 2 + 1] = rand() % 12;
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
    while (gen < 10000) {
        cout << gen << endl;
        for (int i = 0; i < 16; i++) {
            fitness_score[i] = population[i].fitness();
        }

        selection(population, fitness_score);

        if (fitness_score[15] == 9) break;

        /*population[2].crossover(population[2], population[3]);
        population[3].crossover(population[2], population[4]);
        population[4].crossover(population[2], population[5]);
        population[5].crossover(population[3], population[4]);
        population[6].crossover(population[3], population[5]);
        population[7].crossover(population[4], population[5]);*/

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