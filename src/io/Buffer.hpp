#ifndef __IO_BUFFER_HPP_
#define __IO_BUFFER_HPP_

#include <cstddef>
#include <cstring>
#include <utility>

#include "plugin.hpp"
#include PLUG_CONFIG

class Buffer {
private:
    float buffer_[CONFIG_MAX_BUFFER_SIZE] ;
    std::size_t activeSize_ ;

public:
    Buffer():
        buffer_(),
        activeSize_(0)
    {}

    /**
     * @brief reset the buffer
     * 
     */
    void reset(){
        activeSize_ = 0 ;
    }

    /**
     * @brief load data into the buffer
     * 
     * @param input input buffer
     * @param size  input buffer size
     */
    void load(const float* input, std::size_t size){
        activeSize_ = size ;
        std::memcpy(buffer_, input, activeSize_ * sizeof(float));
    }

    /**
     * @brief retrieve data buffer and size in a std::pair
     * 
     */
    std::pair<const float*,std::size_t> get() const {
        return {buffer_, activeSize_} ;
    }
};

#endif // __IO_BUFFER_HPP_