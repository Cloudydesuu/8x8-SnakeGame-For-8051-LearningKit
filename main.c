#include <matrix.h>
#include <REG51.h>
#include <Snake.h>

#define COMMONPORTS P0

void resetGame()
{
    init_game();
}

void showGameOverScreen() {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        display_buffer[i] = 0x00;  
    }
    delay(2000);  // 
    while (1) {
        if (UE == 0) { 
            init_game();
            return;
        } else if (SHITA == 0) {  
            while (1);  
        }
    }
}

void main()
{
    unsigned char tab, i;

    init_game();

    while(1)
    {
        Running_Game();

        for (i = 0; i < Speed; i++)
        {
            for (tab = 0; tab < 8; tab++)
            {
                Hc595SendByte(0x00);
                COMMONPORTS = Cols[tab];
                Hc595SendByte(display_buffer[tab]);
                delay(2);
            }
        }

        if (snake_length == 63) {
            showGameOverScreen();
        }
    }
}
