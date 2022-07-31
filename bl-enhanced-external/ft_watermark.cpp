#include "ft_watermark.hpp"

#include "globals.hpp"

void ft_watermark::on_render()
{
	Globals::g_pOverlay->draw_rect( 10, 20, 285, 21, 255, 0, 0 );

	Globals::g_pOverlay->draw_string( "osmium: Borderlands GOTY Enhanced", 12, 22, 255, 255, 255 );
}
