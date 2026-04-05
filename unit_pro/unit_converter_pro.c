/*
 * ================================================================
 *  unit_converter_pro.c — Enhanced Unit Converter Backend
 *  Class 11 Computer Science Project (Upgraded Version)
 *
 *  FEATURES:
 *    6 Conversion Categories:
 *      1. Temperature (C, F, K — 5 pairs)
 *      2. Distance    (m, km, cm, ft, mi — 6 pairs)
 *      3. Mass        (kg, g, lb, mg, t — 6 pairs)
 *      4. Speed       (m/s, km/h, mph — 5 pairs)
 *      5. Area        (m², cm², ft², ha, acre — 5 pairs)
 *      6. Time        (s, min, h, day, week — 6 pairs)
 *
 *    Features:
 *      - Nested switch-case menus
 *      - Full input validation
 *      - Coloured terminal output (ANSI codes)
 *      - Conversion history (last 5 stored in array)
 *      - Repeat same conversion without re-selecting
 *
 *  Compile:  gcc unit_converter_pro.c -o unit_converter_pro -lm
 *  Run:      ./unit_converter_pro
 * ================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>     /* for fabs() */

/* ── ANSI Colour Codes ─────────────────────────────── */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define BG_DK   "\033[40m"

/* ── History storage ──────────────────────────────── */
#define MAX_HIST 5

typedef struct {
    char from_str[40];
    char to_str[40];
    char formula[80];
} HistoryEntry;

HistoryEntry history[MAX_HIST];
int hist_count = 0;

/* ── Function Prototypes ─────────────────────────── */
void printHeader(const char *title, const char *color);
void printLine(const char *color);
void printMenu();
void clearScreen();
void addToHistory(const char *from, const char *to, const char *formula);
void showHistory();
int  readDouble(double *out);
void printResult(const char *from_str, const char *to_str,
                 const char *formula, const char *type_color);
void convertTemperature();
void convertDistance();
void convertMass();
void convertSpeed();
void convertArea();
void convertTime();

/* ================================================================
   MAIN
================================================================ */
int main() {
    int choice;

    clearScreen();

    while (1) {

        printMenu();
        printf("  " BOLD "Enter choice: " RESET);

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf(RED "  [ERROR] Enter a number between 0 and 7.\n" RESET);
            printf("  Press ENTER to continue...");
            getchar(); getchar();
            clearScreen();
            continue;
        }
        while (getchar() != '\n'); /* flush buffer */

        switch (choice) {
            case 1: convertTemperature(); break;
            case 2: convertDistance();    break;
            case 3: convertMass();        break;
            case 4: convertSpeed();       break;
            case 5: convertArea();        break;
            case 6: convertTime();        break;
            case 7: showHistory();        break;
            case 0:
                printf(GREEN "\n  Goodbye! Keep learning. 🚀\n\n" RESET);
                exit(0);
            default:
                printf(RED "  [ERROR] Invalid choice! Enter 0–7.\n" RESET);
        }

        printf("\n  " CYAN "Press ENTER to return to menu..." RESET);
        getchar();
        clearScreen();
    }

    return 0;
}

/* ================================================================
   MAIN MENU
================================================================ */
void printMenu() {
    printf(BG_DK);
    printHeader("UNIT CONVERTER PRO — CLASS 11 CS", CYAN);
    printf("  " BOLD WHITE "Select a category:\n\n" RESET);
    printf("  " YELLOW "[1]" RESET " 🌡️  Temperature  (°C, °F, K)\n");
    printf("  " CYAN   "[2]" RESET " 📏  Distance     (m, km, cm, ft, mi)\n");
    printf("  " MAGENTA "[3]" RESET " ⚖️  Mass         (kg, g, lb, mg, t)\n");
    printf("  " YELLOW "[4]" RESET " 💨  Speed        (m/s, km/h, mph)\n");
    printf("  " GREEN  "[5]" RESET " 📐  Area         (m², cm², ft², ha)\n");
    printf("  " MAGENTA "[6]" RESET " ⏱️  Time         (s, min, h, day, week)\n");
    printLine(WHITE);
    printf("  " BLUE   "[7]" RESET " 📋  View History (last %d conversions)\n", MAX_HIST);
    printf("  " RED    "[0]" RESET " ❌  Exit\n");
    printLine(WHITE);
}

/* ================================================================
   TEMPERATURE CONVERTER
   Pairs: C↔F, C↔K, F↔K, K↔C, F↔C
================================================================ */
void convertTemperature() {
    int dir;
    double value, result;
    char from_str[40], to_str[40], formula[80];

    printHeader("TEMPERATURE CONVERSION", YELLOW);
    printf("  [1] Celsius    -> Fahrenheit\n");
    printf("  [2] Fahrenheit -> Celsius\n");
    printf("  [3] Celsius    -> Kelvin\n");
    printf("  [4] Kelvin     -> Celsius\n");
    printf("  [5] Fahrenheit -> Kelvin\n");
    printLine(YELLOW);
    printf("  Direction (1-5): ");

    if (scanf("%d", &dir) != 1 || dir < 1 || dir > 5) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter a number 1-5.\n" RESET); return;
    }
    while(getchar()!='\n');

    printf("  Enter value: ");
    if (scanf("%lf", &value) != 1) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter a valid number.\n" RESET); return;
    }
    while(getchar()!='\n');

    switch(dir) {
        case 1:
            result = (value * 9.0/5.0) + 32.0;
            snprintf(from_str, 40, "%.4g °C",  value);
            snprintf(to_str,   40, "%.4g °F",  result);
            snprintf(formula,  80, "F = (C x 9/5) + 32");
            break;
        case 2:
            result = (value - 32.0) * 5.0/9.0;
            snprintf(from_str, 40, "%.4g °F",  value);
            snprintf(to_str,   40, "%.4g °C",  result);
            snprintf(formula,  80, "C = (F - 32) x 5/9");
            break;
        case 3:
            result = value + 273.15;
            snprintf(from_str, 40, "%.4g °C",  value);
            snprintf(to_str,   40, "%.4g K",   result);
            snprintf(formula,  80, "K = C + 273.15");
            break;
        case 4:
            result = value - 273.15;
            snprintf(from_str, 40, "%.4g K",   value);
            snprintf(to_str,   40, "%.4g °C",  result);
            snprintf(formula,  80, "C = K - 273.15");
            break;
        case 5:
            result = (value - 32.0) * 5.0/9.0 + 273.15;
            snprintf(from_str, 40, "%.4g °F",  value);
            snprintf(to_str,   40, "%.4g K",   result);
            snprintf(formula,  80, "K = (F-32) x 5/9 + 273.15");
            break;
    }

    printResult(from_str, to_str, formula, YELLOW);
    addToHistory(from_str, to_str, formula);
}

/* ================================================================
   DISTANCE CONVERTER
================================================================ */
void convertDistance() {
    int dir;
    double value, result;
    char from_str[40], to_str[40], formula[80];

    printHeader("DISTANCE CONVERSION", CYAN);
    printf("  [1] Meter       -> Kilometer\n");
    printf("  [2] Kilometer   -> Meter\n");
    printf("  [3] Meter       -> Centimeter\n");
    printf("  [4] Meter       -> Feet\n");
    printf("  [5] Kilometer   -> Mile\n");
    printf("  [6] Centimeter  -> Inch\n");
    printLine(CYAN);
    printf("  Direction (1-6): ");

    if (scanf("%d", &dir) != 1 || dir < 1 || dir > 6) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter 1-6.\n" RESET); return;
    }
    while(getchar()!='\n');

    printf("  Enter value: ");
    if (scanf("%lf", &value) != 1) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Invalid number.\n" RESET); return;
    }
    while(getchar()!='\n');

    if (value < 0) {
        printf(RED "  [ERROR] Distance cannot be negative!\n" RESET); return;
    }

    switch(dir) {
        case 1:
            result = value / 1000.0;
            snprintf(from_str, 40, "%.6g m",  value);
            snprintf(to_str,   40, "%.6g km", result);
            snprintf(formula,  80, "km = m / 1000");
            break;
        case 2:
            result = value * 1000.0;
            snprintf(from_str, 40, "%.6g km", value);
            snprintf(to_str,   40, "%.6g m",  result);
            snprintf(formula,  80, "m = km x 1000");
            break;
        case 3:
            result = value * 100.0;
            snprintf(from_str, 40, "%.6g m",  value);
            snprintf(to_str,   40, "%.6g cm", result);
            snprintf(formula,  80, "cm = m x 100");
            break;
        case 4:
            result = value * 3.28084;
            snprintf(from_str, 40, "%.6g m",  value);
            snprintf(to_str,   40, "%.6g ft", result);
            snprintf(formula,  80, "ft = m x 3.28084");
            break;
        case 5:
            result = value * 0.621371;
            snprintf(from_str, 40, "%.6g km", value);
            snprintf(to_str,   40, "%.6g mi", result);
            snprintf(formula,  80, "mi = km x 0.621371");
            break;
        case 6:
            result = value / 2.54;
            snprintf(from_str, 40, "%.6g cm", value);
            snprintf(to_str,   40, "%.6g in", result);
            snprintf(formula,  80, "in = cm / 2.54");
            break;
    }

    printResult(from_str, to_str, formula, CYAN);
    addToHistory(from_str, to_str, formula);
}

/* ================================================================
   MASS CONVERTER
================================================================ */
void convertMass() {
    int dir;
    double value, result;
    char from_str[40], to_str[40], formula[80];

    printHeader("MASS CONVERSION", MAGENTA);
    printf("  [1] Kilogram -> Gram\n");
    printf("  [2] Gram     -> Kilogram\n");
    printf("  [3] Kilogram -> Pound\n");
    printf("  [4] Pound    -> Kilogram\n");
    printf("  [5] Gram     -> Milligram\n");
    printf("  [6] Kilogram -> Metric Ton\n");
    printLine(MAGENTA);
    printf("  Direction (1-6): ");

    if (scanf("%d", &dir) != 1 || dir < 1 || dir > 6) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter 1-6.\n" RESET); return;
    }
    while(getchar()!='\n');

    printf("  Enter value: ");
    if (scanf("%lf", &value) != 1) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Invalid number.\n" RESET); return;
    }
    while(getchar()!='\n');

    if (value < 0) {
        printf(RED "  [ERROR] Mass cannot be negative!\n" RESET); return;
    }

    switch(dir) {
        case 1:
            result = value * 1000.0;
            snprintf(from_str, 40, "%.6g kg", value);
            snprintf(to_str,   40, "%.6g g",  result);
            snprintf(formula,  80, "g = kg x 1000");
            break;
        case 2:
            result = value / 1000.0;
            snprintf(from_str, 40, "%.6g g",  value);
            snprintf(to_str,   40, "%.6g kg", result);
            snprintf(formula,  80, "kg = g / 1000");
            break;
        case 3:
            result = value * 2.20462;
            snprintf(from_str, 40, "%.6g kg", value);
            snprintf(to_str,   40, "%.6g lb", result);
            snprintf(formula,  80, "lb = kg x 2.20462");
            break;
        case 4:
            result = value / 2.20462;
            snprintf(from_str, 40, "%.6g lb", value);
            snprintf(to_str,   40, "%.6g kg", result);
            snprintf(formula,  80, "kg = lb / 2.20462");
            break;
        case 5:
            result = value * 1000.0;
            snprintf(from_str, 40, "%.6g g",  value);
            snprintf(to_str,   40, "%.6g mg", result);
            snprintf(formula,  80, "mg = g x 1000");
            break;
        case 6:
            result = value / 1000.0;
            snprintf(from_str, 40, "%.6g kg", value);
            snprintf(to_str,   40, "%.6g t",  result);
            snprintf(formula,  80, "t = kg / 1000");
            break;
    }

    printResult(from_str, to_str, formula, MAGENTA);
    addToHistory(from_str, to_str, formula);
}

/* ================================================================
   SPEED CONVERTER
================================================================ */
void convertSpeed() {
    int dir;
    double value, result;
    char from_str[40], to_str[40], formula[80];

    printHeader("SPEED CONVERSION", YELLOW);
    printf("  [1] m/s   -> km/h\n");
    printf("  [2] km/h  -> m/s\n");
    printf("  [3] km/h  -> mph\n");
    printf("  [4] mph   -> km/h\n");
    printf("  [5] m/s   -> mph\n");
    printLine(YELLOW);
    printf("  Direction (1-5): ");

    if (scanf("%d", &dir) != 1 || dir < 1 || dir > 5) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter 1-5.\n" RESET); return;
    }
    while(getchar()!='\n');

    printf("  Enter value: ");
    if (scanf("%lf", &value) != 1) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Invalid number.\n" RESET); return;
    }
    while(getchar()!='\n');

    if (value < 0) {
        printf(RED "  [ERROR] Speed cannot be negative!\n" RESET); return;
    }

    switch(dir) {
        case 1:
            result = value * 3.6;
            snprintf(from_str, 40, "%.4g m/s",  value);
            snprintf(to_str,   40, "%.4g km/h", result);
            snprintf(formula,  80, "km/h = m/s x 3.6");
            break;
        case 2:
            result = value / 3.6;
            snprintf(from_str, 40, "%.4g km/h", value);
            snprintf(to_str,   40, "%.4g m/s",  result);
            snprintf(formula,  80, "m/s = km/h / 3.6");
            break;
        case 3:
            result = value * 0.621371;
            snprintf(from_str, 40, "%.4g km/h", value);
            snprintf(to_str,   40, "%.4g mph",  result);
            snprintf(formula,  80, "mph = km/h x 0.621371");
            break;
        case 4:
            result = value / 0.621371;
            snprintf(from_str, 40, "%.4g mph",  value);
            snprintf(to_str,   40, "%.4g km/h", result);
            snprintf(formula,  80, "km/h = mph / 0.621371");
            break;
        case 5:
            result = value * 2.23694;
            snprintf(from_str, 40, "%.4g m/s", value);
            snprintf(to_str,   40, "%.4g mph", result);
            snprintf(formula,  80, "mph = m/s x 2.23694");
            break;
    }

    printResult(from_str, to_str, formula, YELLOW);
    addToHistory(from_str, to_str, formula);
}

/* ================================================================
   AREA CONVERTER
================================================================ */
void convertArea() {
    int dir;
    double value, result;
    char from_str[40], to_str[40], formula[80];

    printHeader("AREA CONVERSION", GREEN);
    printf("  [1] m2   -> cm2\n");
    printf("  [2] m2   -> ft2\n");
    printf("  [3] km2  -> mi2\n");
    printf("  [4] ha   -> m2\n");
    printf("  [5] acre -> m2\n");
    printLine(GREEN);
    printf("  Direction (1-5): ");

    if (scanf("%d", &dir) != 1 || dir < 1 || dir > 5) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter 1-5.\n" RESET); return;
    }
    while(getchar()!='\n');

    printf("  Enter value: ");
    if (scanf("%lf", &value) != 1) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Invalid number.\n" RESET); return;
    }
    while(getchar()!='\n');

    if (value < 0) {
        printf(RED "  [ERROR] Area cannot be negative!\n" RESET); return;
    }

    switch(dir) {
        case 1:
            result = value * 10000.0;
            snprintf(from_str, 40, "%.6g m2",   value);
            snprintf(to_str,   40, "%.6g cm2",  result);
            snprintf(formula,  80, "cm2 = m2 x 10000");
            break;
        case 2:
            result = value * 10.7639;
            snprintf(from_str, 40, "%.6g m2",  value);
            snprintf(to_str,   40, "%.6g ft2", result);
            snprintf(formula,  80, "ft2 = m2 x 10.7639");
            break;
        case 3:
            result = value * 0.386102;
            snprintf(from_str, 40, "%.6g km2", value);
            snprintf(to_str,   40, "%.6g mi2", result);
            snprintf(formula,  80, "mi2 = km2 x 0.386102");
            break;
        case 4:
            result = value * 10000.0;
            snprintf(from_str, 40, "%.6g ha",  value);
            snprintf(to_str,   40, "%.6g m2",  result);
            snprintf(formula,  80, "m2 = ha x 10000");
            break;
        case 5:
            result = value * 4046.86;
            snprintf(from_str, 40, "%.6g acre", value);
            snprintf(to_str,   40, "%.6g m2",   result);
            snprintf(formula,  80, "m2 = acre x 4046.86");
            break;
    }

    printResult(from_str, to_str, formula, GREEN);
    addToHistory(from_str, to_str, formula);
}

/* ================================================================
   TIME CONVERTER
================================================================ */
void convertTime() {
    int dir;
    double value, result;
    char from_str[40], to_str[40], formula[80];

    printHeader("TIME CONVERSION", MAGENTA);
    printf("  [1] Second -> Minute\n");
    printf("  [2] Minute -> Hour\n");
    printf("  [3] Hour   -> Day\n");
    printf("  [4] Second -> Hour\n");
    printf("  [5] Day    -> Week\n");
    printf("  [6] Second -> Millisecond\n");
    printLine(MAGENTA);
    printf("  Direction (1-6): ");

    if (scanf("%d", &dir) != 1 || dir < 1 || dir > 6) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Enter 1-6.\n" RESET); return;
    }
    while(getchar()!='\n');

    printf("  Enter value: ");
    if (scanf("%lf", &value) != 1) {
        while(getchar()!='\n');
        printf(RED "  [ERROR] Invalid number.\n" RESET); return;
    }
    while(getchar()!='\n');

    if (value < 0) {
        printf(RED "  [ERROR] Time cannot be negative!\n" RESET); return;
    }

    switch(dir) {
        case 1:
            result = value / 60.0;
            snprintf(from_str, 40, "%.4g s",   value);
            snprintf(to_str,   40, "%.4g min", result);
            snprintf(formula,  80, "min = s / 60");
            break;
        case 2:
            result = value / 60.0;
            snprintf(from_str, 40, "%.4g min", value);
            snprintf(to_str,   40, "%.4g h",   result);
            snprintf(formula,  80, "h = min / 60");
            break;
        case 3:
            result = value / 24.0;
            snprintf(from_str, 40, "%.4g h",   value);
            snprintf(to_str,   40, "%.4g day", result);
            snprintf(formula,  80, "day = h / 24");
            break;
        case 4:
            result = value / 3600.0;
            snprintf(from_str, 40, "%.4g s", value);
            snprintf(to_str,   40, "%.4g h", result);
            snprintf(formula,  80, "h = s / 3600");
            break;
        case 5:
            result = value / 7.0;
            snprintf(from_str, 40, "%.4g day",  value);
            snprintf(to_str,   40, "%.4g week", result);
            snprintf(formula,  80, "week = day / 7");
            break;
        case 6:
            result = value * 1000.0;
            snprintf(from_str, 40, "%.4g s",  value);
            snprintf(to_str,   40, "%.4g ms", result);
            snprintf(formula,  80, "ms = s x 1000");
            break;
    }

    printResult(from_str, to_str, formula, MAGENTA);
    addToHistory(from_str, to_str, formula);
}

/* ================================================================
   HISTORY
================================================================ */
void addToHistory(const char *from, const char *to, const char *formula) {
    if (hist_count < MAX_HIST) {
        strncpy(history[hist_count].from_str, from,    39);
        strncpy(history[hist_count].to_str,   to,      39);
        strncpy(history[hist_count].formula,  formula, 79);
        hist_count++;
    } else {
        /* Shift entries up (oldest out) */
        int i;
        for (i = 0; i < MAX_HIST - 1; i++) {
            history[i] = history[i + 1];
        }
        strncpy(history[MAX_HIST-1].from_str, from,    39);
        strncpy(history[MAX_HIST-1].to_str,   to,      39);
        strncpy(history[MAX_HIST-1].formula,  formula, 79);
    }
}

void showHistory() {
    printHeader("CONVERSION HISTORY", BLUE);
    if (hist_count == 0) {
        printf("  " YELLOW "No conversions yet! Try converting something first.\n" RESET);
        return;
    }
    int i;
    for (i = 0; i < hist_count; i++) {
        printf("  " CYAN "[%d]" RESET " %s  " GREEN "→" RESET "  %s\n",
               i + 1, history[i].from_str, history[i].to_str);
        printf("      " BLUE "Formula: %s\n" RESET, history[i].formula);
        printLine(WHITE);
    }
}

/* ================================================================
   HELPERS
================================================================ */
void printResult(const char *from_str, const char *to_str,
                 const char *formula,  const char *type_color) {
    printLine(type_color);
    printf("  %s📐 Formula: %s%s\n", type_color, formula, RESET);
    printf("  %s✅ Result : %s  =  %s%s\n", type_color, from_str, to_str, RESET);
    printLine(type_color);
}

void printHeader(const char *title, const char *color) {
    printf("\n");
    printLine(color);
    printf("  %s" BOLD "  %s%s\n" RESET, color, title, RESET);
    printLine(color);
}

void printLine(const char *color) {
    printf("  %s=================================================%s\n", color, RESET);
}

void clearScreen() {
    printf("\033[H\033[J");
}

int readDouble(double *out) {
    return (scanf("%lf", out) == 1);
}
