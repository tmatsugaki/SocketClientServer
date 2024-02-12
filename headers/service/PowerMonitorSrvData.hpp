#pragma once

// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct PowerMonitorSrvData {
    // State
    bool powerState;       // データソースは 自身
    bool emsState;         // データソースは 自身
    // Mode
    bool powerSaveMode;    // データソースは 自身

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(powerState), CEREAL_NVP(emsState), CEREAL_NVP(powerSaveMode));
    }
};
