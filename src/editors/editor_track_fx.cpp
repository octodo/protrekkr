// ------------------------------------------------------
// Protrekkr
// Based on Juan Antonio Arguelles Rius's NoiseTrekker.
//
// Copyright (C) 2008-2010 Franck Charlet.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL FRANCK CHARLET OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
// ------------------------------------------------------

// ------------------------------------------------------
// Includes
#include "include/editor_track_fx.h"

// ------------------------------------------------------
// Variables
char fld_chan = FALSE;

// ------------------------------------------------------
// Functions
void Display_Compressor(void);

void Draw_Track_Fx_Ed(void)
{
    Draw_Editors_Bar(USER_SCREEN_TRACK_FX_EDIT);

    Gui_Draw_Button_Box(0, (Cur_Height - 153), fsize, 130, "", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Flat_Box("Track FX");

    Gui_Draw_Button_Box(4, (Cur_Height - 138), 228, 110, "", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_VTOP);

    Gui_Draw_Button_Box(8, (Cur_Height - 128), 64, 16, "Filter LFO", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(118, (Cur_Height - 128), 64, 16, "Flanger", BUTTON_NORMAL | BUTTON_DISABLED);

    Gui_Draw_Button_Box(8, (Cur_Height - 110), 64, 16, "Frequency", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(8, (Cur_Height - 92), 64, 16, "Amplitude", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(8, (Cur_Height - 74), 64, 16, "LFO Status", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(8, (Cur_Height - 56), 64, 16, "Flanger 3D", BUTTON_NORMAL | BUTTON_DISABLED);

    Gui_Draw_Button_Box(240, (Cur_Height - 138), 288, 110, "Flanger Settings", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_VTOP);
    Gui_Draw_Button_Box(248, (Cur_Height - 121), 56, 16, "Amount", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, (Cur_Height - 103), 56, 16, "Period", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, (Cur_Height - 85), 56, 16, "Amplitude", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, (Cur_Height - 67), 56, 16, "Feedback", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(248, (Cur_Height - 49), 56, 16, "Delay", BUTTON_NORMAL | BUTTON_DISABLED);

    Gui_Draw_Button_Box(536, (Cur_Height - 138), 144, 76, "Compressor", BUTTON_NORMAL | BUTTON_DISABLED | BUTTON_TEXT_VTOP);
    Gui_Draw_Button_Box(544, (Cur_Height - 121), 56, 16, "Active", BUTTON_NORMAL | BUTTON_DISABLED);
}

void Actualize_Track_Fx_Ed(char gode)
{
    if(userscreen == USER_SCREEN_TRACK_FX_EDIT)
    {
        if(gode == 0 || gode == 1 || gode == 11)
        {
            if(FLANGER_AMOUNT[Track_Under_Caret] > 1.0f) FLANGER_AMOUNT[Track_Under_Caret] = 1.0f;
            if(FLANGER_AMOUNT[Track_Under_Caret] < -1.0f) FLANGER_AMOUNT[Track_Under_Caret] = -1.0f;
            Realslider(308, (Cur_Height - 121), 64 + (int) (FLANGER_AMOUNT[Track_Under_Caret] * 64.0f), FLANGER_ON[Track_Under_Caret]);
            outlong(458, (Cur_Height - 121), long(FLANGER_AMOUNT[Track_Under_Caret] * 100.0f), 1);
        }

        if(gode == 0 || gode == 7 || gode == 11)
        {
            if(FLANGER_FEEDBACK[Track_Under_Caret] > 1.0f) FLANGER_FEEDBACK[Track_Under_Caret] = 1.0f;
            if(FLANGER_FEEDBACK[Track_Under_Caret] < -1.0f) FLANGER_FEEDBACK[Track_Under_Caret] = -1.0f;
            Realslider(308, (Cur_Height - 67), 64 + (int) (FLANGER_FEEDBACK[Track_Under_Caret] * 64.0f), FLANGER_ON[Track_Under_Caret]);
            outlong(458, (Cur_Height - 67), long(FLANGER_FEEDBACK[Track_Under_Caret] * 100.0f), 1);
        }

        if(gode == 0 || gode == 4 || gode == 11)
        {
            if(FLANGER_DEPHASE[Track_Under_Caret] > 3.1415927f) FLANGER_DEPHASE[Track_Under_Caret] = 3.1415927f;
            if(FLANGER_DEPHASE[Track_Under_Caret] < 0.0f) FLANGER_DEPHASE[Track_Under_Caret] = 0.0f;
            Realslider2(74, (Cur_Height - 56), (int) (FLANGER_DEPHASE[Track_Under_Caret] * 20.371833f), FLANGER_ON[Track_Under_Caret]);
            outlong(159, (Cur_Height - 56), (int) (FLANGER_DEPHASE[Track_Under_Caret] * 57.29578f), 6);
        }

        if(gode == 0 || gode == 5 || gode == 11)
        {
            if(FLANGER_RATE[Track_Under_Caret] < 0.000001f) FLANGER_RATE[Track_Under_Caret] = 0.000001f;
            if(FLANGER_RATE[Track_Under_Caret] > 0.0001363f) FLANGER_RATE[Track_Under_Caret] = 0.0001363f;
            Realslider(308, (Cur_Height - 103), (int) (FLANGER_RATE[Track_Under_Caret] * 939104.92f), FLANGER_ON[Track_Under_Caret]);
            outlong(458, (Cur_Height - 103), long(0.1424758f / FLANGER_RATE[Track_Under_Caret]), 2);
        }

        if(gode == 0 || gode == 6 || gode == 11)
        {
            if(FLANGER_AMPL[Track_Under_Caret] > 0.01f) FLANGER_AMPL[Track_Under_Caret] = 0.01f;
            if(FLANGER_AMPL[Track_Under_Caret] < 0.0f) FLANGER_AMPL[Track_Under_Caret] = 0.0f;
            Realslider(308, (Cur_Height - 85), (int) (FLANGER_AMPL[Track_Under_Caret] * 12800.0f), FLANGER_ON[Track_Under_Caret]);
            outlong(458, (Cur_Height - 85), (int) (FLANGER_AMPL[Track_Under_Caret] * 10000.0f), 1);
        }

        if(gode == 0 || gode == 2)
        {
            if(LFO_RATE[Track_Under_Caret] < 0.0001f) LFO_RATE[Track_Under_Caret] = 0.0001f;
            if(LFO_RATE[Track_Under_Caret] > 0.0078125f) LFO_RATE[Track_Under_Caret] = 0.0078125f;
            Realslider(74, (Cur_Height - 110), (int) (LFO_RATE[Track_Under_Caret] * 16384.0f), LFO_ON[Track_Under_Caret]);
            float tmprate = (8.1632653f / LFO_RATE[Track_Under_Caret]);
            outlong(76, (Cur_Height - 74), (long) tmprate, 2);
            tmprate = 1000.0f / tmprate;
            outfloat(138, (Cur_Height - 74), tmprate, 3);
        }

        if(gode == 0 || gode == 3)
        {
            if(LFO_AMPL[Track_Under_Caret] < 0) LFO_AMPL[Track_Under_Caret] = 0;
            if(LFO_AMPL[Track_Under_Caret] > 128) LFO_AMPL[Track_Under_Caret] = 128;
            Realslider(74, (Cur_Height - 92), (int) (LFO_AMPL[Track_Under_Caret]), LFO_ON[Track_Under_Caret]);
        }

        if(gode == 0 || gode == 9)
        {
            if(LFO_ON[Track_Under_Caret] == 1)
            {
                Gui_Draw_Button_Box(74, (Cur_Height - 128), 20, 16, "On", BUTTON_PUSHED);
                Gui_Draw_Button_Box(96, (Cur_Height - 128), 20, 16, "Off", BUTTON_NORMAL);
            }
            else
            {
                Gui_Draw_Button_Box(74, (Cur_Height - 128), 20, 16, "On", BUTTON_NORMAL);
                Gui_Draw_Button_Box(96, (Cur_Height - 128), 20, 16, "Off", BUTTON_PUSHED);
            }
        }

        if(gode == 0 || gode == 10 || gode == 11)
        {
            if(FLANGER_ON[Track_Under_Caret])
            {
                Gui_Draw_Button_Box(184, (Cur_Height - 128), 20, 16, "On", BUTTON_PUSHED);
                Gui_Draw_Button_Box(206, (Cur_Height - 128), 20, 16, "Off", BUTTON_NORMAL);
            }
            else
            {
                Gui_Draw_Button_Box(184, (Cur_Height - 128), 20, 16, "On", BUTTON_NORMAL);
                Gui_Draw_Button_Box(206, (Cur_Height - 128), 20, 16, "Off", BUTTON_PUSHED);
            }
        }

        if(gode == 0 || gode == 8 || gode == 11)
        {
            if(FLANGER_DELAY[Track_Under_Caret] > 4096) FLANGER_DELAY[Track_Under_Caret] = 4096;
            if(FLANGER_DELAY[Track_Under_Caret] < 0) FLANGER_DELAY[Track_Under_Caret] = 0;
            if(fld_chan == TRUE)
            {
                FLANGER_OFFSET[Track_Under_Caret] = 8192;
                FLANGER_OFFSET2[Track_Under_Caret] = float(FLANGER_OFFSET[Track_Under_Caret] - FLANGER_DELAY[Track_Under_Caret]);
                FLANGER_OFFSET1[Track_Under_Caret] = float(FLANGER_OFFSET[Track_Under_Caret] - FLANGER_DELAY[Track_Under_Caret]);  
                fld_chan = FALSE;
            }
            Realslider(308, (Cur_Height - 49), FLANGER_DELAY[Track_Under_Caret] / 32, FLANGER_ON[Track_Under_Caret]);
            outlong(458, (Cur_Height - 49), long(FLANGER_DELAY[Track_Under_Caret] / 44.1f), 2);
        }

        if(gode == 0 || gode == 12)
        {
            if(Compress_Track[Track_Under_Caret])
            {
                Gui_Draw_Button_Box(602, (Cur_Height - 121), 20, 16, "On", BUTTON_PUSHED);
                Gui_Draw_Button_Box(624, (Cur_Height - 121), 20, 16, "Off", BUTTON_NORMAL);
            }
            else
            {
                Gui_Draw_Button_Box(602, (Cur_Height - 121), 20, 16, "On", BUTTON_NORMAL);
                Gui_Draw_Button_Box(624, (Cur_Height - 121), 20, 16, "Off", BUTTON_PUSHED);
            }
        }

        if(gode == 0 || gode == 12)
        {
            Display_Compressor();
        }

    }//User gui screen match
}

void Mouse_Sliders_Track_Fx_Ed(void)
{
    if(userscreen == USER_SCREEN_TRACK_FX_EDIT)
    {
        if(zcheckMouse(74, (Cur_Height - 110), 148, 16) && LFO_ON[Track_Under_Caret])
        {
            LFO_RATE[Track_Under_Caret] = (Mouse.x - 84) / 16384.0f;
            teac = 2;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
        }
        if(zcheckMouse(74, (Cur_Height - 92), 148, 16) && LFO_ON[Track_Under_Caret])
        {
            LFO_AMPL[Track_Under_Caret] = float(Mouse.x - 84);
            teac = 3;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
        }
        if(zcheckMouse(74, (Cur_Height - 56), 148, 16) && FLANGER_ON[Track_Under_Caret])
        {
            FLANGER_DEPHASE[Track_Under_Caret] = (Mouse.x - 84) * 0.0490873f;
            teac = 4;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 4;
        }

        if(zcheckMouse(308, (Cur_Height - 121), 148, 16) && FLANGER_ON[Track_Under_Caret])
        {
            teac = 1;
            FLANGER_AMOUNT[Track_Under_Caret] = ((Mouse.x - 318.0f) / 64.0f) - 1.0f;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
        }
        if(zcheckMouse(308, (Cur_Height - 103), 148, 16) && FLANGER_ON[Track_Under_Caret])
        {
            FLANGER_RATE[Track_Under_Caret] = (Mouse.x - 318.0f) / 939104.92f;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 5;
        }
        if(zcheckMouse(308, (Cur_Height - 85), 148, 16) && FLANGER_ON[Track_Under_Caret])
        {
            FLANGER_AMPL[Track_Under_Caret] = (Mouse.x - 318.0f) / 12800.0f;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 6;
        }
        if(zcheckMouse(308, (Cur_Height - 67), 148, 16) && FLANGER_ON[Track_Under_Caret])
        {
            FLANGER_FEEDBACK[Track_Under_Caret] = ((Mouse.x - 318) / 64.0f) - 1.0f;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 7;
        }
        if(zcheckMouse(308, (Cur_Height - 49), 148, 16) && FLANGER_ON[Track_Under_Caret])
        {
            FLANGER_DELAY[Track_Under_Caret] = (Mouse.x - 318) * 32;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            fld_chan = TRUE;
            teac = 8;
        }

        // Compressor threshold
        if(zcheckMouse(602, (Cur_Height - 103), 67, 18))
        {
            Mas_Compressor_Set_Variables_Track(Track_Under_Caret,
                                               (Mouse.x - 612.0f) * 2.0f,
                                                mas_comp_ratio_Track[Track_Under_Caret]);
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 12;
        }

        // Compressor ratio
        if(zcheckMouse(602, (Cur_Height - 85), 67, 18))
        {
            Mas_Compressor_Set_Variables_Track(Track_Under_Caret,
                                               mas_comp_threshold_Track[Track_Under_Caret],
                                               (Mouse.x - 612.0f) * 2.0f);
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 12;
        }

    }
}

void Mouse_Left_Track_Fx_Ed(void)
{
    if(userscreen == USER_SCREEN_TRACK_FX_EDIT)
    {
        if(zcheckMouse(74, (Cur_Height - 128), 20, 16) && LFO_ON[Track_Under_Caret] == FALSE)
        {
            LFO_ON[Track_Under_Caret] = TRUE;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 0;
        }
        if(zcheckMouse(96, (Cur_Height - 128), 20, 16) && LFO_ON[Track_Under_Caret] == TRUE)
        {
            LFO_ON[Track_Under_Caret] = FALSE;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 0;
        }
        if(zcheckMouse(184, (Cur_Height - 128), 20, 16) && FLANGER_ON[Track_Under_Caret] == FALSE)
        {
            FLANGER_ON[Track_Under_Caret] = TRUE;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 0;
        }
        if(zcheckMouse(206, (Cur_Height - 128), 20, 16) && FLANGER_ON[Track_Under_Caret])
        {
            FLANGER_ON[Track_Under_Caret] = FALSE;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 0;
        }

        if(zcheckMouse(602, (Cur_Height - 121), 20, 16) && Compress_Track[Track_Under_Caret] == FALSE)
        {
            Compress_Track[Track_Under_Caret] = TRUE;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 0;
        }
        if(zcheckMouse(624, (Cur_Height - 121), 20, 16) && Compress_Track[Track_Under_Caret])
        {
            Compress_Track[Track_Under_Caret] = FALSE;
            gui_action = GUI_CMD_UPDATE_TRACK_FX_ED;
            teac = 0;
        }
    }
}

// ------------------------------------------------------
// Display compressor sliders
void Display_Compressor(void)
{
    char string[64];

    Gui_Draw_Button_Box(544, (Cur_Height - 103), 56, 16, "Threshold", BUTTON_NORMAL | BUTTON_DISABLED);
    Realslider_Size(601, (Cur_Height - 103), 50, (int) (mas_comp_threshold_Track[Track_Under_Caret] * 0.5f), Compress_Track[Track_Under_Caret] ? TRUE : FALSE);
    sprintf(string, "%d%%", (int) (mas_comp_threshold_Track[Track_Under_Caret]));
    Print_String(string, 601, (Cur_Height - 101), 67, BUTTON_TEXT_CENTERED);

    Gui_Draw_Button_Box(544, (Cur_Height - 85), 56, 16, "Ratio", BUTTON_NORMAL | BUTTON_DISABLED);
    Realslider_Size(601, (Cur_Height - 85), 50, (int) (mas_comp_ratio_Track[Track_Under_Caret] * 0.5f), Compress_Track[Track_Under_Caret] ? TRUE : FALSE);
    sprintf(string, "%d%%", (int) (mas_comp_ratio_Track[Track_Under_Caret]));
    Print_String(string, 601, (Cur_Height - 83), 67, BUTTON_TEXT_CENTERED);
}
