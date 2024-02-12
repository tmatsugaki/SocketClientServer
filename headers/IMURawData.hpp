#pragma once

// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct IMURawData {
    double fx;
    double fy;
    double mz;

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(fx), CEREAL_NVP(fy), CEREAL_NVP(mz));
    }
};
