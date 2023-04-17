//
// Created by Lorenzo Vaccarini on 05/04/23.
//
#include "unity.h"
#include "AudioAnalysis.h"
#include "multi_heap.h"
#define SAMPLE_SIZE         128
#define SAMPLE_RATE         44100
#define BAND_SIZE           8

TEST_CASE("first test", "[ftt]"){
    auto audio_analysis = AudioAnalysis(SAMPLE_SIZE, SAMPLE_RATE, BAND_SIZE);
    audio_analysis.setNoiseFloor(10);       // sets the noise floor
    audio_analysis.normalize(true, 0, 255); // normalize all values to range provided.

    audio_analysis.autoLevel(AudioAnalysis::ACCELERATE_FALLOFF, 1); // uncomment this line to set auto level falloff rate
    audio_analysis.bandPeakFalloff(AudioAnalysis::EXPONENTIAL_FALLOFF, 0.05); // set the band peak fall off rate
    audio_analysis.vuPeakFalloff(AudioAnalysis::EXPONENTIAL_FALLOFF, 0.05);    // set the volume unit peak fall off rate
    printf("audio analysis ok\n");
    int32_t sine_samples[SAMPLE_SIZE] = {0, 62, 125, 186, 248, 308, 367, 424, 480, 534, 586, 636, 683, 727, 769, 807, 843, 875, 903, 928, 950, 967, 981, 991, 997, 999, 998, 992, 983, 969, 952, 931, 906, 878, 846, 811, 773, 732, 688, 641, 592, 540, 486, 431, 373, 315, 255, 193, 132, 69, 7, -55, -117, -179, -241, -301, -360, -418, -474, -528, -580, -630, -678, -722, -764, -803, -839, -871, -900, -926, -947, -966, -980, -990, -997, -999, -998, -993, -984, -971, -954, -933, -909, -881, -850, -816, -778, -737, -693, -647, -598, -546, -493, -437, -380, -321, -261, -200, -139, -76, -14, 48, 110, 172, 234, 294, 354, 411, 468, 522, 575, 625, 672, 717, 760, 799, 835, 868, 897, 923, 945, 964, 978, 989, 996, 999, 998, 994};
    audio_analysis.computeFFT(sine_samples, SAMPLE_SIZE, SAMPLE_RATE);
    float* r = audio_analysis.getReal();
    float* im = audio_analysis.getImaginary();
    for (int i=0; i<SAMPLE_SIZE; i++){
        printf("Real[%d] = %f   ", i, r[i]);
        printf("Img[%d] = %f\n", i, im[i]);

    }
    printf("compute fft ok\n");
    audio_analysis.computeFrequencies();
    printf("frequencies ok\n");
    float* freq = audio_analysis.getBands();
    for (int i=0; i<BAND_SIZE; i++){
        printf("Freq %d = %f\n", i, freq[i]);
    }
}