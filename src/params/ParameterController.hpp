#ifndef __PARAMETER_CONTROLLER_HPP_
#define __PARAMETER_CONTROLLER_HPP_

#include "params/ParameterObserver.hpp"
#include "params/Parameter.hpp"
#include "plugin.hpp"
#include PLUG_CONFIG

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>

#include <cstring>
#include <vector>


class ParameterController {
private:
    const LV2_Feature *const *features_ ;
    LV2_Atom_Forge* forge_ ;
    Urids* urids_ ;
    LV2_URID_Map* map_ ;

    std::vector<Parameter> dict_ ;
    PluginState State_ ;

    std::vector<ParameterObserver*> observers_ ;

public:
    // CONSTRUCTORS
    /**
     * @brief ParameterController default constructor
     *
     */
    ParameterController();

    // ACTIVATION FUNCTIONS

    /**
     * @brief Initialize
     *
     * @param forge LV2 atom forge
     * @param map LV2 URID map
     * @param urids Urids object
     */
    void initialize(const LV2_Feature *const *features ,LV2_Atom_Forge* forge, LV2_URID_Map* map, Urids* urids) ;

    /**
     * @brief add parameter to controller
     * 
     */
    void addParameter(Parameter parameter) ;
    
    /**
     * @brief register an observer to the ParameterController. Only run during initialization/activation stages
     *
     * @param observer
     */
    void registerObserver(ParameterObserver* observer);

    // LV2 PATCH/STATE HANDLING

    /**
     * @brief checks if specified input event is a patch event
     *
     * @param ev
     */
    bool isPatchEvent(const LV2_Atom_Object* obj) ;

    /**
     * @brief Handle input event
     *
     * @param obj LV2 Atom object
     * @param frames LV2 event->time.frames
     */
    void handleEvent(const LV2_Atom_Object* obj, long frames) ;

    /**
     * @brief save current state
     * see https://lv2plug.in/c/html/group__state.html#LV2_State_Interface
     */
    LV2_State_Status saveState(
            LV2_State_Store_Function  store,
            LV2_State_Handle          handle,
            uint32_t                  flags,
            const LV2_Feature* const* features
    );

    /**
     * @brief restore state to saved state
     * see https://lv2plug.in/c/html/group__state.html#LV2_State_Interface
     */
    LV2_State_Status restoreState(
            LV2_State_Retrieve_Function retrieve,
            LV2_State_Handle            handle,
            uint32_t                    flags,
            const LV2_Feature* const*   features
    );

    // PARAMETER HANDLING

    /**
     * @brief gets the atom corresponding to a State Item
     *
     * @param key
     * @return LV2_Atom*
     */
    LV2_Atom* getParameter(LV2_URID key) const ;

    template<ParameterType T>
    VALUE_TYPE(T) getParameterValue() const ;

    /**
     * @brief function to notify observers of a parameter change
     *
     */
    void notifyObservers(const Parameter* item) const ;

private:
    /**
     * @brief send notifies for all state items with specified observer
     *
     * @param observer observer class instance
     */
    void syncObserver(ParameterObserver* observer) const ;

    /**
     * @brief makes sure an atom object message subject is valid for this plugin
     *
     * @param subject atom object subject
     */
    bool isValidSubject(const LV2_Atom_URID* subject);

    /**
     * @brief Sets the state for a given atom
     *
     * @param key property URID
     * @param size value variable size
     * @param type value variable type (URID)
     * @param body pointer to LV2_Atom body
     * @return LV2_State_Status
     */
    LV2_State_Status setParameter(LV2_URID key, uint32_t size, LV2_URID type, const void* body) const ;

    /**
     * @brief Save property to state using specified store function.
     *
     * @param mapPath LV2 State map path
     * @param saveStatus save status
     * @param store LV2_State_Store_Function (comes from LV2 host or defined for internal functions)
     * @param key property urid
     * @param value atom object pointer
     */
    void storeStateProperty(
        LV2_State_Map_Path*      mapPath,
        LV2_State_Status*        saveStatus,
        LV2_State_Store_Function store,
        LV2_State_Handle         handle,
        LV2_URID                 key,
        const LV2_Atom*          value
    );

    /**
     * @brief write State properties to forge
     *
     * @param mapPath pointer to LV2_State_Map_Path
     * @param key target LV2_URID
     * @param value stored LV2_ATOM object
     */
    void writeToForge(
        LV2_State_Map_Path* mapPath,
        LV2_URID key,
        const LV2_Atom* value
    );

    /**
     * @brief restore a state property
     *
     * @param status LV2_State_Status pointer
     * @param retrieve retrieve function
     * @param handle host handle object
     * @param key LV2_URID
     */
    void restoreStateProperty(
        LV2_State_Status*           status,
        LV2_State_Retrieve_Function retrieve,
        LV2_State_Handle            handle,
        LV2_URID                    key
    );

    /**
     * @brief
     *
     * @param ev
     */
    void handleGetEvent(const LV2_Atom_Object* obj, long frames) ;
    void handleSetEvent(const LV2_Atom_Object* obj, long frames) ;
    void handlePutEvent(const LV2_Atom_Object* obj, long frames) ;
} ;
#endif // __PARAMETER_CONTROLLER_HPP_
