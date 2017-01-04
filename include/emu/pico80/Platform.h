#define PORT_LOG_OUT 0

#define PORT_MEM_BANK_A 1
#define PORT_MEM_BANK_B 2
#define PORT_MEM_BANK_C 3

#define PORT_INT_MASK 4
#define PORT_INT_TRIG 5
#define INT_TIMER 0
#define INT_ON 1

#define PORT_SCRN_CMD 6
#define PORT_SCRN_ARG0 7
#define PORT_SCRN_ARG1 8
#define PORT_SCRN_ARG2 9
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define PORT_MOUSE_X 10
#define PORT_MOUSE_Y 11
#define PORT_MOUSE_BTN 12
#define MOUSE_BTN_LEFT 0
#define MOUSE_BTN_RIGHT 1
#define MOUSE_MASK(btn) (1 << (btn))

#define PORT_STORAGE_CTRL 13

#define PORT_KEYBOARD 14
#define PORT_KEYPAD 15
#define PORT_KEYMOD 16

#define PORT_CLOCKREG1 17
#define PORT_CLOCKREG2 18
#define PORT_CLOCKREG3 19
#define PORT_CLOCKREG4 20