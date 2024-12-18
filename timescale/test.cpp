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
    default:
        return 0;
        break;
    }
}

int main() {
    int offset[9][2] = {
        {0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
        };
    


    for (int p1 = 0; p1 < 6; p1++) {
        for (int p2 = 0; p2 < 8; p2++) {
            for (int p3 = 0; p3 < 6; p3++) {
                for (int p4 = 0; p4 < 8; p4++) {
                    for (int p5 = 0; p5 < 6; p5++) {
                        for (int p6 = 0; p6 < 8; p6++) {
                            for (int p7 = 0; p7 < 6; p7++) {
                                for (int p8 = 0; p8 < 8; p8++) {

                                    bool good = true;
                                    for (int i = 0; i < 8; i++) {
                                        int x = operation(operation(i, p2, p1), p6, p5);
                                        int y = operation(operation(i, p4, p3), p8, p7);

                                        if (x != offset[i][0] || y != offset[i][1]) {good = false; break;}
                                    }
                                    if (good) cout << p1 << "," << p2 << "," << p3 << "," << p4 << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}