#pragma once

#include "Defines.h"

namespace ATGE
{
    static constexpr uint KeyStatesLength = 256;

    enum class KEY
    {
        KEY_SPACE = 0x20,
        KEY_APOSTROPHE = 0xDE,  /* ' */
        KEY_COMMA = 0xBC,  /* , */
        KEY_MINUS = 0xBD,  /* - */
        KEY_PERIOD = 0xBE,  /* . */
        KEY_SLASH = 0xBF,  /* / */
        KEY_0 = 0x30,
        KEY_1 = 0x31,
        KEY_2 = 0x32,
        KEY_3 = 0x33,
        KEY_4 = 0x34,
        KEY_5 = 0x35,
        KEY_6 = 0x36,
        KEY_7 = 0x37,
        KEY_8 = 0x38,
        KEY_9 = 0x39,
        KEY_SEMICOLON = 0xBA,  /* ; */
        KEY_A = 0x41,
        KEY_B = 0x42,
        KEY_C = 0x43,
        KEY_D = 0x44,
        KEY_E = 0x45,
        KEY_F = 0x46,
        KEY_G = 0x47,
        KEY_H = 0x48,
        KEY_I = 0x49,
        KEY_J = 0x4A,
        KEY_K = 0x4B,
        KEY_L = 0x4C,
        KEY_M = 0x4D,
        KEY_N = 0x4E,
        KEY_O = 0x4F,
        KEY_P = 0x50,
        KEY_Q = 0x51,
        KEY_R = 0x52,
        KEY_S = 0x53,
        KEY_T = 0x54,
        KEY_U = 0x55,
        KEY_V = 0x56,
        KEY_W = 0x57,
        KEY_X = 0x58,
        KEY_Y = 0x59,
        KEY_Z = 0x5A,
        KEY_LEFT_BRACKET = 0xDB,  /* [ */
        KEY_BACKSLASH = 0xDC,  /* \ */
        KEY_RIGHT_BRACKET = 0xDD,  /* ] */
        KEY_GRAVE_ACCENT = 0xC0,  /* ` */

        KEY_ARROW_UP = 0x26,
        KEY_ARROW_DOWN = 0x28,
        KEY_ARROW_LEFT = 0x25,
        KEY_ARROW_RIGHT = 0x27,

        // Function keys
        KEY_ESCAPE = 0x1B,
        KEY_ENTER = 0x0D,
        KEY_TAB = 0x09,
        KEY_BACKSPACE = 0x08,
        KEY_INSERT = 0x2D,
        KEY_DELETE = 0x2E,
        KEY_PAGE_UP = 0x21,
        KEY_PAGE_DOWN = 0x22,
        KEY_HOME = 0x24,
        KEY_END = 0x23,
        KEY_CAPS_LOCK = 0x14,
        KEY_SCROLL_LOCK = 0x91,
        KEY_NUM_LOCK = 0x90,
        KEY_PAUSE = 0x13,
        KEY_F1 = 0x70,
        KEY_F2 = 0x71,
        KEY_F3 = 0x72,
        KEY_F4 = 0x73,
        KEY_F5 = 0x74,
        KEY_F6 = 0x75,
        KEY_F7 = 0x76,
        KEY_F8 = 0x77,
        KEY_F9 = 0x78,
        KEY_F10 = 0x79,
        KEY_F11 = 0x7A,
        KEY_F12 = 0x7B,
        KEY_F13 = 0x7C,
        KEY_F14 = 0x7D,
        KEY_F15 = 0x7E,
        KEY_F16 = 0x7F,   
        KEY_F17 = 0x80,   
        KEY_F18 = 0x81,   
        KEY_F19 = 0x82,   
        KEY_F20 = 0x83,   
        KEY_F21 = 0x84,   
        KEY_F22 = 0x85,   
        KEY_F23 = 0x86,   
        KEY_F24 = 0x87,   

        KEY_KP_0 = 0x60,  
        KEY_KP_1 = 0x61,  
        KEY_KP_2 = 0x62,  
        KEY_KP_3 = 0x63,  
        KEY_KP_4 = 0x64,  
        KEY_KP_5 = 0x65,  
        KEY_KP_6 = 0x66,  
        KEY_KP_7 = 0x67,  
        KEY_KP_8 = 0x68,  
        KEY_KP_9 = 0x69,  

        KEY_KP_DECIMAL = 0x6E,  
        KEY_KP_DIVIDE = 0x6F,   
        KEY_KP_MULTIPLY = 0x6A, 
        KEY_KP_SUBTRACT = 0x6D, 
        KEY_KP_ADD = 0x6B,   

        KEY_LEFT_SHIFT = 0x10,
        KEY_LEFT_CONTROL = 0x11,
        KEY_LEFT_ALT = 0xA4,        
        KEY_RIGHT_SHIFT = 0xA1,     
        KEY_RIGHT_CONTROL = 0xA3,   
        KEY_RIGHT_ALT = 0xA5,       
        KEY_MENU = 0x12             
    };
}
