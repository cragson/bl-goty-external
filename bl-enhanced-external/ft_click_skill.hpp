#pragma once

#include "osmium/Cheat/Feature/feature.hpp"

class ft_click_skill : public feature
{
public:
	void on_first_activation() override {}

	void on_enable() override;

	void on_disable() override;

	void on_render() override {}

	void tick() override {}
};
