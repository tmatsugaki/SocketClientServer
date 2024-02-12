#pragma once

// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct IMUSrvData {
    double roll;
    double pitch;

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(roll), CEREAL_NVP(pitch));
    }
};
