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

#define BT1_PIN 17
#define BT2_PIN 4
#define BT3_PIN 18
#define BT4_PIN 27

#define LED1_PIN 22
#define LED2_PIN 23
#define LED3_PIN 24
#define LED4_PIN 25


struct GpioCtx
{
    gpiod_chip* chip = nullptr;
    gpiod_line* line_btn1 = nullptr;
    gpiod_line* line_btn3 = nullptr;
    gpiod_line* line_btn4 = nullptr;
    gpiod_line* line_led1 = nullptr;
    gpiod_line* line_led3 = nullptr;
    gpiod_line* line_led4 = nullptr;

    bool init()
    {
        chip = gpiod_chip_open_by_name("gpiochip0");
        if (!chip) return false;

        line_btn1 = gpiod_chip_get_line(chip, BT1_PIN);
        line_btn3 = gpiod_chip_get_line(chip, BT3_PIN);
        line_btn4 = gpiod_chip_get_line(chip, BT4_PIN);

        line_led1 = gpiod_chip_get_line(chip, LED1_PIN);
        line_led3 = gpiod_chip_get_line(chip, LED3_PIN);
        line_led4 = gpiod_chip_get_line(chip, LED4_PIN);

        //if (!line_btn || !line_led) return false;

        // Botão: entrada (com pull-up/down feito via hardware ou overlay; libgpiod não "liga pull-up" no Pi clássico)
        if (gpiod_line_request_input(line_btn1, "dnp3-btn1") < 0) 
            return false;
        if (gpiod_line_request_input(line_btn3, "dnp3-btn3") < 0) 
            return false;
        if (gpiod_line_request_input(line_btn4, "dnp3-btn4") < 0) 
            return false;

        // LED: saída
        if (gpiod_line_request_output(line_led1, "dnp3-led1", 0) < 0) 
            return false;
        if (gpiod_line_request_output(line_led3, "dnp3-led3", 0) < 0) 
            return false;
        if (gpiod_line_request_output(line_led4, "dnp3-led4", 0) < 0) 
            return false;

        return true;
    }

    void set_led(uint8_t pos, bool on)
    {
        switch (pos){
            case 1:
                if (line_led1) 
                    gpiod_line_set_value(line_led1, on ? 1 : 0);
            break;
            case 3:
                if (line_led3) 
                    gpiod_line_set_value(line_led3, on ? 1 : 0);
            break;
            case 4:
                if (line_led4) 
                    gpiod_line_set_value(line_led4, on ? 1 : 0);
            break;
            default:
            break;
        }
    }

    int read_btn(uint8_t pos)
    {
        switch (pos){
            case 1:
                return line_btn1 ? gpiod_line_get_value(line_btn1) : -1;
            break;
            case 3:
                return line_btn3 ? gpiod_line_get_value(line_btn3) : -1;
            break;
            case 4:
                return line_btn4 ? gpiod_line_get_value(line_btn4) : -1;
            break;
            default:
                return 0;
            break;
        }

        return 0;
    }

    void close()
    {
        if (chip) gpiod_chip_close(chip);
        chip = nullptr;
        line_btn1 = nullptr;
        line_btn3 = nullptr;
        line_btn4 = nullptr;
        
        line_led1 = nullptr;
        line_led3 = nullptr;
        line_led4 = nullptr;
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
    bool last[3] = {false,false,false};
    int stable[3] = {0,0,0};
    bool val[3] = {false,false,false};
    int pos=0;
    int i=0;

    while (true)
    {
        for (i=0; i<3;i++){

            if (i==0)
                pos=i+1;
            else
                pos=i+2;

            val[i] = gpio->read_btn(pos);
            if (val[i] >= 0) {
                bool now = (val[i] != 0);

                // debounce simples: precisa repetir 3 leituras iguais
                if (now == last[i]) 
                   stable[i]++;
                else 
                   stable[i] = 0;
                
                if (stable[i] >= 3) {
                    stable[i] = 0;
                    g_button.store(now);
                    g_led.store(now);
                    gpio->set_led(pos, now);
                }
                last[i] = now;
            }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

}
