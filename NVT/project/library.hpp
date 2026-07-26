#pragma once

#include <set>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <variant>

namespace nvt {

    class property;
    class entity;
    class relation;
    class linkage;
    class event;
    class event_chain;
    class timeline;
    struct launch_details;
    class global;
    class project;

    global* global_instance();
}
