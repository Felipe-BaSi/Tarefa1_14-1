#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_blue 20

const uint rows[4] = {1, 2, 3, 4};
const uint columns[4] = {5, 6, 7, 8};

char teclas[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void pico_keypad_init() {
    for (int i = 0; i < 4; i++) {
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_OUT);
        gpio_put(rows[i], 0);
    }

    for (int j = 0; j < 4; j++) {
        gpio_init(columns[j]);
        gpio_set_dir(columns[j], GPIO_IN);
        gpio_pull_down(columns[j]);
    }
}

char pico_keypad_get_key() {
    for (int row = 0; row < 4; row++) {
        gpio_put(rows[row], 1);

        for (int col = 0; col < 4; col++) {
            if (gpio_get(columns[col])) {
                busy_wait_ms(50);
                while (gpio_get(columns[col]));
                gpio_put(rows[row], 0);
                return teclas[row][col];
            }
        }

        gpio_put(rows[row], 0);
    }

    return 0;
}

int main() {
    stdio_init_all();
    pico_keypad_init();

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    char caracter_press;

    while (1) {

        caracter_press = pico_keypad_get_key();

        if(caracter_press){

          printf("\nTecla pressionada: %c\n", caracter_press);
          
        }

        switch(caracter_press){

          case 'A':

              if(gpio_get(led_pin_blue) == 0){

                gpio_put(led_pin_blue, 1);

              } else {
                gpio_put(led_pin_blue, 0);
              }
              
              break;
        }

    busy_wait_us(100);
    }
}