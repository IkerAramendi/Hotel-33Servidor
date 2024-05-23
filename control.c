#include <stdint.h>
#include <stdio.h>
#include "ws2811.h"

#define LED_COUNT 8
#define TARGET_FREQ WS2811_TARGET_FREQ
#define GPIO_PIN 18
#define DMA 10

ws2811_t ledstring = {
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel = {
        [0] = {
            .gpionum = GPIO_PIN,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
        },
    },
};

void set_led_color(int index, uint32_t color) {
    ledstring.channel[0].leds[index] = color;
}

int main() {
    if (ws2811_init(&ledstring)) {
        printf("Error initializing\n");
        return -1;
    }

    for (int i = 0; i < LED_COUNT; i++) {
        set_led_color(i, 0x00200000);  // Red color
    }

    if (ws2811_render(&ledstring)) {
        printf("Error rendering\n");
        return -1;
    }

    ws2811_fini(&ledstring);
    return 0;
}