#ifndef ASTC_TABLES_INTEGER_SEQUENCE_ENCODING_H_
#define ASTC_TABLES_INTEGER_SEQUENCE_ENCODING_H_

#ifdef RTTC_USE_ASTCRT

static const uint8_t integer_from_trits[3][3][3][3][3] = {
    {
        {
            {
                {0,1,2},
                {4,5,6},
                {8,9,10}
            },
            {
                {16,17,18},
                {20,21,22},
                {24,25,26}
            },
            {
                {3,7,15},
                {19,23,27},
                {12,13,14}
            }
        },
        {
            {
                {32,33,34},
                {36,37,38},
                {40,41,42}
            },
            {
                {48,49,50},
                {52,53,54},
                {56,57,58}
            },
            {
                {35,39,47},
                {51,55,59},
                {44,45,46}
            }
        },
        {
            {
                {64,65,66},
                {68,69,70},
                {72,73,74}
            },
            {
                {80,81,82},
                {84,85,86},
                {88,89,90}
            },
            {
                {67,71,79},
                {83,87,91},
                {76,77,78}
            }
        }
    },
    {
        {
            {
                {128,129,130},
                {132,133,134},
                {136,137,138}
            },
            {
                {144,145,146},
                {148,149,150},
                {152,153,154}
            },
            {
                {131,135,143},
                {147,151,155},
                {140,141,142}
            }
        },
        {
            {
                {160,161,162},
                {164,165,166},
                {168,169,170}
            },
            {
                {176,177,178},
                {180,181,182},
                {184,185,186}
            },
            {
                {163,167,175},
                {179,183,187},
                {172,173,174}
            }
        },
        {
            {
                {192,193,194},
                {196,197,198},
                {200,201,202}
            },
            {
                {208,209,210},
                {212,213,214},
                {216,217,218}
            },
            {
                {195,199,207},
                {211,215,219},
                {204,205,206}
            }
        }
    },
    {
        {
            {
                {96,97,98},
                {100,101,102},
                {104,105,106}
            },
            {
                {112,113,114},
                {116,117,118},
                {120,121,122}
            },
            {
                {99,103,111},
                {115,119,123},
                {108,109,110}
            }
        },
        {
            {
                {224,225,226},
                {228,229,230},
                {232,233,234}
            },
            {
                {240,241,242},
                {244,245,246},
                {248,249,250}
            },
            {
                {227,231,239},
                {243,247,251},
                {236,237,238}
            }
        },
        {
            {
                {28,29,30},
                {60,61,62},
                {92,93,94}
            },
            {
                {156,157,158},
                {188,189,190},
                {220,221,222}
            },
            {
                {31,63,127},
                {159,191,255},
                {252,253,254}
            }
        }
    }
};

static const uint8_t integer_from_quints[5][5][5] = {
    {
        {0,1,2,3,4},
        {8,9,10,11,12},
        {16,17,18,19,20},
        {24,25,26,27,28},
        {5,13,21,29,6}
    },
    {
        {32,33,34,35,36},
        {40,41,42,43,44},
        {48,49,50,51,52},
        {56,57,58,59,60},
        {37,45,53,61,14}
    },
    {
        {64,65,66,67,68},
        {72,73,74,75,76},
        {80,81,82,83,84},
        {88,89,90,91,92},
        {69,77,85,93,22}
    },
    {
        {96,97,98,99,100},
        {104,105,106,107,108},
        {112,113,114,115,116},
        {120,121,122,123,124},
        {101,109,117,125,30}
    },
    {
        {102,103,70,71,38},
        {110,111,78,79,46},
        {118,119,86,87,54},
        {126,127,94,95,62},
        {39,47,55,63,31}
    }
};

#endif

#endif