#ifndef __LV2_PLUGIN_HPP_
#define __LV2_PLUGIN_HPP_

#include <memory> 
#include <string>
#include <vector>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/log/logger.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>

#include "plugin.hpp"
#include PLUG_CONFIG
#include "plugins/PluginResources.hpp"
#include "modules/Module.hpp"

class LV2Plugin {
protected:
    Urids urids_ ;
    LV2_URID_Map uridMap_ ;
    LV2_Atom_Forge forge_ ;
    const LV2_Feature *const *features_ ;

    const double sampleRate_ ;
    PluginState state_ ;
    std::vector<Module::Module*> modules_ ;

public:
    /**
     * @brief LV2Plugin Constructor
     *
     * @param sampleRate host sample rate
     * @param features LV2 features array
     */
    LV2Plugin(const double sampleRate, const LV2_Feature *const *features);

    virtual ~LV2Plugin() = default ;

    // API FUNCTIONS
    virtual void connectPort(const uint32_t port, void* data) = 0 ;
    virtual void activate() = 0 ;
    virtual void run(const uint32_t sampleCount) = 0 ;
    virtual void deactivate() = 0 ;

    // LV2 EXTENSIONS SUPPORT
    // void LV2StateEnabled()

    // FACTORY METHOD TO CREATE DYNAMIC INSTANCE
    static LV2Plugin* create(const std::string& plugin, const double sampleRate, const LV2_Feature *const *features);

    PluginResources getResources();

};

#endif // __LV2_PLUGIN_HPP_