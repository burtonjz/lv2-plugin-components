#ifndef __PLUGIN_HPP_
#define __PLUGIN_HPP_

#define STRINGIFY(x) #x
#define CAT(X,Y) X##Y

// define plugins
#define BASE_URI "https://github.com/burtonjz/lv2-plugin-components"

#define PLUG_STRING_OSCILLATOR   "Oscillator"
#define PLUG_URI_OSCILLATOR STRINGIFY(BASE_URI "#" PLUG_STRING_OSCILLATOR)

#define PLUG_STRING_BASIC_FILTER "BasicFilter"
#define PLUG_URI_BASIC_FILTER STRINGIFY(BASE_URI "#" PLUG_STRING_BASIC_FILTER)

// The plugin string and config Should be defined by compiler variable, if not default to oscillator
#ifndef PLUG_STRING
#define PLUG_STRING PLUG_STRING_OSCILLATOR
#endif

#ifndef PLUG_CONFIG
#define PLUG_CONFIG "config/Oscillator_config.hpp"
#endif

#define PLUG_URI STRINGIFY(BASE_URI "#" PLUG_STRING)

#endif