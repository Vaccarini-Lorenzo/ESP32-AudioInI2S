#include <hal/gpio_types.h>
#include "esp_event.h"
#include "nvs_flash.h"
#include "../components/AudioInI2S/include/AudioInI2S.h"
#include "../components/AudioInI2S/include/AudioAnalysis.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#define SAMPLE_SIZE 1024  // Buffer size of read samples
#define SAMPLE_RATE 44100 // Audio Sample Rate

int32_t samples[SAMPLE_SIZE]; // I2S sample data is stored here

extern "C" void app_main(void) {
    // Initialize library to keep persistent data in flash storage
    ESP_ERROR_CHECK(nvs_flash_init());
    // Initialize event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    AudioInI2S mic(GPIO_NUM_4, GPIO_NUM_18, GPIO_NUM_21, GPIO_NUM_19); // defaults to RIGHT channel.
    mic.begin(SAMPLE_SIZE, SAMPLE_RATE); // Starts the I2S DMA port.

    AudioAnalysis audioInfo(SAMPLE_SIZE, SAMPLE_RATE, 8);
    audioInfo.setNoiseFloor(10);       // sets the noise floor
    audioInfo.normalize(true, 0, 255); // normalize all values to range provided.

    // audioInfo.autoLevel(AudioAnalysis::ACCELERATE_FALLOFF, 1); // uncomment this line to set auto level falloff rate
    audioInfo.bandPeakFalloff(AudioAnalysis::EXPONENTIAL_FALLOFF, 0.05); // set the band peak fall off rate
    audioInfo.vuPeakFalloff(AudioAnalysis::EXPONENTIAL_FALLOFF, 0.05);    // set the volume unit peak fall off rate
    float old_v = 0;

    while(1){
        mic.read(samples);
        audioInfo.computeFFT(samples, SAMPLE_SIZE, SAMPLE_RATE);
        audioInfo.computeFrequencies(BAND_SIZE);

        //float *bands = audioInfo.getBands();
        //float *peaks = audioInfo.getPeaks();
        //float vuMeterPeak = audioInfo.getVolumeUnitPeak();

        float vuMeter = audioInfo.getVolumeUnit();

        if(old_v + 40 < vuMeter || old_v - 40 > vuMeter){
            ESP_LOGI("A", "Volume = %f\n", vuMeter);
            old_v = vuMeter;
        }

    }
}
