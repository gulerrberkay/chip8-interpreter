#include "../include/libs.h"



int main(){

    initialize_chip();
    load_rom();
    setup_graphics();
    //set_inputs();

    
    

    int i = 100;
    while(i>0){
        emulate_cycle();
        i--;
    }
    



    return 0;
}