# Architecture

## Config

## IO

The [io](../src/io) codebase handles all data routing for a given plugin

The [Port Controller](../src/io/PortController.hpp) is responsible for passing LV2 audio and control port data to their appropriate resources. Each plugin MUST have 1 Port Controller, which will be responsible for handling all LV2 [connect_port](https://lv2plug.in/c/html/group__lv2core.html#a4d904937a1bd27cb5f5478f95c708b16) events.

## MIDI
    
The [midi](../src/midi) codebase handles all tracking of midi events. The [KeyboardController](../src/midi/KeyboardController.hpp) serves as the main class. Every plugin that interacts with midi SHOULD have a single controller object. 

MIDI information is internally passed around as a [Note](../src/midi/Note.hpp), which contains all the midi information along with several utilities, such as easily converting from a midi note to a frequency.

MIDI [Modules](#modules) follow an observer pattern, being registered with the controller as a [KeyboardObserver](../src/midi/KeyboardObserver.hpp). Modules can be configured to take action related to a note press or release, or a supported midi control action (such as pitchbend or sustain).



## Modulation

## Modules

The [modules](../src/modules) codebase contains standard modules in the context of modular synthesis. At its core, a module has [parameters](#parameters), a specified number of inputs and outputs...

## Parameters

The [params](../src/params) codebase controls all parameter logic, and supports [LV2 Parameters](https://lv2plug.in/ns/ext/parameters) and [LV2 State](https://lv2plug.in/ns/ext/state), though they can also be connected to a simple [LV2 Control Port](https://lv2plug.in/ns/lv2core#ControlPort). Specific [Plugin](#plugins) parameters should be defined in their respective [config](#config) and [turtle](#turtle) files. 

Plugin parameters are handled by the [ParameterController](../src/params/ParameterController.hpp), with every [Module](#modules) having it's own parameter controller. If configured to be [modulatable](#modulation), each individual parameter will support an input data stream to calculate an "instantaneous" value

## Plugins

## Turtle
