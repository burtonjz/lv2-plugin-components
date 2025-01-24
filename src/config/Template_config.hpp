#ifndef __TEMPLATE_CONFIG_HPP_
#define __TEMPLATE_CONFIG_HPP_

#include <cstddef>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>

// These configuration items are required for any config:
constexpr std::size_t CONFIG_NUM_STATE_PARAMETERS = 3 ;
constexpr double      CONFIG_DEFAULT_SAMPLE_RATE = 44100 ;

#endif // __TEMPLATE_CONFIG_HPP_