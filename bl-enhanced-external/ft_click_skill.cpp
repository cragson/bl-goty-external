#include "ft_click_skill.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_click_skill::on_enable()
{
	Globals::g_pProcess->write_to_protected_memory< uint8_t >( Offsets::click_max_skill, 0x09 );
}

void ft_click_skill::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint8_t >( Offsets::click_max_skill, 0x29 );
}
