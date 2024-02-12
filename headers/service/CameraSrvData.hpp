#pragma once

// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct CameraSrvData {
    double dx;
    double dy;
    double dtheta;

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(dx), CEREAL_NVP(dy), CEREAL_NVP(dtheta));
    }
};
