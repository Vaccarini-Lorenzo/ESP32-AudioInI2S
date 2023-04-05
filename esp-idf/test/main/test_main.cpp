//
// Created by Lorenzo Vaccarini on 05/04/23.
//

#include "unity.h"

extern "C" void app_main(void){
    printf("Starting unity testing...\n");
    UNITY_BEGIN();
    unity_run_all_tests();
    UNITY_END();
}