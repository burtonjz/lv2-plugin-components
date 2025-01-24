#ifndef __PLUGIN_RESOURCES_HPP_
#define __PLUGIN_RESOURCES_HPP_


#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>

#include "plugin.hpp"
#include PLUG_CONFIG

struct PluginResources {
    LV2_URID_Map* uridMap ;
    Urids* urids ;
    LV2_Atom_Forge* forge ;
    PluginState* state ;
} ;

#endif // __PLUGIN_RESOURCES_HPP_