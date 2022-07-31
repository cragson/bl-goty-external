#include "ft_enemies_hp.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_enemies_hp::on_enable()
{
	Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::enemies_low_hp + 2, 0x0098 );
}

void ft_enemies_hp::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::enemies_low_hp + 2, 0x0148 );
}
