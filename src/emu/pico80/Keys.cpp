#include "emu/pico80/Keys.h"

uint8_t mapQTkeyAlt(Qt::Key key)
{
	switch(key)
	{
	case Qt::Key_Q:
		return K_QUIT;
	case Qt::Key_M:
		return K_MODE;
	case Qt::Key_Minus:
		return K_NEGATIVE;
	default:
		return K_NONE;
	}
}

uint8_t mapQTkeyShift(Qt::Key key)
{
	switch(key)
	{
	default:
		return K_NONE;
	}
}

uint8_t mapQTkeyNone(Qt::Key key)
{
	switch(key)
	{
	case Qt::Key_F1:
		return K_F1;
	case Qt::Key_F2:
		return K_F2;
	case Qt::Key_F3:
		return K_F3;
	case Qt::Key_F4:
		return K_F4;
	case Qt::Key_F5:
		return K_F5;

	case Qt::Key_Down:
		return K_DOWN;
	case Qt::Key_Left:
		return K_LEFT;
	case Qt::Key_Right:
		return K_RIGHT;
	case Qt::Key_Up:
		return K_UP;

	case Qt::Key_Backspace:
		return K_BACKSPACE;
	case Qt::Key_Escape:
		return K_ESC;
	case Qt::Key_Shift:
		return K_SHIFT;
	case Qt::Key_Control:
		return K_CTRL;
	case Qt::Key_Space:
		return K_SPACE;
	case Qt::Key_Enter:
		return K_ENTER;

	case Qt::Key_Plus:
		return K_PLUS;
	case Qt::Key_Minus:
		return K_MINUS;
	case Qt::Key_Asterisk:
		return K_ASTERISK;
	case Qt::Key_Slash:
		return K_SLASH;
	case Qt::Key_Equal:
		return K_EQUALS;

	case Qt::Key_BracketLeft:
		return K_LBRACKET;
	case Qt::Key_BracketRight:
		return K_RBRACKET;
	case Qt::Key_BraceLeft:
		return K_LBRACE;
	case Qt::Key_BraceRight:
		return K_RBRACE;
	case Qt::Key_ParenLeft:
		return K_LPAREN;
	case Qt::Key_ParenRight:
		return K_RPAREN;

	case Qt::Key_Underscore:
		return K_UNDERSCORE;
	case Qt::Key_Question:
		return K_QUESTION;
	case Qt::Key_Period:
		return K_PERIOD;
	case Qt::Key_Comma:
		return K_COMMA;
	case Qt::Key_Exclam:
		return K_EXCLAM;
	case Qt::Key_Colon:
		return K_COLON;
	case Qt::Key_Delete:
		return K_DEL;
	case Qt::Key_Insert:
		return K_INS;
	case Qt::Key_QuoteDbl:
		return K_QUOTEDBL;
	case Qt::Key_Apostrophe:
		return K_QUOTE;

	default:
		if (Qt::Key_A <= key && key <= Qt::Key_Z)
			return key - (int) Qt::Key_A + K_a;
		else if (Qt::Key_0 <= key && key <= Qt::Key_9)
			return key - (int) Qt::Key_0 + K_0;

		return K_NONE;
	}
}

uint8_t mapQTKey(Qt::Key key, Qt::KeyboardModifiers mod)
{
	uint8_t k = K_NONE;
	if (mod & Qt::AltModifier)
		k = mapQTkeyAlt(key);
	if (k == K_NONE && (mod & Qt::ShiftModifier))
		k = mapQTkeyShift(key);
	if (k == K_NONE)
		k = mapQTkeyNone(key);
	return k;
}
