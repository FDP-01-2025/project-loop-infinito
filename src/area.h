#pragma once
#include <string>

// se usa un struct porque solo se necesita agrupar datos publicos.
struct Area {
    int id;
    std::string name;
    std::string description;
    bool completed;
};