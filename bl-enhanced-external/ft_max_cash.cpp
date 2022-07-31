#include "ft_max_cash.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_max_cash::on_enable()
{
	Globals::g_pProcess->write_to_protected_memory< uint64_t >( Offsets::max_cash, 0x9090FFFFFFFF02C7 );
}

void ft_max_cash::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint64_t >( Offsets::max_cash, 0x088B416041B60F41 );
}
