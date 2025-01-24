#include "params/Parameter.hpp"

Parameter::Parameter(ParameterType type, LV2_URID_Map* map, const char* uri, LV2_Atom* atom, uint32_t size, const char* atomUri):
    type_(type),
    uri_(uri)
{
    urid_ = map->map(map->handle, uri_) ;
    value_ = atom ;
    value_->size = sizeof(VALUE_TYPE(ParameterType::AMPLITUDE)) - sizeof(LV2_Atom) ;
    value_->type = map->map(map->handle, atomUri) ;
}

bool Parameter::operator<(const Parameter& other) const {
    return urid_ < other.getURID() ;
}

bool Parameter::operator==(const Parameter& other) const {
    return urid_ == other.getURID() &&
        std::strcmp(uri_,other.getURI()) == 0 &&
        value_ == other.getAtom() ;
}

ParameterType Parameter::getType() const {
    return type_ ;
}

const char* Parameter::getURI() const {
    return uri_ ;
}

LV2_URID Parameter::getURID() const {
    return urid_ ;
}

LV2_Atom* Parameter::getAtom() const {
    return value_ ;
}

template<ParameterType T>
VALUE_TYPE(T) Parameter::getValue() const {
    LV2_ATOM_TYPE(T) atom = reinterpret_cast<LV2_ATOM_TYPE(T)*>(value_);
    VALUE_TYPE(T) v = atom->body ;
    return v ;
}