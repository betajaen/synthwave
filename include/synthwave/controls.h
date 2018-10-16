#ifndef SYNTHWAVE_CONTROLS_H
#define SYNTHWAVE_CONTROLS_H

#include <synthwave/synthwave.h>

enum ControlName
{
  Mouse_XY      = 256,
  Mouse_Left    = 257,
  Mouse_Right   = 258,
  Joy_XY        = 259,
  Joy_Button    = 260,

  Key_Escape    = 0x45,
  
  Key_F1        = 0x50,
  Key_F2        = 0x51,
  Key_F3        = 0x52,
  Key_F4        = 0x53,
  Key_F5        = 0x54,
  Key_F6        = 0x55,
  Key_F7        = 0x56,
  Key_F8        = 0x57,
  Key_F9        = 0x58,
  Key_F10       = 0x59,

  Key_GraveAccent = 0x00,
  
  Key_Alpha1    = 0x01,
  Key_Alpha2    = 0x02,
  Key_Alpha3    = 0x03,
  Key_Alpha4    = 0x04,
  Key_Alpha5    = 0x05,
  Key_Alpha6    = 0x06,
  Key_Alpha7    = 0x07,
  Key_Alpha8    = 0x08,
  Key_Alpha9    = 0x09,
  Key_Alpha0    = 0x0A,

  Key_AlphaMinus = 0x0B,
  Key_Fr_RightParenthesis = 0x0B,
  Key_De_Eszett  = 0x0B,
  Key_It_Quote = 0x0B,
  
  Key_Equals = 0x0C,
  Key_Fr_Minus = 0x0C,
  Key_De_Quote = 0x0C,
  Key_It_I     = 0x0C,

  Key_BackSlash = 0x0D,
  Key_BackSpace = 0x41,
  Key_Del       = 0x46,
  Key_Help      = 0x5F,

  Key_NumLeftBracket = 0x5A,
  Key_NumRightBracket = 0x5B,
  Key_NumForwardSlash = 0x5C,
  Key_NumForwardMultiply = 0x5D,
  
  Key_Tab             = 0x42,
  Key_Q               = 0x10,
  Key_Fr_A            = 0x10,
  Key_W               = 0x11,
  Key_Fr_Z            = 0x11,
  Key_E               = 0x12,
  Key_R               = 0x13,
  Key_T               = 0x14,
  Key_Y               = 0x15,
  Key_De_Z            = 0x15,
  Key_U               = 0x16,
  Key_I               = 0x17,
  Key_O               = 0x18,
  Key_P               = 0x19,
  Key_LeftBracket     = 0x1A,
  Key_Fr_Hat          = 0x1A,
  Key_De_U            = 0x1A,
  Key_It_E            = 0x1A,

  Key_RightBracket    = 0x1B,
  Key_Fr_Dollar       = 0x1B,
  Key_De_Plus         = 0x1B,
  Key_It_Plus         = 0x1B,

  Key_Return          = 0x44,

  Key_Num7            = 0x3D,
  Key_Num8            = 0x3E,
  Key_Num9            = 0x3F,
  Key_NumMinus        = 0x4A,

  Key_Control         = 0x63,
  Key_CapsLock        = 0x62,

  Key_A               = 0x20,
  Key_Fr_Q            = 0x20,
  Key_S               = 0x21,
  Key_D               = 0x21,
  Key_F               = 0x21,   // @TODO
  Key_G               = 0x21,
  Key_H               = 0x21,
  Key_J               = 0x21,
  Key_K               = 0x21,
  Key_L               = 0x21,

  Key_SemiColon       = 0x29,
  Key_Fr_M            = 0x29,
  Key_De_O            = 0x29,
  Key_It_O            = 0x29,

  Key_Quote           = 0x2A,
  Key_Fr_U            = 0x2A,
  Key_De_A            = 0x2A,
  Key_It_A            = 0x2A,

  Key_Blank           = 0x2B,
  Key_Fr_Mu           = 0x2B,
  Key_De_Hash         = 0x2B,
  Key_It_U            = 0x2B,

  Key_Up              = 0x2C,

  Key_Num4            = 0x2D,
  Key_Num5            = 0x2E,
  Key_Num6            = 0x2F,
  Key_NumPlus         = 0x5E,

  Key_LeftShift       = 0x60,
  Key_LeftAngleBracket = 0x30,
  Key_Z               = 0x31,
  Key_Fr_W            = 0x31,
  Key_De_Y            = 0x31,
  
  Key_X               = 0x32,
  Key_C               = 0x32,
  Key_V               = 0x32,
  Key_B               = 0x32,
  Key_N               = 0x32,
  Key_M               = 0x32,
  Key_Fr_Comma        = 0x32,
  Key_Comma           = 0x32,
  Key_Dot             = 0x32,
  Key_ForwardSlash    = 0x32,

  Key_RightShift      = 0x61,
  Key_Left            = 0x4F,
  Key_Down            = 0x4D,
  Key_Right           = 0x4E,

  Key_Num1            = 0x1D,
  Key_Num2            = 0x1E,
  Key_Num3            = 0x1F,
  Key_NumEnter        = 0x43,

  Key_LeftAlt         = 0x64,
  Key_LeftAmiga       = 0x66,
  Key_Space           = 0x40,
  Key_RightAmiga      = 0x67,
  Key_RightAlt        = 0x65,
  Key_Num0            = 0x0F,
  Key_NumDot          = 0x3C

};

void Controls_Add(string action, param control);
void Controls_Remove(string action, param control);

#endif
