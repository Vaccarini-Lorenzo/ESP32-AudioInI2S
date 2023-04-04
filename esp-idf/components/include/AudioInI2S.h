//
// Created by Lorenzo Vaccarini on 04/04/23.
//

#ifndef ESP32_AUDIOINI2S_AUDIOINI2S_H
#define ESP32_AUDIOINI2S_AUDIOINI2S_H

#include <driver/i2s.h>

class AudioInI2S {
public:
    AudioInI2S(gpio_num_t bck_pin, gpio_num_t ws_pin, gpio_num_t data_pin, gpio_num_t channel_pin = GPIO_NUM_NC, i2s_channel_fmt_t channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT);
    void read(int32_t _samples[]);
    void begin(int sample_size, int sample_rate = 44100, i2s_port_t i2s_port_number = I2S_NUM_0);

private:
    gpio_num_t _bck_pin;
    gpio_num_t _ws_pin;
    gpio_num_t _data_pin;
    gpio_num_t _channel_pin;
    i2s_channel_fmt_t _channel_format;
    int _sample_size;
    int _sample_rate;
    i2s_port_t _i2s_port_number;

    i2s_config_t _i2s_config = {
            .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
            .sample_rate = 0, // set in begin()
            .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
            .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
            .communication_format = I2S_COMM_FORMAT_STAND_I2S,
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_desc_num = 4,
            .dma_frame_num = 0, // set in begin()
            .use_apll = false,
            .tx_desc_auto_clear = false,
            .fixed_mclk = 0};

    i2s_pin_config_t _i2s_mic_pins = {
            .bck_io_num = I2S_PIN_NO_CHANGE, // set in begin()
            .ws_io_num = I2S_PIN_NO_CHANGE,  // set in begin()
            .data_out_num = I2S_PIN_NO_CHANGE,
            .data_in_num = I2S_PIN_NO_CHANGE // set in begin()
    };
};

#endif //ESP32_AUDIOINI2S_AUDIOINI2S_H
