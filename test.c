#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void fill_buffer_freq (char *buf, int size, double freq) {
    int i = 0;
    uint32_t x = 0;
    double t = freq / 4800 * 2;
    for (i = 0, x = 0x00000000; i < size * 32; i++) {
        x = x << 1;
        if ((int) (i * t) % 2 == 0) {
            x++;
        }
        if ((i%32)==31) {
            *(buf++) = x;
            x = 0x00000000;
        }
    }
}

void do_write (char *destination, int size, int freq) {
    printf("Attempt to emit at frequency %d, size: %d\n", freq, size);
    FILE * fileP;
    fileP = fopen(destination, "wb");

    char *buffer;
    buffer = (char *) malloc (size);
    fill_buffer_freq(buffer, size, freq);

    fwrite(buffer, size, 1, fileP);
    fclose(fileP);
    printf("Write complete!\n");
}

int main (int argc, char *argv[]) {
    char *dest;
    dest = argv[3];
    int size = atoi(argv[2]);
    int freq = atoi(argv[1]);


    int sleep_time = 1000 * 1000;

    /* unit: mhz * 100 */
    /* for (;;) { */
        do_write(dest, size, freq);
        usleep(sleep_time);
    /* } */
}
