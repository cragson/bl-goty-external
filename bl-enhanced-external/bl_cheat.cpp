#include "bl_cheat.hpp"

#include "ft_click_skill.hpp"
#include "ft_enemies_hp.hpp"
#include "ft_max_cash.hpp"
#include "ft_max_level.hpp"
#include "ft_watermark.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "offsets.hpp"

bool bl_cheat::setup_features()
{
	auto mark = std::make_unique< ft_watermark >();
	mark->set_name( L"Watermark" );
	mark->set_print_status( false );
	mark->set_activation_delay( 420 );
	mark->enable_drawing();
	mark->set_status( true );
	mark->set_virtual_key_code( VK_F1 );

	this->m_features.push_back( std::move( mark ) );

	auto max_level = std::make_unique< ft_max_level >();
	max_level->set_name( L"Instant Max Level" );
	max_level->set_print_status( false );
	max_level->set_activation_delay( 1000 );
	max_level->disable_drawing();
	max_level->set_status( false );
	max_level->set_virtual_key_code( VK_NUMPAD1 );

	this->m_features.push_back( std::move( max_level ) );

	auto click_skill = std::make_unique< ft_click_skill >();
	click_skill->set_name( L"Click Skill Max" );
	click_skill->set_print_status( true );
	click_skill->set_activation_delay( 420 );
	click_skill->disable_drawing();
	click_skill->set_virtual_key_code( VK_NUMPAD2 );

	this->m_features.push_back( std::move( click_skill ) );

	auto cash = std::make_unique< ft_max_cash >();
	cash->set_name( L"Max Cash (Buy/Sell anything)" );
	cash->set_print_status( true );
	cash->set_activation_delay( 420 );
	cash->disable_drawing();
	cash->set_virtual_key_code( VK_NUMPAD3 );

	this->m_features.push_back( std::move( cash ) );

	auto hp = std::make_unique< ft_enemies_hp >();
	hp->set_name( L"All Enemies Low HP" );
	hp->set_print_status( true );
	hp->set_activation_delay( 420 );
	hp->disable_drawing();
	hp->set_virtual_key_code( VK_NUMPAD4 );

	this->m_features.push_back( std::move( hp ) );

	return true;
}

bool bl_cheat::setup_offsets()
{
	if( !Globals::g_pProcess->does_image_exist_in_map( L"BorderlandsGOTY.exe" ) )
		return false;

	const auto image = Globals::g_pProcess->get_image_ptr_by_name( L"BorderlandsGOTY.exe" );

	if( !image )
		return false;

	const auto max_level = image->find_pattern( L"F3 0F 11 93 98 00 00 00 F3 0F 10 43", false );

	if( !max_level )
		return false;

	Offsets::instant_max_level = max_level;

	const auto click_skill = image->find_pattern( L"29 07 8B 07 48 8B 5C 24 40", false );

	if( !click_skill )
		return false;

	Offsets::click_max_skill = click_skill;

	const auto cash = image->find_pattern( L"41 0F B6 41 60 41 8B", false );

	if( !cash )
		return false;

	Offsets::max_cash = cash;

	const auto lowhp = image->find_pattern( L"89 83 48 01 00 00 8B 83 98", false );

	if( !lowhp )
		return false;

	Offsets::enemies_low_hp = lowhp;

	return true;
}

void bl_cheat::print_features()
{
	printf( "\n" );

	printf( "Feature-Name -> Feature-Hotkey\n" );

	for( const auto& feature : this->m_features )
		printf(
			"[>] %-25ws -> %s\n",
			feature->get_name().c_str(),
			utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str()
		);

	printf( "\n" );
}

void bl_cheat::print_offsets()
{
	printf( "\n" );

	const auto msg = []( const std::string& name, const std::uintptr_t value )
	{
		printf( "[>] %-35s -> 0x%llX\n", name.c_str(), value );
	};

	msg( "Instant Max Level", Offsets::instant_max_level );
	msg( "Click Skill Max", Offsets::click_max_skill );
	msg( "Max Cash", Offsets::max_cash );
	msg( "All Enemies Low HP", Offsets::enemies_low_hp );

	printf( "\n" );
}

void bl_cheat::run()
{
	for( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if( GetAsyncKeyState( feature->get_virtual_key_code() ) & 0x8000 )
			feature->toggle();

		// let the feature tick() when active
		if( feature->is_active() )
			feature->tick();
	}
}

void bl_cheat::shutdown()
{
	// disable every feature here
	for( const auto& feature : this->m_features )
		if( feature->is_active() )
			feature->disable();

	// clear image map here
	if( Globals::g_pProcess )
		Globals::g_pProcess->clear_image_map();
}
