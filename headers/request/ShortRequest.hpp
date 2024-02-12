#pragma once

/******************************************************************************
 * 未使用
 ******************************************************************************/
// for Serialization
#include <iostream>
#include <fstream>
#include <string>

// for Cereal
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

struct ShortRequest {
    std::string name;
    short value;

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(CEREAL_NVP(name), CEREAL_NVP(value));
    }
};
