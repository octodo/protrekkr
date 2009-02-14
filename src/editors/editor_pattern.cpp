// ------------------------------------------------------
// Protrekkr
// Written by Franck Charlet
// Based on the work of Juan Antonio Arguelles Rius 
// ------------------------------------------------------

// ------------------------------------------------------
// Includes
#include "include/editor_pattern.h"
#include "include/editor_diskio.h"
#include "../support/include/timer.h"

// ------------------------------------------------------
// Variables
int VIEWLINE = 15; // BOOKMARK
int VIEWLINE2 = -13;
int YVIEW = 300; 
char is_editing = 0;
char is_recording = 0;
char is_recording_2 = 0;
char is_record_key = 0;

// Min 1 Max 16
int patt_highlight = 4;
int Continuous_Scroll;

MARKER Patterns_Marker;

int ped_pattad = 1;
int ped_patoct = 4;

char sr_isrecording = 0;

#define HIGH_COLOR_NOTE 0
#define HIGH_COLOR_INSTRUMENT_1 1
#define HIGH_COLOR_INSTRUMENT_2 2
#define HIGH_COLOR_VOLUME_1 3
#define HIGH_COLOR_VOLUME_2 4
#define HIGH_COLOR_PANNING_1 5
#define HIGH_COLOR_PANNING_2 6
#define HIGH_COLOR_EFFECT_1 7
#define HIGH_COLOR_EFFECT_2 8
#define HIGH_COLOR_EFFECT_3 9
#define HIGH_COLOR_EFFECT_4 10

int color_1b[11];
int color_2b[11];

char table_decimal[] =
{
    20, 20, 0,
    20, 20, 1,
    20, 20, 2,
    20, 20, 3,
    20, 20, 4,
    20, 20, 5,
    20, 20, 6,
    20, 20, 7,
    20, 20, 8,
    20, 20, 9,

    20, 1, 0,
    20, 1, 1,
    20, 1, 2,
    20, 1, 3,
    20, 1, 4,
    20, 1, 5,
    20, 1, 6,
    20, 1, 7,
    20, 1, 8,
    20, 1, 9,

    20, 2, 0,
    20, 2, 1,
    20, 2, 2,
    20, 2, 3,
    20, 2, 4,
    20, 2, 5,
    20, 2, 6,
    20, 2, 7,
    20, 2, 8,
    20, 2, 9,

    20, 3, 0,
    20, 3, 1,
    20, 3, 2,
    20, 3, 3,
    20, 3, 4,
    20, 3, 5,
    20, 3, 6,
    20, 3, 7,
    20, 3, 8,
    20, 3, 9,

    20, 4, 0,
    20, 4, 1,
    20, 4, 2,
    20, 4, 3,
    20, 4, 4,
    20, 4, 5,
    20, 4, 6,
    20, 4, 7,
    20, 4, 8,
    20, 4, 9,

    20, 5, 0,
    20, 5, 1,
    20, 5, 2,
    20, 5, 3,
    20, 5, 4,
    20, 5, 5,
    20, 5, 6,
    20, 5, 7,
    20, 5, 8,
    20, 5, 9,

    20, 6, 0,
    20, 6, 1,
    20, 6, 2,
    20, 6, 3,
    20, 6, 4,
    20, 6, 5,
    20, 6, 6,
    20, 6, 7,
    20, 6, 8,
    20, 6, 9,

    20, 7, 0,
    20, 7, 1,
    20, 7, 2,
    20, 7, 3,
    20, 7, 4,
    20, 7, 5,
    20, 7, 6,
    20, 7, 7,
    20, 7, 8,
    20, 7, 9,

    20, 8, 0,
    20, 8, 1,
    20, 8, 2,
    20, 8, 3,
    20, 8, 4,
    20, 8, 5,
    20, 8, 6,
    20, 8, 7,
    20, 8, 8,
    20, 8, 9,

    20, 9, 0,
    20, 9, 1,
    20, 9, 2,
    20, 9, 3,
    20, 9, 4,
    20, 9, 5,
    20, 9, 6,
    20, 9, 7,
    20, 9, 8,
    20, 9, 9,

    1, 0, 0,
    1, 0, 1,
    1, 0, 2,
    1, 0, 3,
    1, 0, 4,
    1, 0, 5,
    1, 0, 6,
    1, 0, 7,
    1, 0, 8,
    1, 0, 9,

    1, 1, 0,
    1, 1, 1,
    1, 1, 2,
    1, 1, 3,
    1, 1, 4,
    1, 1, 5,
    1, 1, 6,
    1, 1, 7,
    1, 1, 8,
    1, 1, 9,

    1, 2, 0,
    1, 2, 1,
    1, 2, 2,
    1, 2, 3,
    1, 2, 4,
    1, 2, 5,
    1, 2, 6,
    1, 2, 7,
    1, 2, 8,
    1, 2, 9,
};

// 28 lines on the screen
int Table_Mouse_Lines[] =
{
    0, 
    8 * 1 + 1,
    8 * 2 + 1,
    8 * 3 + 1,
    8 * 4 + 1,
    8 * 5 + 1,
    8 * 6 + 1,
    8 * 7 + 1,
    8 * 8 + 1,
    8 * 9 + 1,
    8 * 10 + 1,
    8 * 11 + 1,
    8 * 12 + 1,
    8 * 13 + 1,
    8 * 14 + 8 + 1,
    8 * 15 + 8 + 1,
    8 * 16 + 8 + 1,
    8 * 17 + 8 + 1,
    8 * 18 + 8 + 1,
    8 * 19 + 8 + 1,
    8 * 20 + 8 + 1,
    8 * 21 + 8 + 1,
    8 * 22 + 8 + 1,
    8 * 23 + 8 + 1,
    8 * 24 + 8 + 1,
    8 * 25 + 8 + 1,
    8 * 26 + 8 + 1,
    8 * 27 + 8 + 1,
    8 * 28 + 8 + 1,
};

PtkTimer Pattern_Timer_Horiz;
int Pattern_Scrolling_Horiz;
float Pattern_First_Delay_Horiz;
float Pattern_Delay_Horiz;

PtkTimer Pattern_Timer_Vert;
int Pattern_Scrolling_Vert;
float Pattern_First_Delay_Vert;
float Pattern_Delay_Vert;

// ------------------------------------------------------
// Functions
int Get_Nibble_Color(int row, int column, int multi, int Shadow);
int Get_Nibble_Color_Highlight(int row, int column);
void Display_Patt_Line(int In_Prev_Next, int Shadow_Pattern, int y, int rel, int track, int tVisible_Columns, int pattern);
void Solo_Track(int track_to_solo);

// ------------------------------------------------------
// Draw a pattern on screen
void draw_pated(int track, int line, int petrack, int row)
{
    int rel = 0;
    int liner;

    int Cur_Position;
    int Cur_Position2;
    int Shadow_Pattern;
    int pattern;
    int In_Prev_Next;
    int In_Prev_Next2;
    int rel2;
    int i;
    int rel2_size;
    int rel2_size2;
    int dover;
    int cur_track;

    if(Songplaying) Cur_Position = cPosition_delay;
    else Cur_Position = cPosition;

    int tVisible_Columns = Visible_Columns;
    if(tVisible_Columns > Songtracks) tVisible_Columns = Songtracks;

    SetColor(COL_PATTERN_LO_BACK);
    bjbox(0, 183, CONSOLE_WIDTH, 13);

    dover = PAT_COL_NOTE;

    // Tracks headers
    for(liner = 0; liner < tVisible_Columns; liner++)
    {
        cur_track = track + liner;

        if(ped_track == cur_track) SetColor(COL_PUSHED_MED);
        else SetColor(COL_PATTERN_LO_BACK);

        dover += 2;
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += 4;
        if(dover >= MAX_PATT_SCREEN_X) break;

        Letter(dover, 187, liner + track, 71, 71 + 6);

        if((dover + 9) >= MAX_PATT_SCREEN_X) break;
        if(CHAN_MUTE_STATE[track + liner]) Letter(dover + 9, 187, 25, 0, 0);
        else Letter(dover + 9, 187, 26, 0, 0);

        if((dover + 9 + 29) >= MAX_PATT_SCREEN_X) break;
        if(CHAN_ACTIVE_STATE[Cur_Position][track + liner]) Letter(dover + 9 + 29, 187, 23, 0, 0);
        else Letter(dover + 9 + 29, 187, 24, 0, 0);

        if((dover + 9 + 29 + 32) >= MAX_PATT_SCREEN_X) break;
        if(ped_track == cur_track) SetColor(COL_VUMETERPEAK);
        else SetColor(COL_PATTERN_LO_BACK);
        bjbox(dover + 9 + 29 + 32, 187, 12, 7);

        // On / off
        for(i = 0; i < MAX_POLYPHONY; i++)
        {
            if(Reserved_Sub_Channels[cur_track][i])
            {
                dover += PAT_COL_CHAR * 3;
                if(dover >= MAX_PATT_SCREEN_X) break;

                dover += PAT_COL_SHIFT - 2;
                if(dover >= MAX_PATT_SCREEN_X) break;

                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
                dover += 2;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
        }
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += PAT_COL_SHIFT;
        if(dover >= MAX_PATT_SCREEN_X) break;
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += PAT_COL_SHIFT;
        if(dover >= MAX_PATT_SCREEN_X) break;
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += PAT_COL_SHIFT;
        if(dover >= MAX_PATT_SCREEN_X) break;
       
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;

        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;

    }

    int y = YVIEW + VIEWLINE2 * 8;
    Cur_Position2 = Cur_Position;
    Shadow_Pattern = 0;
    In_Prev_Next = FALSE;
    In_Prev_Next2 = FALSE;

    SetColor(COL_PATTERN_LO_BACK);
    bjbox(0, 196, CHANNELS_WIDTH + 1, (8 * 29));

    for(liner = VIEWLINE2; liner < VIEWLINE; liner++)
    {
        rel2 = 0;
        rel = liner + line;
        In_Prev_Next = In_Prev_Next2;

        if(See_Prev_Next_Pattern)
        {
            // Can't see past the first & last positions
            if(Cur_Position2)
            {
                if(rel <= -1)
                {
                    // See previous pattern
                    rel2 = patternLines[pSequence[Cur_Position2 - 1]] + rel;
                    if(rel2 < 0)
                    {
                        rel2_size = -rel;
                        rel2_size2 = rel2_size;
                        // Find the first line to display
                        if(rel2 < 0)
                        {
                            rel2 = 0;
                            while(rel2_size2 != 0)
                            {
                                Cur_Position2--;
                                rel2_size2 -= patternLines[pSequence[Cur_Position2]];
                                if(rel2_size2 < 0)
                                {
                                    rel2 += -rel2_size2;
                                    rel2_size2 = 0;
                                }
                                if(!Cur_Position2) break;
                            }
                            y += rel2_size2 * 8;
                            liner += rel2_size2;
                            rel2_size -= rel2_size2;
                        }

                        // Display the lines before our position
                        rel = rel2;
                        In_Prev_Next = TRUE;
                        for(i = 0; i < rel2_size; i++)
                        {
                            pattern = pSequence[Cur_Position2];
                            Display_Patt_Line(In_Prev_Next, Shadow_Pattern, y, rel, track, tVisible_Columns, pattern);
                            y += 8;
                            rel++;
                            if(rel >= patternLines[pSequence[Cur_Position2]])
                            {
                                Cur_Position2++;
                                if(Cur_Position == Cur_Position2)
                                {
                                    In_Prev_Next = FALSE;
                                }
                                rel = 0;
                            }
                            liner++;
                        }
                        liner--;
                        In_Prev_Next2 = FALSE;
                        In_Prev_Next = FALSE;
                        goto Disp;
                    }
                    rel = rel2;
                    In_Prev_Next = TRUE;
                    pattern = pSequence[Cur_Position2 - 1];
                    goto Go_Display;
                } 
            }
            if(Cur_Position2 < sLength - 1)
            {
                if(rel >= patternLines[pSequence[Cur_Position2]])
                {
                    // See next pattern
                    line -= patternLines[pSequence[Cur_Position2]];
                    rel = liner + line;
                    Cur_Position2++;
                    In_Prev_Next2 = TRUE;
                    In_Prev_Next = In_Prev_Next2;
                } 
            } 
        }

        if(rel > -1 && rel < patternLines[pSequence[Cur_Position2]])
        {
            pattern = pSequence[Cur_Position2];
            // Do not show the line at the current caret location
Go_Display:
            if(liner != 0)
            {
                Display_Patt_Line(In_Prev_Next, Shadow_Pattern, y, rel, track, tVisible_Columns, pattern);
            }
            else
            {
                y += 8;
            }
        }
        y += 8;
        Disp:;
    }
}

// ------------------------------------------------------
// Draw a pattern row
void Display_Patt_Line(int In_Prev_Next, int Shadow_Pattern,
                       int y, int rel, int track, int tVisible_Columns, int pattern)
{
    int cur_column;
    int offset_t;
    int cur_color;
    char *ptr_table_decimal;
    int high_color;
    char multip;
    int dover;
    int synchro_fx = FALSE;
    int Fx_Color;
    int tracky;
    int cur_track;
    int i;

    if(!In_Prev_Next) Shadow_Pattern = 0;
    else Shadow_Pattern = 1;

    multip = FALSE;
    if(patt_highlight > 1)
    {
        if(rel % patt_highlight == 0) multip = TRUE;
    }
    cur_column = (track * 11);

    // Browse all tracks to seek synchro markers
    for(tracky = 0; tracky < Songtracks; tracky++)
    {
        offset_t = (rel * 96 + (tracky * 6)) + pattern * 12288;
        unsigned char p_e_sync = *(RawPatterns + offset_t + 4);
        unsigned char p_eh_sync = p_e_sync & 0xf;

        if((p_e_sync >> 4) == 0) if(p_eh_sync == 0x07) synchro_fx = TRUE;
    }
    
    dover = PAT_COL_NOTE;

    for(tracky = 0; tracky < tVisible_Columns; tracky++)
    {
        cur_track = track + tracky;
        // Read the datas
        offset_t = (rel * 96 + ((track + tracky) * 6)) + pattern * 12288;
        unsigned char p_a = *(RawPatterns + offset_t);
        unsigned char p_b = *(RawPatterns + offset_t + 1);
        unsigned char p_bh = p_b & 0xf;
        unsigned char p_c = *(RawPatterns + offset_t + 2);
        unsigned char p_ch = p_c & 0xf;
        unsigned char p_d = *(RawPatterns + offset_t + 3);
        unsigned char p_dh = p_d & 0xf;
        unsigned char p_e = *(RawPatterns + offset_t + 4);
        unsigned char p_eh = p_e & 0xf;
        unsigned char p_f = *(RawPatterns + offset_t + 5);
        unsigned char p_fh = p_f & 0xf;

        // Note
        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        Letter(dover, y, 20, cur_color, cur_color + 7);
        dover += 2;
        if(dover >= MAX_PATT_SCREEN_X) break;
        Letter(dover, y, 30, cur_color, cur_color + 7);
        dover += 4;
        if(dover >= MAX_PATT_SCREEN_X) break;

        for(i = 0; i < MAX_POLYPHONY; i++)
        {
            if(Reserved_Sub_Channels[cur_track][i])
            {
                blitnote(dover, y, p_a, cur_color, cur_color + 7);

                dover += PAT_COL_CHAR * 3;
                if(dover >= MAX_PATT_SCREEN_X) break;

                cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
                Letter(dover, y, 29, cur_color, cur_color + 7);
                dover += PAT_COL_SHIFT - 2;
                if(dover >= MAX_PATT_SCREEN_X) break;
                // Instrument
                if(p_b != 255)
                {
                    Letter(dover, y, p_b >> 4, cur_color, cur_color + 7);
                    dover += PAT_COL_CHAR;
                    if(dover >= MAX_PATT_SCREEN_X) break;
                    cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
                    Letter(dover, y, p_bh, cur_color, cur_color + 7);
                    dover += PAT_COL_CHAR;
                    if(dover >= MAX_PATT_SCREEN_X) break;
                }
                else
                {
                    Letter(dover, y, 21, cur_color, cur_color + 7);
                    dover += PAT_COL_CHAR;
                    if(dover >= MAX_PATT_SCREEN_X) break;
                    cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
                    Letter(dover, y, 21, cur_color, cur_color + 7);
                    dover += PAT_COL_CHAR;
                    if(dover >= MAX_PATT_SCREEN_X) break;
                }
                Letter(dover, y, 29, cur_color, cur_color + 7);
                dover += 2;
            }
        }
        if(dover >= MAX_PATT_SCREEN_X) break;

        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        Letter(dover, y, 29, cur_color, cur_color + 7);
        dover += PAT_COL_SHIFT;
        if(dover >= MAX_PATT_SCREEN_X) break;
        // Volume
        if(p_c != 255)
        {
            Letter(dover, y, p_c >> 4, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
            Letter(dover, y, p_ch, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
        }
        else
        {
            Letter(dover, y, 21, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
            Letter(dover, y, 21, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
        }

        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        Letter(dover, y, 29, cur_color, cur_color + 7);
        dover += PAT_COL_SHIFT;
        if(dover >= MAX_PATT_SCREEN_X) break;
        // Panning
        if(p_d != 255)
        {
            Letter(dover, y, p_d >> 4, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
            Letter(dover, y, p_dh, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
        }
        else
        {
            Letter(dover, y, 21, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
            Letter(dover, y, 21, cur_color, cur_color + 7);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
        }

        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        // Effect
        Letter(dover, y, 29, cur_color, cur_color + 7);
        dover += PAT_COL_SHIFT;
        if(dover >= MAX_PATT_SCREEN_X) break;
        
        Letter(dover, y, p_e >> 4, cur_color, cur_color + 7);
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;
        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        Letter(dover, y, p_eh, cur_color, cur_color + 7);
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;
        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        Letter(dover, y, p_f >> 4, cur_color, cur_color + 7);
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;
        cur_color = Get_Nibble_Color(rel, cur_column++, multip, Shadow_Pattern);
        Letter(dover, y, p_fh, cur_color, cur_color + 7);
        dover += PAT_COL_CHAR;
        if(dover >= MAX_PATT_SCREEN_X) break;
    } // Track

    // Display the rows numbers
    if(Shadow_Pattern)
    {
        if(multip)
        {
            high_color = 71 + 87;
            Fx_Color = 32;
        }
        else
        {
            high_color = 0 + 87;
            Fx_Color = 31;
        }
    }
    else
    {
        if(multip)
        {
            high_color = 71;
            Fx_Color = 32;
        }
        else
        {
            high_color = 0;
            Fx_Color = 31;
        }
    }

    ptr_table_decimal = table_decimal + (rel * 3);

    // Display the row index
    if(Rows_Decimal)
    {
        Letter(0, y, ptr_table_decimal[0], high_color, high_color + 7);
        Letter(8, y, ptr_table_decimal[1], high_color, high_color + 7);
        Letter(16, y, ptr_table_decimal[2], high_color, high_color + 7);
    }
    else
    {
        Letter(0, y, 20, high_color, high_color + 7);
        Letter(8, y, rel >> 4, high_color, high_color + 7);
        Letter(16, y, rel & 0xf, high_color, high_color + 7);
    }

    // Display the synchro marker
    if(synchro_fx)
    {
        Letter(24, y, Fx_Color, 0, 0);
    }
}

// ------------------------------------------------------
// Draw the caret pattern row
void draw_pated_highlight(int track, int line, int petrack, int row)
{
    int offset_t;
    int dover = 0;
    int cur_column;
    int cur_color;
    char *ptr_table_decimal;
    int pattern;
    int Cur_Position;
    int synchro_fx = FALSE;
    int tracky;
    int high_col;
    int i;

    int tVisible_Columns = Visible_Columns;

    if(Songplaying) Cur_Position = cPosition_delay;
    else Cur_Position = cPosition;

    pattern = pSequence[Cur_Position];

    if(RawPatterns)
    {
        if(tVisible_Columns > Songtracks) tVisible_Columns = Songtracks;

        // Browse all tracks to seek synchro markers
        for(tracky = 0; tracky < Songtracks; tracky++)
        {
            offset_t = (line * 96 + (tracky * 6)) + pattern * 12288;
            unsigned char p_e_sync = *(RawPatterns + offset_t + 4);
            unsigned char p_eh_sync = p_e_sync & 0xf;

            if((p_e_sync >> 4) == 0) if(p_eh_sync == 0x07) synchro_fx = TRUE;
        }

        SetColor(COL_PATTERN_LO_BACK);
        bjbox(0, YVIEW, CHANNELS_WIDTH + 1, 16);

        dover = PAT_COL_NOTE;

        cur_column = (track * 11);

        for(tracky = 0; tracky < tVisible_Columns; tracky++)
        {
            int tri = track + tracky;

            offset_t = line * 96 + tri * 6 + pattern * 12288;

            unsigned char p_a = *(RawPatterns + offset_t);
            unsigned char p_b = *(RawPatterns + offset_t + 1);
            unsigned char p_bh = p_b & 0xf;
            unsigned char p_c = *(RawPatterns + offset_t + 2);
            unsigned char p_ch = p_c & 0xf;
            unsigned char p_d = *(RawPatterns + offset_t + 3);
            unsigned char p_dh = p_d & 0xf;
            unsigned char p_e = *(RawPatterns + offset_t + 4);
            unsigned char p_eh = p_e & 0xf;
            unsigned char p_f = *(RawPatterns + offset_t + 5);
            unsigned char p_fh = p_f & 0xf;

            // Note
            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            Letter(dover, YVIEW, 20, cur_color, cur_color + 15);
            dover += 2;
            if(dover >= MAX_PATT_SCREEN_X) break;
            Letter(dover, YVIEW, 30, cur_color, cur_color + 15);
            dover += 4;
            if(dover >= MAX_PATT_SCREEN_X) break;

            high_col = 0;

            for(i = 0; i < MAX_POLYPHONY; i++)
            {
                if(Reserved_Sub_Channels[tri][i])
                {
                    if(row == high_col && tri == petrack) blitnote(dover, YVIEW, p_a, 48, 48 + 15);
                    else blitnote(dover, YVIEW, p_a, cur_color, cur_color + 15);
                    dover += PAT_COL_CHAR * 3;
                    high_col++;
                    if(dover >= MAX_PATT_SCREEN_X) break;

                    // Instrument
                    cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
                    Letter(dover, YVIEW, 29, cur_color, cur_color + 15);
                    dover += PAT_COL_SHIFT - 2;
                    if(dover >= MAX_PATT_SCREEN_X) break;
                    if(row == high_col && tri == petrack)
                    {
                        if(p_b != 255) Letter(dover, YVIEW, p_b >> 4, 48, 48 + 15);
                        else Letter(dover, YVIEW, 21, 48, 48 + 15);
                        dover += PAT_COL_CHAR;
                        if(dover >= MAX_PATT_SCREEN_X) break;
                    }
                    else
                    {
                        if(p_b != 255) Letter(dover, YVIEW, p_b >> 4, cur_color, cur_color + 15);
                        else Letter(dover, YVIEW, 21, cur_color, cur_color + 15);
                        dover += PAT_COL_CHAR;
                        if(dover >= MAX_PATT_SCREEN_X) break;
                    }
                    high_col++;

                    cur_color = Get_Nibble_Color_Highlight(line, cur_column++);

                    if(row == high_col && tri == petrack)
                    {
                        if(p_b != 255) Letter(dover, YVIEW, p_bh, 48, 48 + 15);
                        else Letter(dover, YVIEW, 21, 48, 48 + 15);
                        dover += PAT_COL_CHAR;
                        if(dover >= MAX_PATT_SCREEN_X) break;
                    }
                    else
                    {
                        if(p_b != 255) Letter(dover, YVIEW, p_bh, cur_color, cur_color + 15);
                        else Letter(dover, YVIEW, 21, cur_color, cur_color + 15);
                        dover += PAT_COL_CHAR;
                        if(dover >= MAX_PATT_SCREEN_X) break;
                    }

                    Letter(dover, YVIEW, 29, cur_color, cur_color + 15);
                    dover += 2;

                    high_col++;
                }
            }
            if(dover >= MAX_PATT_SCREEN_X) break;

            // Volume
            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            Letter(dover, YVIEW, 29, cur_color, cur_color + 15);
            dover += PAT_COL_SHIFT;
            if(dover >= MAX_PATT_SCREEN_X) break;
            if(row == high_col && tri == petrack)
            {
                if(p_c != 255) Letter(dover, YVIEW, p_c >> 4, 48, 48 + 15);
                else Letter(dover, YVIEW, 21, 48, 48 + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            else
            {
                if(p_c != 255) Letter(dover, YVIEW, p_c >> 4, cur_color, cur_color + 15);
                else Letter(dover, YVIEW, 21, cur_color, cur_color + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            high_col++;

            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            if(row == high_col && tri == petrack)
            {
                if(p_c != 255) Letter(dover, YVIEW, p_ch, 48, 48 + 15);
                else Letter(dover, YVIEW, 21, 48, 48 + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            else
            {
                if(p_c != 255) Letter(dover, YVIEW, p_ch, cur_color, cur_color + 15);
                else Letter(dover, YVIEW, 21, cur_color, cur_color + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            high_col++;

            // Panning
            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            Letter(dover, YVIEW, 29, cur_color, cur_color + 15);
            dover += PAT_COL_SHIFT;
            if(dover >= MAX_PATT_SCREEN_X) break;
            if(row == high_col && tri == petrack)
            {
                if(p_d != 255) Letter(dover, YVIEW, p_d >> 4, 48, 48 + 15);
                else Letter(dover, YVIEW, 21, 48, 48 + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            else
            {
                if(p_d != 255) Letter(dover, YVIEW, p_d >> 4, cur_color, cur_color + 15);
                else Letter(dover, YVIEW, 21, cur_color, cur_color + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            high_col++;

            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            if(row == high_col && tri == petrack)
            {
                if(p_d != 255) Letter(dover, YVIEW, p_dh, 48, 48 + 15);
                else Letter(dover, YVIEW, 21, 48, 48 + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            else
            {
                if(p_d != 255) Letter(dover, YVIEW, p_dh, cur_color, cur_color + 15);
                else Letter(dover, YVIEW, 21, cur_color, cur_color + 15);
                dover += PAT_COL_CHAR;
                if(dover >= MAX_PATT_SCREEN_X) break;
            }
            high_col++;

            //  Effects
            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            Letter(dover, YVIEW, 29, cur_color, cur_color + 15);
            dover += PAT_COL_SHIFT;
            if(dover >= MAX_PATT_SCREEN_X) break;
            if(row == high_col && tri == petrack) Letter(dover, YVIEW, p_e >> 4, 48, 48 + 15);
            else Letter(dover, YVIEW, p_e >> 4, cur_color, cur_color + 15);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            high_col++;

            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            if(row == high_col && tri == petrack) Letter(dover, YVIEW, p_eh, 48, 48 + 15);
            else Letter(dover, YVIEW, p_eh, cur_color, cur_color + 15);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            high_col++;

            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            if((p_e >> 4) == 0) if(p_eh == 0x07) synchro_fx = TRUE;
            if(row == high_col && tri == petrack) Letter(dover, YVIEW, p_f >> 4, 48, 48 + 15);
            else Letter(dover, YVIEW, p_f >> 4, cur_color, cur_color + 15);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            high_col++;

            cur_color = Get_Nibble_Color_Highlight(line, cur_column++);
            if(row == high_col && tri == petrack) Letter(dover, YVIEW, p_fh, 48, 48 + 15);
            else Letter(dover, YVIEW, p_fh, cur_color, cur_color + 15);
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) break;
            high_col++;

            if(sr_isrecording)
            {
                if(liveparam > 0 && ped_track == tri && Songplaying)
                {
                    if(livevalue < 0) livevalue = 0;
                    if(livevalue > 255) livevalue = 255;

                    switch(liveparam)
                    {
                        case LIVE_PARAM_TRACK_CUTOFF:
                            *(RawPatterns + offset_t + 4) = 8;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_TRACK_RESONANCE:
                            *(RawPatterns + offset_t + 4) = 0x14;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_TRACK_REVERB_SEND:
                            *(RawPatterns + offset_t + 4) = 0x11;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_TRACK_THRESHOLD:
                            *(RawPatterns + offset_t + 4) = 0x12;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_TRACK_CLAMP:
                            *(RawPatterns + offset_t + 4) = 0x13;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_TRACK_PANNING:
                            if(livevalue > 128) livevalue = 0x80;
                            *(RawPatterns + offset_t + 3) = livevalue;
                            break;
                        case LIVE_PARAM_303_1_CUTOFF:
                            *(RawPatterns + offset_t + 4) = 0x33;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_2_CUTOFF:
                            *(RawPatterns + offset_t + 4) = 0x34;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_1_RESONANCE:
                            *(RawPatterns + offset_t + 4) = 0x35;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_2_RESONANCE:
                            *(RawPatterns + offset_t + 4) = 0x36;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_1_ENVMOD:
                            *(RawPatterns + offset_t + 4) = 0x37;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_2_ENVMOD:
                            *(RawPatterns + offset_t + 4) = 0x38;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_1_DECAY:
                            *(RawPatterns + offset_t + 4) = 0x39;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_2_DECAY:
                            *(RawPatterns + offset_t + 4) = 0x3a;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_1_TUNE:
                            *(RawPatterns + offset_t + 4) = 0x3d;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_2_TUNE:
                            *(RawPatterns + offset_t + 4) = 0x3e;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_1_ACCENT:
                            *(RawPatterns + offset_t + 4) = 0x3b;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                        case LIVE_PARAM_303_2_ACCENT:
                            *(RawPatterns + offset_t + 4) = 0x3c;
                            *(RawPatterns + offset_t + 5) = livevalue;
                            break;
                    } // Close switch

                    liveparam = 0;
                } // Close liveparam updated
            } // Close is recording
        }

        // Row number
        ptr_table_decimal = table_decimal + (line * 3);
        if(Rows_Decimal)
        {
            Letter(0, YVIEW, ptr_table_decimal[0], 16, 16 + 15);
            Letter(8, YVIEW, ptr_table_decimal[1], 16, 16 + 15);
            Letter(16, YVIEW, ptr_table_decimal[2], 16, 16 + 15);
        }
        else
        {
            Letter(0, YVIEW, 20, 16, 16 + 15);
            Letter(8, YVIEW, line >> 4, 16, 16 + 15);
            Letter(16, YVIEW, line & 0xf, 16, 16 + 15);
        }

        // Synchro marker
        if(synchro_fx)
        {
            Letter(24, YVIEW + 4, 33, 0, 0);
        }
    }
}

// ------------------------------------------------------
// Update the displayed pattern data
void Actupated(int modac)
{
    int nlines;
    int Cur_Position;
    int cur_line;

    if(is_editing > 1)
    {
        is_editing = 0;
        StartEdit();
    }

    if(Songplaying)
    {
        nlines = patternLines[pSequence[cPosition_delay]];
        if(ped_line_delay < 0) ped_line_delay += nlines;
        if(ped_line_delay >= nlines) ped_line_delay -= nlines;
        if(ped_line_delay >= nlines) ped_line_delay = nlines - 1;
    }
    else
    {
        nlines = patternLines[pSequence[cPosition]];

        if(cPosition != 0 || cPosition < (sLength - 1))
        {
            if(Continuous_Scroll)
            {
                if(ped_line < 0)
                {
                    nlines = patternLines[pSequence[cPosition - 1]];
                    ped_line = nlines + ped_line;
                    Unselect_Selection();
                    gui_action = GUI_CMD_PREVIOUS_POSITION;
                    return;
                }
                else
                {
                    if(ped_line >= nlines)
                    {
                        ped_line -= nlines;
                        Unselect_Selection();
                        gui_action = GUI_CMD_NEXT_POSITION;
                        return;
                    }
                }
            }
            else
            {
                if(ped_line < 0) ped_line += nlines;
                if(ped_line >= nlines) ped_line -= nlines;
                if(ped_line >= nlines) ped_line = nlines - 1;
            }
        }
        else
        {
            if(ped_line < 0) ped_line += nlines;
            if(ped_line >= nlines) ped_line -= nlines;
            if(ped_line >= nlines) ped_line = nlines - 1;
        }
    }

    if(ped_row > 10)
    {
        ped_row = 0;
        ped_track++;
    }
    if(ped_row < 0)
    {
        ped_row = 10;
        ped_track--;
    }
    if(ped_track > Songtracks - 1)
    {
        ped_track = 0;
        gui_track = 0;
        Set_Track_Slider(gui_track);
        modac = 0;
    }
    if(ped_track < 0)
    {
        ped_track = Songtracks - 1;
        gui_track = Songtracks - (Visible_Columns);
        if(gui_track < 0) gui_track = 0;
        Set_Track_Slider(gui_track);
        modac = 0;
    }
    if(ped_track >= gui_track + Visible_Columns)
    {
        gui_track += (ped_track + 1) - (gui_track + Visible_Columns);
        Set_Track_Slider(gui_track);
        modac = 0;
    }
    if(ped_track < gui_track)
    {
        gui_track -= gui_track - ped_track;
        Set_Track_Slider(gui_track);
        modac = 0;
    }

    
    if(Songplaying)
    {
        cur_line = ped_line_delay;
        Cur_Position = cPosition_delay;
    }
    else
    {
        cur_line = ped_line;
        Cur_Position = cPosition;
    }

    draw_pated(gui_track, cur_line, ped_track, ped_row);
    draw_pated_highlight(gui_track, cur_line, ped_track, ped_row);

    Realslider_Vert(781, 212, cur_line, DISPLAYED_LINES, patternLines[pSequence[Cur_Position]] + DISPLAYED_LINES, 200, TRUE);
    Gui_Draw_Button_Box(781, 196, 16, 14, "\01", BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
    Gui_Draw_Button_Box(781, 413, 16, 14, "\02", BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
}

// ------------------------------------------------------
// Actually the extra data associated with the pattern
void Actualize_Patterned(void)
{
    if(ped_pattad < 0) ped_pattad = 16;
    if(ped_pattad > 16) ped_pattad = 0;
    if(ped_patoct < 0) ped_patoct = 0;
    if(ped_patoct > 8) ped_patoct = 8;
    if(ped_patsam < 0) ped_patsam = 127;
    if(ped_patsam > 127) ped_patsam = 0;

    char tcp[30];
    sprintf(tcp, "%s_", nameins[ped_patsam]);

    if(snamesel == 2) Gui_Draw_Button_Box(90, 134, 166, 16, tcp, BUTTON_PUSHED);
    else Gui_Draw_Button_Box(90, 134, 166, 16, nameins[ped_patsam], BUTTON_NORMAL);

    Gui_Draw_Arrows_Number_Box2(90, 152, ped_pattad, BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
    value_box(258, 152, ped_patoct, BUTTON_NORMAL | BUTTON_TEXT_CENTERED);
    value_box(258, 134, ped_patsam, BUTTON_NORMAL | BUTTON_TEXT_CENTERED);

    Set_Track_Slider(gui_track);
}

// ------------------------------------------------------
// Create a new pattern
int Alloc_Patterns_Pool(void)
{
    for(int api = 0; api < 128; api++)
    {
        patternLines[api] = 64;
    }

    nPatterns = 1;

    if((RawPatterns = (unsigned char *) malloc(PBLEN)) != NULL)
    { // 6144 bytes per pattern
        for(int inicial = 0; inicial < PBLEN; inicial += 6)
        {
            *(RawPatterns + inicial) = 121;     //121
            *(RawPatterns + inicial + 1) = 255; //255
            *(RawPatterns + inicial + 2) = 255; //255
            *(RawPatterns + inicial + 3) = 255; //255
            *(RawPatterns + inicial + 4) = 0;   //0
            *(RawPatterns + inicial + 5) = 0;   //0
        }
        return TRUE; // Allocated
    }
    else
    {
        return FALSE; // Not allocated
    }
} // End of alloc pattern

// ------------------------------------------------------
// Return the correct color of a character (select / highlighted or not)
int Get_Nibble_Color(int row, int column, int multi, int Shadow)
{
    int color = (Shadow * 87);
    
    if(!Shadow)
    {
        if(column >= block_start_track &&
           column <= block_end_track &&
           row >= block_start && row <= block_end)
        {
            color = 8;
        }
    }
    if(multi) color += 71;
    return(color);
}

// ------------------------------------------------------
// Return the color of a character in the caret row
int Get_Nibble_Color_Highlight(int row, int column)
{
    int color = 0;
    if(column >= block_start_track &&
       column <= block_end_track &&
       row >= block_start && row <= block_end)
    {
        color = 16;
    }
    return(color + 16);
}

// ------------------------------------------------------
// Return the size in pixel of a given track
int Get_Track_Size(int Track)
{
    int i;
    int dover = 0;
    int old_dover = 0;

    // Gap
    old_dover = dover;
    dover += 2;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    old_dover = dover;
    dover += 4;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    // On / off
    for(i = 0; i < MAX_POLYPHONY; i++)
    {
        if(Reserved_Sub_Channels[Track][i])
        {
            // Note
            old_dover = dover;
            dover += PAT_COL_CHAR * 3;
            if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

            // Gap
            old_dover = dover;
            dover += PAT_COL_SHIFT - 2;
            if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

            // Instrument
            old_dover = dover;
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

            old_dover = dover;
            dover += PAT_COL_CHAR;
            if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

            // Gap
            old_dover = dover;
            dover += 2;
            if(dover >= MAX_PATT_SCREEN_X) return(old_dover);
        }
    }

    // Gap
    old_dover = dover;
    dover += PAT_COL_SHIFT;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    // Volume
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    // Gap
    old_dover = dover;
    dover += PAT_COL_SHIFT;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    // Panning
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    // Gap
    old_dover = dover;
    dover += PAT_COL_SHIFT;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    // Effect
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(dover >= MAX_PATT_SCREEN_X) return(old_dover);

    return(dover);
}

// ------------------------------------------------------
// Return the size in pixel of all visible tracks
int Get_Visible_Tracks_Size(void)
{
    int i;
    int size = 0;

    for(i = gui_track; i < (gui_track + Visible_Columns); i++)
    {
        size += Get_Track_Size(i);
    }
    return(size);
}

// ------------------------------------------------------
// Return the index of the tracker located under the mouse pointer
int Get_Track_Over_Mouse(void)
{
    int i;
    int bound_left = 0;
    int bound_right = 0;
    int under_mouse = 0;
    int mouse_coord = Mouse.x;

    if(mouse_coord > CHANNELS_WIDTH)
    {
        under_mouse = (gui_track + 1) + Visible_Columns - 1;

        // It will scroll
        if(under_mouse >= (gui_track + Visible_Columns - 1))
        {
            if(Pattern_Scrolling_Horiz)
            {
                Pattern_Delay_Horiz += Pattern_Timer_Horiz.Get_Frames_Delay();
                if(Pattern_Delay_Horiz < Pattern_First_Delay_Horiz)
                {
                    // Wait before scrolling
                    under_mouse--;
                }
                else
                {
                    // Scroll it
                    Pattern_Delay_Horiz = 0;
                    Pattern_First_Delay_Horiz = 200.0f;
                }
            }
            else
            {
                Pattern_Timer_Horiz.Set_Frames_Counter();
                Pattern_Scrolling_Horiz = TRUE;
                Pattern_Delay_Horiz = 0;
                Pattern_First_Delay_Horiz = 0.0f;
                under_mouse--;
            }
        }
        else
        {
            Pattern_Delay_Horiz = 0;
            Pattern_Scrolling_Horiz = FALSE;
        }
    }
    else
    {
        mouse_coord -= PAT_COL_NOTE;
        for(i = gui_track; i < (gui_track + Visible_Columns); i++)
        {
            bound_right += Get_Track_Size(i);
            if(mouse_coord >= bound_left && mouse_coord < bound_right)
            {
                under_mouse = i;
                break;
            }
            bound_left = bound_right;
        }
    }
    if(under_mouse < gui_track)
    {
        if(Pattern_Scrolling_Horiz)
        {
            Pattern_Delay_Horiz += Pattern_Timer_Horiz.Get_Frames_Delay();
            if(Pattern_Delay_Horiz < Pattern_First_Delay_Horiz)
            {
                // Wait before scrolling
                under_mouse = gui_track;
            }
            else
            {
                under_mouse = gui_track - 1;
                // Scroll it
                Pattern_Delay_Horiz = 0;
                Pattern_First_Delay_Horiz = 150.0f;
            }
        }
        else
        {
            Pattern_Timer_Horiz.Set_Frames_Counter();
            Pattern_Scrolling_Horiz = TRUE;
            Pattern_Delay_Horiz = 0;
            Pattern_First_Delay_Horiz = 0.0f;
            under_mouse = gui_track;
        }
    }

    if(under_mouse > Songtracks - 1) under_mouse = Songtracks - 1;
    if(under_mouse < 0) under_mouse = 0;
    return(under_mouse);
}

// ------------------------------------------------------
// Return the index of a track column according to a coordinate
int Get_Column_Idx(int track, int mouse_coord)
{
    int ret_value = 0;
    int old_dover = 0;
    int dover = 0;
    int i;
    
    if(mouse_coord < 0) return(0);

    // Gap
    old_dover = dover;
    dover += 2;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);
    
    old_dover = dover;
    dover += 4;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    // On / off
    for(i = 0; i < MAX_POLYPHONY; i++)
    {
        if(Reserved_Sub_Channels[track][i])
        {
            // Note
            old_dover = dover;
            dover += PAT_COL_CHAR * 3;
            if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

            ret_value++;
            // Gap
            old_dover = dover;
            dover += PAT_COL_SHIFT - 2;
            if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

            // Instrument
            old_dover = dover;
            dover += PAT_COL_CHAR;
            if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

            ret_value++;
            old_dover = dover;
            dover += PAT_COL_CHAR;
            if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

            ret_value++;
            // Gap
            old_dover = dover;
            dover += 2;
            if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);
        }
    }

    // Gap
    old_dover = dover;
    dover += PAT_COL_SHIFT;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    // Volume
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);
    
    ret_value++;
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    // Gap
    ret_value++;
    old_dover = dover;
    dover += PAT_COL_SHIFT;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    // Panning
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    ret_value++;
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    // Gap
    ret_value++;
    old_dover = dover;
    dover += PAT_COL_SHIFT;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    // Effect
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    ret_value++;
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    ret_value++;
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    ret_value++;
    old_dover = dover;
    dover += PAT_COL_CHAR;
    if(mouse_coord >= old_dover && mouse_coord < dover) return(ret_value);

    return(ret_value);
}

// ------------------------------------------------------
// Return the index of the column located under the mouse pointer
int Get_Column_Over_Mouse(void)
{
    int i;
    int max_tr = 6;
    int dover = 0;
    int old_dover = 0;

    int track = Get_Track_Over_Mouse();
    int mouse_coord = Mouse.x - PAT_COL_NOTE;
    int column = 0;

    for(i = gui_track; i < track; i++)
    {
        mouse_coord -= Get_Track_Size(i);
    }
    column = Get_Column_Idx(track, mouse_coord);
    return(column);
}

// ------------------------------------------------------
// return the index of the row located under the mouse pointer
int Get_Line_Over_Mouse(void)
{
    int i;
    int Cur_Position = cPosition;
    if(Songplaying) Cur_Position = cPosition_delay;

    int mouse_line = (Mouse.y - 194) - 1;
    for(i = 0; i < (sizeof(Table_Mouse_Lines) / sizeof(int)) - 1; i++)
    {
        if(mouse_line >= Table_Mouse_Lines[i] &&
           mouse_line < Table_Mouse_Lines[i + 1])
        {
            mouse_line = i - 13 + ped_line;
            break;   
        }
    }
    if(mouse_line > patternLines[pSequence[Cur_Position]] - 1) mouse_line = patternLines[pSequence[Cur_Position]] - 1;
    if(mouse_line < 0) mouse_line = 0;
    return(mouse_line);
}

// ------------------------------------------------------
// Set the layout of the tracks slider and bound the caret
void Set_Track_Slider(int pos)
{
    int i;
    int pixel_size_tracks = 0;
    int pixel_visible_tracks = 0;
    int pixel_visible_pos = 0;

    for(i = 0; i < pos; i++)
    {
        pixel_visible_pos += Get_Track_Size(i);
    }

    for(i = 0; i < Songtracks; i++)
    {
        pixel_size_tracks += Get_Track_Size(i);
    }

    for(i = 0; i < Visible_Columns; i++)
    {
        pixel_visible_tracks += Get_Track_Size(i);
    }

    Realslider_Horiz(726, 429, pixel_visible_pos, pixel_visible_tracks, pixel_size_tracks, 72, TRUE);

    if(ped_track >= gui_track + Visible_Columns - 1) ped_track = gui_track + Visible_Columns - 1;
    if(ped_track < gui_track) ped_track = gui_track;
}

// ------------------------------------------------------
// Make sure the position isn't beyond current pattern lines range
void Bound_Patt_Pos(void)
{
    if(ped_line >= patternLines[pSequence[cPosition]])
    {
        ped_line = patternLines[pSequence[cPosition]] - 1;
    }
}

// ------------------------------------------------------
// Reset the mouse scrolling timing
void Reset_Pattern_Scrolling_Horiz(void)
{
    Pattern_Delay_Horiz = 0;
    Pattern_Scrolling_Horiz = FALSE;
    Pattern_Delay_Vert = 0;
    Pattern_Scrolling_Vert = FALSE;
}

// ------------------------------------------------------
// Handle the mouse wheel event
void Mouse_Wheel_Pattern_Ed(int roll_amount)
{
    int Cur_Position;

    if(Songplaying) Cur_Position = cPosition_delay;
    else Cur_Position = cPosition;

    // Scroll the patterns
    if(zcheckMouse_nobutton(0, 182, CONSOLE_WIDTH, 246) == 1)
    {
        ped_line += roll_amount;
        if(Continuous_Scroll && !Cur_Position) if(ped_line < 0) ped_line = 0;
        if(Continuous_Scroll && (Cur_Position == sLength - 1))
        {
            if(ped_line >= patternLines[pSequence[Cur_Position]])
            {
                ped_line = patternLines[pSequence[Cur_Position]] - 1;
            }
        }
        Actupated(0);
    }
}

// ------------------------------------------------------
// Handle the sliders event (right mouse button)
void Mouse_Sliders_Right_Pattern_Ed(void)
{
    int sched_line;

    // Position the caret on the specified track/column with the mouse
    if(zcheckMouse(1, 194, CHANNELS_WIDTH, 234))
    {
        ped_track = Get_Track_Over_Mouse();
        ped_row = Get_Column_Over_Mouse();
        Actupated(1);
        gui_action = GUI_CMD_SET_FOCUS_TRACK;
    }

    // Go to the row selected with the mouse
    if(!Songplaying)
    {
        if(zcheckMouse(1, 194, CHANNELS_WIDTH, 234))
        {
            if(!is_recording)
            {
                sched_line = Get_Line_Over_Mouse();

                if(Pattern_Scrolling_Vert)
                {
                    Pattern_Delay_Vert += Pattern_Timer_Vert.Get_Frames_Delay();
                    if(Pattern_Delay_Vert >= Pattern_First_Delay_Vert)
                    {
                        // Scroll it
                        Pattern_Delay_Vert = 0;
                        Pattern_First_Delay_Vert = 250.0f;
                        ped_line = sched_line;
                    }
                }
                else
                {
                    Pattern_Timer_Vert.Set_Frames_Counter();
                    Pattern_Scrolling_Vert = TRUE;
                    Pattern_Delay_Vert = 0;
                    Pattern_First_Delay_Vert = 0.0f;
                }
            }
            Actupated(1);
        }
    }
}

// ------------------------------------------------------
// Handle the sliders event (left mouse button)
void Mouse_Sliders_Pattern_Ed(void)
{
    // Current track slider
    if(zcheckMouse(726, 429, 72, 16))
    {
        float Pos_Mouse = (float) (Mouse.x - 726);
        if(Pos_Mouse < 0) Pos_Mouse = 0;
        int disp = 6;
        if(Songtracks < disp) disp = Songtracks;
        disp = (Songtracks - disp);
        // Normalize and scale
        Pos_Mouse = (Pos_Mouse / 72.0f) * (disp + 1);
        if(Pos_Mouse > disp) Pos_Mouse = (float) disp;
        gui_track = (int) Pos_Mouse;
        Set_Track_Slider(gui_track);
        Actupated(1);
    }

    // Rows slider
    if(zcheckMouse(781, 212, 16 + 1, 200) & !Songplaying)
    {
        int final_row;
        int Cur_Position = Get_Current_Position();
        int max_length = patternLines[pSequence[Cur_Position]] + DISPLAYED_LINES;
        int Center = Slider_Get_Center(DISPLAYED_LINES, max_length, 200);
        float Pos_Mouse = ((float) ((Mouse.y - 212) - (Center / 2))) / 200.0f;
        if(Pos_Mouse > 1.0f) Pos_Mouse = 1.0f;
        float s_offset = (Pos_Mouse * max_length);
        if(s_offset > (float) (max_length - DISPLAYED_LINES))
        {
            s_offset = (float) (max_length - DISPLAYED_LINES);
        }
        final_row = (int32) s_offset;
        if(final_row < 0) final_row = 0;
        if(final_row > patternLines[pSequence[Cur_Position]] - 1) final_row = patternLines[pSequence[Cur_Position]] - 1;
        ped_line = final_row;
        Actupated(0);
    }

    // End of the marking stuff
    if(zcheckMouse(1, 194, CHANNELS_WIDTH, 234) && !Songplaying)
    {
        Mark_Block_End(Get_Column_Over_Mouse(), Get_Track_Over_Mouse(), Get_Line_Over_Mouse(), 3);
    }
}

// ------------------------------------------------------
// Handle the left mouse button event
void Mouse_Left_Pattern_Ed(void)
{
    // Start of the marking block
    if(zcheckMouse(1, 194, CHANNELS_WIDTH, 234) && !Songplaying)
    {
        Mark_Block_Start(Get_Column_Over_Mouse(), Get_Track_Over_Mouse(), Get_Line_Over_Mouse());
    }

    // Next/Prev rows buttons
    if(zcheckMouse(781, 196, 16 + 1, 14) & !Songplaying)
    {
        int Cur_Position = Get_Current_Position();

        ped_line--;
        if(Continuous_Scroll && !Cur_Position) if(ped_line < 0) ped_line = 0;
        Actupated(0);
    }
    if(zcheckMouse(781, 413, 16 + 1, 14) & !Songplaying)
    {
        int Cur_Position = Get_Current_Position();

        ped_line++;
        if(Continuous_Scroll && (Cur_Position == sLength - 1)) if(ped_line >= patternLines[pSequence[Cur_Position]]) ped_line = patternLines[pSequence[Cur_Position]] - 1;
        Actupated(0);
    }
}

// ------------------------------------------------------
// Handle the right mouse button event
void Mouse_Right_Pattern_Ed(void)
{
    // Decrease/Increase steps
    if(zcheckMouse(90, 152, 16, 16))
    {
        ped_pattad = 0;
        gui_action = GUI_CMD_UPDATE_PATTERN_ED;
    }
    if(zcheckMouse(134, 152, 16, 16))
    {
        ped_pattad = 16;
        gui_action = GUI_CMD_UPDATE_PATTERN_ED;
    }

    // Solo track with right mouse button
    if(zcheckMouse(1, 184, CHANNELS_WIDTH, 10) == 1)
    {
        int tmp_track = Get_Track_Over_Mouse();

        if(tmp_track > 15) tmp_track = 15;
        if(tmp_track < 0) tmp_track = 0;

        Solo_Track(tmp_track);
        // Will unmute the correct track
        gui_action = GUI_CMD_SWITCH_TRACK_MUTE_STATE;
    }
}

// ------------------------------------------------------
// Mute all tracks but a given one
void Solo_Track(int track_to_solo)
{
    // Unmute all if the user clicked on a solo track
    if(CHAN_MUTE_STATE[track_to_solo] == 0)
    {
        int Was_Solo = FALSE;
        
        // Check if all other tracks are muted
        for(int solify = 0; solify < MAX_TRACKS; solify++)
        {
            if((solify != track_to_solo) && CHAN_MUTE_STATE[solify] == 0)
            {
                Was_Solo = TRUE;
            }
        }
        if(!Was_Solo)
        {
            // Unmute all
            for(int solify = 0; solify < MAX_TRACKS; solify++)
            {
                CHAN_MUTE_STATE[solify] = 0;
            }
            CHAN_MUTE_STATE[track_to_solo] = 1;
        }
        else
        {
            // Else mute all
            for(int solify = 0; solify < MAX_TRACKS; solify++)
            {
                CHAN_MUTE_STATE[solify] = 1;
            }
        }
    }
    else
    {
        // Else mute all
        for(int solify = 0; solify < MAX_TRACKS; solify++)
        {
            CHAN_MUTE_STATE[solify] = 1;
        }
    }
}

// ------------------------------------------------------
// Move one row above
void Goto_Previous_Row(void)
{
    int Cur_Position = Get_Current_Position();

    Select_Block_Keyboard(BLOCK_MARK_ROWS);
    ped_line--;
    if(Continuous_Scroll && !Cur_Position) if(ped_line < 0) ped_line = 0;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_ROWS);
}

// ------------------------------------------------------
// Move one row below
void Goto_Next_Row(void)
{
    int Cur_Position = Get_Current_Position();

    Select_Block_Keyboard(BLOCK_MARK_ROWS);
    ped_line++;
    if(Continuous_Scroll && (Cur_Position == sLength - 1)) if(ped_line >= patternLines[pSequence[Cur_Position]]) ped_line = patternLines[pSequence[Cur_Position]] - 1;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_ROWS);
}

// ------------------------------------------------------
// Move one page above
void Goto_Previous_Page(void)
{
    int Cur_Position = Get_Current_Position();

    Select_Block_Keyboard(BLOCK_MARK_ROWS);
    ped_line -= 16;
    if(!is_recording && !Continuous_Scroll) if(ped_line < 0) ped_line = 0;
    if(Continuous_Scroll && !Cur_Position) if(ped_line < 0) ped_line = 0;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_ROWS);
}

// ------------------------------------------------------
// Move one page below
void Goto_Next_Page(void)
{
    int Cur_Position = Get_Current_Position();

    Select_Block_Keyboard(BLOCK_MARK_ROWS);
    ped_line += 16;
    if(!is_recording && !Continuous_Scroll) if(ped_line >= patternLines[pSequence[Cur_Position]]) ped_line = patternLines[pSequence[Cur_Position]] - 1;
    if(Continuous_Scroll && (Cur_Position == sLength - 1)) if(ped_line >= patternLines[pSequence[Cur_Position]]) ped_line = patternLines[pSequence[Cur_Position]] - 1;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_ROWS);
}

// ------------------------------------------------------
// Move one column on the left
void Goto_Previous_Column(void)
{
    Select_Block_Keyboard(BLOCK_MARK_TRACKS);
    ped_row--;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_TRACKS);
    gui_action = GUI_CMD_SET_FOCUS_TRACK;
}

// ------------------------------------------------------
// Move one column on the right
void Goto_Next_Column(void)
{
    Select_Block_Keyboard(BLOCK_MARK_TRACKS);
    ped_row++;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_TRACKS);
    gui_action = GUI_CMD_SET_FOCUS_TRACK;
}

// ------------------------------------------------------
// Move to the top left of the pattern
void Goto_Top_Left(void)
{
    Select_Block_Keyboard(BLOCK_MARK_ROWS | BLOCK_MARK_TRACKS);
    ped_row = 0;
    ped_track = 0;
    if(Get_LCtrl()) ped_line = 0;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_ROWS | BLOCK_MARK_TRACKS);
    gui_action = GUI_CMD_SET_FOCUS_TRACK;
}

// ------------------------------------------------------
// Move to the bottom right of the pattern
void Goto_Bottom_Right(void)
{
    Select_Block_Keyboard(BLOCK_MARK_ROWS | BLOCK_MARK_TRACKS);
    ped_row = 0;
    ped_track = Songtracks - 1;
    if(Get_LCtrl()) ped_line = patternLines[pSequence[cPosition_delay]] - 1;
    Actupated(0);
    gui_action = GUI_CMD_SET_FOCUS_TRACK;
    Select_Block_Keyboard(BLOCK_MARK_ROWS | BLOCK_MARK_TRACKS);
}

// ------------------------------------------------------
// Move to a given row of the pattern
void Goto_Row(int row)
{
    Select_Block_Keyboard(BLOCK_MARK_ROWS);
    ped_line = row;
    Actupated(0);
    Select_Block_Keyboard(BLOCK_MARK_ROWS);
}

// ------------------------------------------------------
// Return the current sequence position
int Get_Current_Position(void)
{
    if(Songplaying) return(cPosition_delay);
    else return(cPosition);
}
