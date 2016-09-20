#pragma once
#include <cstdint>

struct SimpleColor {
	
	SimpleColor() : r(0), g(0), b(0), a(0) {}
	SimpleColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	uint32_t r;
	uint32_t g;
	uint32_t b;
	uint32_t a;

	//We should add on demand methods to transform color spaces, etc...

	static const SimpleColor Black;
	static const SimpleColor White;
	static const SimpleColor Red;
	static const SimpleColor Green;
	static const SimpleColor Blue;
	static const SimpleColor Yellow;
	
};
