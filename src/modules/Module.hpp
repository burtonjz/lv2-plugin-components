#ifndef __MODULE_HPP_
#define __MODULE_HPP_

#include "plugins/PluginResources.hpp"
#include "modules/ModuleType.hpp"
#include "params/ParameterController.hpp"
#include "io/Buffer.hpp"

#include <vector>
#include <cstddef>

namespace Module {

    /**
    * @brief the base class for all audio modules
    * 
    * This class provides the framework for module instantiation and common methods/features 
    * that all modules may use. It is templated to require the number of inputs and outputs
    */
    class Module {
    protected:
        std::vector<const Buffer*> inputSignal_ ;
        std::vector<Buffer*> outputSignal_ ;

        PluginResources res_ ;
        ParameterController parameterController_ ;
        double sampleRate_ ;
        ModuleType type_ ;

    public:
        /**
        * @brief Module constructor
        * @param plugReferences plugin-owned object pointers
        * @param sampleRate plugin sample rate
        * @param typ Module Type
        * @param instance Module instance
        * @param numSignalIn number of input signal buffers
        * @param numSignalOut number of output signal buffers
        */
        Module(PluginResources res, double sampleRate, ModuleType typ, size_t numSignalIn, size_t numSignalOut):
            res_(res),
            parameterController_(),
            sampleRate_(sampleRate),
            type_(typ)
        {
            // pre-allocate memory for IO vectors
            for ( size_t i = 0 ; i < numSignalIn ; ++i ) inputSignal_.push_back(nullptr);
            for ( size_t i = 0 ; i < numSignalOut ; ++i ) outputSignal_.push_back(nullptr);
        }

        virtual ~Module() = default ;

        void connectInput(const Buffer* signal, std::size_t index){
            if ( index > inputSignal_.size() )
                return ;
            inputSignal_[index] = signal ;
        }

        void disconnectInput(std::size_t index){
            if ( index > inputSignal_.size() ){
                return ;
            } 
            inputSignal_[index] = nullptr ;
        }

        std::size_t getNumInputs(){
            return inputSignal_.size() ;
        }

        std::size_t getNumOutputs(){
            return outputSignal_.size() ;
        }

        const Buffer* getInput(std::size_t index) const {
            if ( index > inputSignal_.size() ){
                return nullptr ;
            }
            return inputSignal_[index] ;
        }

        Buffer* getOutput(std::size_t index){
            if ( index > inputSignal_.size() ){
                return nullptr ;
            }
            return outputSignal_[index] ;
        }
        
        /**
        * @brief Activate the module. Must be called before real-time processing begins
        * 
        * Modules override this virtual function to perform initialization and setup of the
        * module.
        */
        // virtual void activate() = 0 ;

        /**
        * @brief returns a read-only pointer to the module's sample rate
        */
        double getSampleRate() const {
            return sampleRate_ ;
        }

        /**
        * @brief sets the pointer for the module's sample rate
        */
        void setSampleRate(double sampleRate){
            sampleRate_ = sampleRate ;
        }

        /**
        * @brief get the module type
        */
        ModuleType getType() const {
            return type_ ;
        }
    
        /**
        * @brief get a pointer to the parameterController
        */
        ParameterController* getParameterController(){
            return &parameterController_ ;
        }

        /**
        * @brief increment module for next sample
        */
        virtual void tick(){
        }

    };

}

#endif // __MODULE_HPP_