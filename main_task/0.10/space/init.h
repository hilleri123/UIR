
#pragma once


#define INIT(result, init_class, ...) \
	auto* result = new init_class(__VA_ARGS__);\
	if ( ! result->init() ) {\
		delete result;\
		result = nullptr;\
	}\


class base_init
{
public:
	virtual bool init() const
	{
		return true;
	}


};
