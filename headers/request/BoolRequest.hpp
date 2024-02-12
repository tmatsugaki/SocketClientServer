#pragma once

// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct BoolRequest {
    std::string name;
    bool flag;

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(name), CEREAL_NVP(flag));
    }
};
