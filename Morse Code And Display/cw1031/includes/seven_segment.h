/* Seven-segment display (5161BS) */
// http://www.xlitx.com/datasheet/5161BS.pdf

// (Raspberry Pi Pico pinout: https://datasheets.raspberrypi.com/pico/Pico-R3-A4-Pinout.pdf)

#pragma once

/** Top-center horizontal bar. */
#define SEGMENT_A            7  // Pin 10 (GPIO 07)

/** Top-right vertical bar */
#define SEGMENT_B            6  // Pin 09 (GPIO 06)

/** Bottom-right vertical bar */
#define SEGMENT_C           20  // Pin 26 (GPIO 20)

/** Bottom-center horizontal bar */
#define SEGMENT_D           19  // Pin 25 (GPIO 19)

/** Bottom-left vertical bar */
#define SEGMENT_E           18  // Pin 24 (GPIO 18)

/** Top-left vertical bar */
#define SEGMENT_F            8  // Pin 11 (GPIO 08)

/** Center horizontal bar */
#define SEGMENT_G            9  // Pin 12 (GPIO 09)

/** An array containing the pins for all segments. */
static const unsigned int ALL_SEGMENTS[] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G};

#define ALL_SEGMENTS_COUNT  7

// You will need to extend the array to include more letters.
uint8_t values[] = {
    0b11111100,        // 0
    0b01100000,        // 1
    0b11011010,        // 2
    0b11110010,        // 3
    0b01100110,        // 4
    0b10110110,        // 5
    0b10111110,        // 6
    0b11100000,        // 7
    0b11111110,        // 8
    0b11110110,        // 9
    0b11101110,        // A
    0b00111110,        // B
    0b10011100,        // C
    0b01111010,        // D
    0b10011110,        // E
    0b10001110,        // F
    0b11110110,        // G
    0b01101110,        // H
    0b00001100,        // I
    0b01111000,        // J
    0b01101110,        // K
    0b00011100,        // L
    0b10101000,        // M
    0b00101010,        // N
    0b11111100,        // O
    0b11001110,        // P
    0b11100110,        // Q
    0b00001010,        // R
    0b10110110,        // S
    0b00011110,        // T
    0b01111100,        // U
    0b00111000,        // V
    0b01010100,        // W
    0b01101110,        // X
    0b01110110,        // Y
    0b11011010         // Z
};

char morse_codes[][5] = {
    "-----",        //0
    "*----",        //1
    "**---",        //2
    "***--",        //3
    "****-",        //4
    "*****",        //5
    "-****",        //6
    "--***",        //7
    "---**",        //8
    "----*",        //9 
    "*-",           //A
    "-***",         //B
    "-*-*",         //C
    "-**",          //D
    "*",            //E
    "**-*",         //F
    "--*",          //G
    "****",         //H
    "**",           //I
    "*---",         //J
    "-*-",          //K
    "*-**",         //L
    "--",           //M
    "-*",           //N
    "---",          //O
    "*--*",         //P
    "--*-",         //Q
    "*-*",          //R
    "***",          //S
    "-",            //T
    "**-",          //U
    "***-",         //V
    "*--",          //W
    "-**-",         //X
    "-*--",         //Y
    "--**"          //Z
};


/* Initialise the GPIO pins for the seven-segment display. */
void seven_segment_init() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_init(ALL_SEGMENTS[i]);
        gpio_set_dir(ALL_SEGMENTS[i], GPIO_OUT);
    }    
}

/* Turn off the seven-segment display. */
void seven_segment_off() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], true);
    }
}

void seven_segment_on() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], false);
    }
}

void seven_segment_show(unsigned int number) {
    for (unsigned int i = 0; i < 7; i++) {
        unsigned int segmentBit = 1 << (7 - i);
        bool illuminateSegment = (segmentBit & values[number]);

        gpio_put(
            ALL_SEGMENTS[i],
            !illuminateSegment
        );
    }
}

void loopButtonTest(){
	timer_hw->dbgpause = 0;
	seven_segment_on();
	sleep_ms(1000);
	seven_segment_off();
	sleep_ms(1000);
	int i;
	// display the numbers from 0 to z in a loop
	for(i = 0; i < 36; i++){
		seven_segment_show(i);
		sleep_ms(100);
		seven_segment_off();
		sleep_ms(50);
	}
}