#include "plugins/LV2Plugin.hpp"
#include "plugins/BasicFilter.hpp"

#include "plugin.hpp"

// update factory function with any supported plugin
LV2Plugin* LV2Plugin::create(const std::string& plugin, const double sampleRate, const LV2_Feature *const *features){
    LV2Plugin* p = nullptr ;
    if (plugin == PLUG_STRING_BASIC_FILTER){
        p = new BasicFilter(sampleRate, features);
        return p ;
    }
}

LV2Plugin::LV2Plugin(const double sampleRate, const LV2_Feature *const *features):
    uridMap_(),
    forge_(),
    features_(features),
    sampleRate_(sampleRate),
    state_()
{}

PluginResources LV2Plugin::getResources(){
        PluginResources r ;
        r.forge = &forge_ ;
        r.state = &state_ ;
        r.uridMap = &uridMap_ ;
        r.urids = &urids_ ;
        return r ;
    }