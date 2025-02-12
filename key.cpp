#include <iostream>
#ifdef _WIN32
#include <windows.h> // برای ویندوز
//#include "curses.h"
#else
#include <ncurses.h> // برای لینوکس
#endif

void detectKeys() {
    #ifdef _WIN32
    // کد برای ویندوز
    std::cout << "Running on Windows. Press F1-F8, Ctrl+Shift+P, Alt+X, or 'q' to quit.\n";
    while (true) {
        // بررسی کلیدهای F1 تا F8
        for (int i = VK_F1; i <= VK_F12; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                std::cout << "F" << (i - VK_F1 + 1) << " pressed\n";
                Sleep(200); // جلوگیری از تشخیص چندباره
            }
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000){
                std::cout << "UP pressed\n";
                Sleep(200);
        }
          if (GetAsyncKeyState(VK_DOWN) & 0x8000){
                std::cout << "down pressed\n";
                Sleep(200);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
                std::cout << "right pressed\n";
                Sleep(200);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000){
                std::cout << "left pressed\n";
                Sleep(200);
        }
       

        // بررسی ترکیب Ctrl+Shift+P
        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
            (GetAsyncKeyState(VK_SHIFT) & 0x8000) &&
            (GetAsyncKeyState('P') & 0x8000)) {
            std::cout << "Ctrl + Shift + P pressed\n";
            Sleep(200); // جلوگیری از تشخیص چندباره
        }

        // بررسی ترکیب Alt+X
        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && // VK_MENU = کلید Alt
            (GetAsyncKeyState('X') & 0x8000)) {
            std::cout << "Alt + X pressed\n";
            Sleep(200); // جلوگیری از تشخیص چندباره
        }

        // بررسی کلید q برای خروج
        if (GetAsyncKeyState('Q') & 0x8000) {
            std::cout << "'q' pressed. Exiting...\n";
            break;
        }

        Sleep(100); // تأخیر برای جلوگیری از مصرف زیاد CPU
        //noecho();
    }
    #else
    // کد برای لینوکس
    initscr(); // راه‌اندازی ncurses
    cbreak(); // غیرفعال کردن بافر خطی
    noecho(); // غیرفعال کردن اکوی خودکار
    keypad(stdscr, TRUE); // فعال‌سازی کلیدهای ویژه
    timeout(100); // تنظیم زمان انتظار برای دریافت کلید (میلی‌ثانیه)

    printw("Running on Linux. Press F1-F8, Ctrl+Shift+P, Alt+X, or 'q' to quit.\n");
    refresh();

    while (true) {
        int ch = getch(); // دریافت کلید
        if (ch != ERR) { // اگر کلیدی زده شده باشد
            clear(); // پاک کردن صفحه
            if (ch == 'q') { // خروج با کلید q
                printw("'q' pressed. Exiting...\n");
                refresh();
                break;
            } else if (ch == KEY_F(1)) {
                printw("F1 pressed\n");
            } else if (ch == KEY_F(2)) {
                printw("F2 pressed\n");
            } else if (ch == KEY_F(3)) {
                printw("F3 pressed\n");
            } else if (ch == KEY_F(4)) {
                printw("F4 pressed\n");
            } else if (ch == KEY_F(5)) {
                printw("F5 pressed\n");
            } else if (ch == KEY_F(6)) {
                printw("F6 pressed\n");
            } else if (ch == KEY_F(7)) {
                printw("F7 pressed\n");
            } else if (ch == KEY_F(8)) {
                printw("F8 pressed\n");
            } else if (ch == 27) { // کلید Alt (Escape)
                ch = getch(); // دریافت کلید بعدی
                if (ch == 'x' || ch == 'X') {
                    printw("Alt + X pressed\n");
                } else {
                    ungetch(ch); // بازگرداندن کلید به بافر
                }
            } else if (ch == 16) { // Ctrl+P
                ch = getch(); // دریافت کلید بعدی
                if (ch == 'P' || ch == 'p') {
                    printw("Ctrl + Shift + P pressed\n");
                } else {
                    ungetch(ch); // بازگرداندن کلید به بافر
                }
            } else {
                printw("Other key pressed: %d\n", ch);
            }
            refresh();
        } else {
            // اگر هیچ کلیدی زده نشده بود، برنامه کار خود را ادامه می‌دهد
            printw("Working...\n");
            refresh();
        }
    }

    endwin(); // پایان ncurses
    #endif
}

int main() {
    detectKeys(); // تشخیص کلیدها
    return 0;
}