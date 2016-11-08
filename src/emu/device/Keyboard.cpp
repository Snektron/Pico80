#include "emu/device/Keyboard.h"
#include "emu/device/Keys.h"
#include "core/Keys.h"

uint8_t Keyboard::read()
{
	return 0;
}

uint8_t KeyModifiers::read()
{
	return 0;
}

uint8_t KeyPad::read()
{
	return mapKos(0, 0);
}

uint8_t KeyPad::mapKos(uint8_t key, uint8_t mod)
{
	switch(key)
	{
	case K_F1: return kF1;
	case K_F2: return kF2;
	case K_F3: return kF3;
	case K_F4: return kF4;
	case K_F5: return kF5;

	case K_DOWN: return kDown;
	case K_LEFT: return kLeft;
	case K_RIGHT: return kRight;
	case K_UP: return kUp;

	case K_BACKSPACE: return kXTThetaN;
	case K_ESC: return kClear;
	case K_SHIFT: return kAlpha;
	case K_CTRL: return k2nd;
	case K_SPACE: return kSpace;
	case K_ENTER: return kEnter;

	case K_A: case K_a: return kA;
	case K_B: case K_b: return kB;
	case K_C: case K_c: return kC;
	case K_D: case K_d: return kD;
	case K_E: case K_e: return mod & KM_ALT ? kVarE : kE;
	case K_F: case K_f: return kF;
	case K_G: case K_g: return kG;
	case K_H: case K_h: return kH;
	case K_I: case K_i: return kI;
	case K_J: case K_j: return kJ;
	case K_K: case K_k: return kK;
	case K_L: case K_l: return kL;
	case K_M: case K_m: return kM;
	case K_N: case K_n: return kN;
	case K_O: case K_o: return kO;
	case K_P: case K_p: return mod & KM_ALT ? kPi : kP;
	case K_Q: case K_q: return kQ;
	case K_R: case K_r: return kR;
	case K_S: case K_s: return kS;
	case K_T: case K_t: return kT;
	case K_U: case K_u: return kU;
	case K_V: case K_v: return kV;
	case K_W: case K_w: return kW;
	case K_X: case K_x: return kX;
	case K_Y: case K_y: return kY;
	case K_Z: case K_z: return kZ;

	case K_LBRACE: return kLBrace;
	case K_RBRACE: return kRBrace;
	case K_LBRACKET: return kLSqBracket;
	case K_RBRACKET: return kRSqBracket;
	case K_LPAREN: return kLParen;
	case K_RPAREN: return kRParen;

	case K_0: return k0;
	case K_1: return k1;
	case K_2: return k2;
	case K_3: return k3;
	case K_4: return k4;
	case K_5: return k5;
	case K_6: return k6;
	case K_7: return k7;
	case K_8: return k8;
	case K_9: return k9;

	case K_PLUS: return kPlus;
	case K_MINUS: return kMinus;
	case K_ASTERISK: return kMul;
	case K_SLASH: return kDiv;
	case K_NEGATIVE: return kNeg;
	case K_EQUALS: return kStore;

	case K_UNDERSCORE: return k0; // no underscore defined :(
	case K_QUESTION: return kQuestion;
	case K_PERIOD: return kPeriod;
	case K_COMMA: return kComma;
//	case K_EXCLAIM: return;
	case K_COLON: return kColon;
	case K_INS: return kIns;
	case K_DEL: return kDel;
	case K_QUOTEDBL: return kQuote;
//	case K_QUOTE: return;

	case K_QUIT: return kQuit;
	case K_MODE: return kMode;

	default:
		return 0;
	}
}
