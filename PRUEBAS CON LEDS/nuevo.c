
#include "sqlite3.h"
//#include "rpi_ws281x/WS281x.h"

#include "clk.h"
#include "dma.h"
#include "gpio.h"
#include "pwm.h"
#include "version.h"

#include "ws2811.h"


void controlarLeds(WS281x &leds, int red, int green, int blue) {
    // Configurar todos los LEDs con el mismo color
    for (int i = 0; i < leds.numPixels(); i++) {
        leds.setPixelColor(i, leds.Color(red, green, blue));
    }
    leds.show();
}

int main(){
 WS281x leds;
    leds.begin();

            controlarLeds(leds, 255, 0, 0); // Rojo
            delay(5000); // Esperar 5 segundos
            controlarLeds(leds, 0, 255, 0); // Verde
            delay(5000); // Esperar 5 segundos
            controlarLeds(leds, 255, 255, 255); // Blanco
            delay(5000); // Esperar 5 segundos


return 0;
}