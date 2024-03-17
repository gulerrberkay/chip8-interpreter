#include "../include/libs.h"


extern unsigned char V[REGS_NUM];

int main(){
    DEBUG_PRINT("Debugging is enabled.\n");

    initialize_chip();
    load_rom();
    setup_graphics();
    //set_inputs();

    
    

    int i = 25;
    while(i>0){
        emulate_cycle();

        if((V[0xF])==1)
            update_screen();


        update_keypad();

        i--;
    }
    


    deinit_screen();
    return 0;
}