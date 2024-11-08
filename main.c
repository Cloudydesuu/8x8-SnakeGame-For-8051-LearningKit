#include <matrix.h>
#include <INTRINS.h>
#include <REG51.h>
#include <Snake.h>

#define COMMONPORTS P0


void main()
{
	unsigned char tab;
	unsigned char i;

	init_game();

	while(1)
	{
		Running_Game();
		// Refresh display
		for(i = 0; i < Speed; i++)
		{
			for(tab = 0; tab < 8; tab++)
			{
				Hc595SendByte(0x00);
				COMMONPORTS = Cols[tab];
				Hc595SendByte(display_buffer[tab]);
				delay(2);
			}
		}
	}
}