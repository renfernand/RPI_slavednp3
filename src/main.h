#ifndef MAIN_H
#define MAIN_H

#include <atomic>

// variáveis globais declaradas em main.cpp
extern std::atomic<bool> g_button;
extern std::atomic<bool> g_led;


int gpioinit();

#endif