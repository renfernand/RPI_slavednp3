#include "main.h"
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>

#ifdef GPIOD_SUPPORT
#include <gpiod.h>
#endif

struct GpioCtx
{
    gpiod_chip* chip = nullptr;
    gpiod_line* line_btn = nullptr;
    gpiod_line* line_led = nullptr;

    bool init()
    {
        chip = gpiod_chip_open_by_name("gpiochip0");
        if (!chip) return false;

        line_btn = gpiod_chip_get_line(chip, 17);
        line_led = gpiod_chip_get_line(chip, 22);
        if (!line_btn || !line_led) return false;

        // Botão: entrada (com pull-up/down feito via hardware ou overlay; libgpiod não "liga pull-up" no Pi clássico)
        if (gpiod_line_request_input(line_btn, "dnp3-btn") < 0) return false;

        // LED: saída
        if (gpiod_line_request_output(line_led, "dnp3-led", 0) < 0) return false;

        return true;
    }

    void set_led(bool on)
    {
        if (line_led) gpiod_line_set_value(line_led, on ? 1 : 0);
    }

    int read_btn()
    {
        return line_btn ? gpiod_line_get_value(line_btn) : -1;
    }

    void close()
    {
        if (chip) gpiod_chip_close(chip);
        chip = nullptr;
        line_btn = nullptr;
        line_led = nullptr;
    }
};

static  GpioCtx gpio;

static void ButtonThread(GpioCtx* gpio);


int gpioinit(){

    #ifdef GPIOD_SUPPORT
        if (!gpio.init())
        {
            std::cerr << "Erro inicializando GPIO" << std::endl;
            return -1;
        }

        // Cria thread do botão
        std::thread btnThread(ButtonThread, &gpio);
        btnThread.detach();   // deixa rodando em background
    #endif

    return 0;
}


void ButtonThread(GpioCtx* gpio)
{
    bool last = false;
    int stable = 0;

    while (true)
    {
        int v = gpio->read_btn();
        if (v >= 0)
        {
            bool now = (v != 0);

            // debounce simples: precisa repetir 3 leituras iguais
            if (now == last) stable++;
            else stable = 0;

            if (stable >= 3) {
                stable = 0;
                g_button.store(now);
            }
            last = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
