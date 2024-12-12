#include <iostream>
using namespace std;

int remove_useless(int bitmap) {
    if (bitmap & 16 && !(bitmap & 1 && bitmap & 2)) bitmap -= 16;
    if (bitmap & 32 && !(bitmap & 2 && bitmap & 4)) bitmap -= 32;
    if (bitmap & 64 && !(bitmap & 4 && bitmap & 8)) bitmap -= 64;
    if (bitmap & 128 && !(bitmap & 8 && bitmap & 1)) bitmap -= 128;
    return bitmap;
}

int main() {
    for (int i = 0; i < 256; i++) {
        int code = remove_useless(i);
        if (i != code) continue;

        int x =  (code & 3) | ((code & 48) >> 2);
        int y =  ((code & 12) >> 2) | ((code & 192) >> 4);

        // Caution send negative output value
        switch (x & 12) {
            case 12: x -= 8; break;
            case 8: x -= 5; break;
            case 4: x -= 3; break;
            default: break;
        }
        switch (y & 12) {
            case 12: y -= 8; break;
            case 8: y -= 5; break;
            case 4: y -= 3; break;
            default: break;
        }

        if (x == 7 || y == 7) {
            if ((y == 4 || y == 7) && (x == 4 || x == 7)) {
                x -= 2;
                y -= 2;
            } else {
                x -= 1;
                y -= 1;
            }
        }

        cout << i << " for " << x << "," << y << endl;
    }

    return 0;
}