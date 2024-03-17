#include "../include/libs.h"



int main(){

    setup_graphics();
    //set_inputs();

    initialize_chip();
    load_rom();
    emulate_cycle();



    return 0;
}