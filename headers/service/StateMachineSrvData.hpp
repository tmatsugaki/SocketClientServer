#pragma once

// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct StateMachineSrvData {
    // Master State
    bool powerState;        // (Power is ON/OFF)       データソースは PowerMonitor
    bool emsState;          // (Emergency Stop State)  データソースは PowerMonitor

    // Sub State
    uint16_t runningState;  // (Running State)         データソースは 自身
    uint16_t imuState;      // (IMU State)             データソースは 自身

    // Mode
    bool powerSaveMode;     // (Power Save Mode)       データソースは PowerMonitor

    // Data
    double fx;              //                         データソースは 自身
    double fy;              //                         データソースは 自身
    double mz;              //                         データソースは 自身

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(powerState), CEREAL_NVP(emsState),
                CEREAL_NVP(runningState), CEREAL_NVP(imuState),
                CEREAL_NVP(powerSaveMode),
                CEREAL_NVP(fx), CEREAL_NVP(fy), CEREAL_NVP(mz));
    }
};
