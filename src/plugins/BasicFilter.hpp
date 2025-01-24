#ifndef __BASIC_FILTER_HPP_
#define __BASIC_FILTER_HPP_

#include "plugins/LV2Plugin.hpp"

class BasicFilter : public LV2Plugin {
private:

public:
    // Constructor
    BasicFilter(const double sampleRate, const LV2_Feature *const *features);
    
    // API FUNCTIONS
    virtual void connectPort(const uint32_t port, void* data) ;
    virtual void activate() ;
    virtual void run(const uint32_t sampleCount) ;
    virtual void deactivate() ;
};

#endif // __BASIC_FILTER_HPP_