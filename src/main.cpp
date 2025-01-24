#include <lv2.h>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>

#include <iostream>

#include "plugins/LV2Plugin.hpp"
#include "plugin.hpp"

static LV2_Handle instantiate(const struct LV2_Descriptor *descriptor, double sample_rate, const char *bundle_path, const LV2_Feature *const *features)
{
    LV2Plugin* p = nullptr ;
    try {
        p = LV2Plugin::create(PLUG_URI, sample_rate, features);
    }
    catch(const std::invalid_argument& ia){
        std::cerr << ia.what() << std::endl ;
        return nullptr ;
    }
    catch(const std::bad_alloc& ba){
        std::cerr << "Failed to allocate memory. Aborting." << std::endl ;
        return nullptr ;
    }
    
    return p ;
}

static void connect_port(LV2_Handle instance, uint32_t port, void *data){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance);
    if (p) p->connectPort (port, data);
}

static void activate(LV2_Handle instance){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance);
    p->activate();
}

static void run(LV2_Handle instance, uint32_t sample_count){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance);

    if (p) p->run (sample_count);
}

static void deactivate (LV2_Handle instance){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance);
    p->deactivate();
}

static void cleanup (LV2_Handle instance){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance);
    if (p) delete p ;
}

// STATE INTERFACE FUNCTIONS
LV2_State_Status save(
    LV2_Handle                instance,
    LV2_State_Store_Function  store,
    LV2_State_Handle          handle,
    uint32_t                  flags,
    const LV2_Feature* const* features
){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance) ;
    ParameterController* pc = p->getParameterController() ;
    return pc->saveState(store, handle, flags, features);
};

LV2_State_Status restore(
    LV2_Handle                  instance,
    LV2_State_Retrieve_Function retrieve,
    LV2_State_Handle            handle,
    uint32_t                    flags,
    const LV2_Feature* const*   features
){
    LV2Plugin* p = static_cast <LV2Plugin*> (instance) ;
    ParameterController* pc = p->getParameterController() ;
    return pc->restoreState(retrieve, handle, flags, features);
};


static const void* extension_data(const char *uri){
    static const LV2_State_Interface state = { save, restore };
    if (!strcmp(uri, LV2_STATE__interface)) return &state ;
    return nullptr ;
}


static LV2_Descriptor const descriptor = {
    PLUG_URI,
    instantiate,
    connect_port,
    activate,
    run,
    deactivate,
    cleanup,
    extension_data
};

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index){
    if (index == 0) return &descriptor ;
    return nullptr ;
};
