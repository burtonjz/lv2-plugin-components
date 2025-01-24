#ifndef __PARAMETER_HPP_
#define __PARAMETER_HPP_

#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <cstring>

#include "params/ParameterType.hpp"

#define VALUE_TYPE(T)    typename ParameterTypeTraits<T>::ValueType 
#define LV2_ATOM_TYPE(T) typename ParameterTypeTraits<T>::LV2AtomType

class Parameter {
private:
    const ParameterType type_ ;
    const char* uri_ ;
    LV2_URID urid_ ;
    LV2_Atom* value_ ;

public:
    Parameter(ParameterType type, LV2_URID_Map* map, const char* uri, LV2_Atom* atom, uint32_t size, const char* atomUri);

    // OPERATOR OVERRIDES FOR 
    bool operator<(const Parameter& other) const ;

    bool operator==(const Parameter& other) const ;

    // GETTERS / SETTERS
    ParameterType getType() const ;
    const char* getURI() const ;
    LV2_URID getURID() const ;
    LV2_Atom* getAtom() const ;
    
    template<ParameterType T>
    VALUE_TYPE(T) getValue() const ;

} ;

#endif // __PARAMETER_HPP_
