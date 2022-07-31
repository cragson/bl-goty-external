#include "ft_max_level.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_max_level::on_enable()
{
	Globals::g_pProcess->write_to_protected_memory< uint8_t >( Offsets::instant_max_level + 3, 0x8B );

	Sleep( 2000 );

	printf( "[>] You should be now max level! :)\n" );

	this->on_disable();
}

void ft_max_level::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint8_t >( Offsets::instant_max_level + 3, 0x93 );
}
