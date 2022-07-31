#include "globals.hpp"

int main()
{
	SetConsoleTitleA( "osmium: Borderlands GOTY Enhanced" );

	printf( "[>] Waiting for the game.." );

	while( !Globals::g_pProcess->setup_process( L"BorderlandsGOTY.exe" ) )
		Sleep( 420 );

	printf( "done!\n" );


	//printf("[>] Preparing the overlay..");

	//while (!Globals::g_pOverlay->initialize(Globals::g_pProcess->get_window_handle()))
	//Sleep(420);

	//printf("done!\n");


	printf( "[>] Preparing the cheat.." );

	while( !Globals::g_pCheat->setup_offsets() )
		Sleep( 420 );

	while( !Globals::g_pCheat->setup_features() )
		Sleep( 420 );

	printf( "done!\n" );

	Globals::g_pCheat->print_offsets();

	Globals::g_pCheat->print_features();


	printf( "Have fun! ;-)\n" );

	while( 0xDEAD != 0xAFFE )
	{
		if( GetAsyncKeyState( VK_END ) & 0x8000 )
			break;

		Globals::g_pCheat->run();

		Sleep( 3 );
	}

	Globals::g_pCheat->shutdown();

	printf( "Goodbye!\n" );

	Sleep( 3000 );

	return EXIT_SUCCESS;
}
