#pragma once

#include <set>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <variant>
#include <optional>

namespace nvt {

    class property;
    class entity;
    class relation;
    class linkage;
    class event;
    class event_chain;
    class timeline;
    struct launch_details;
    struct less_launch_details;
    class global;
    class story;

    void log(std::string);
}

#if defined(PROJECTLIB)
#  define PROJECT_API __declspec(dllexport)
#else
#  define PROJECT_API __declspec(dllimport)
#endif

