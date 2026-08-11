#pragma once

#include <nlohmann/json.hpp>

#include <set>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <variant>
#include <optional>

namespace fs = std::filesystem;

#if defined(PROJECTLIB)
#  define PROJECT_API __declspec(dllexport)
#else
#  define PROJECT_API __declspec(dllimport)
#endif

namespace nvt {
    struct parse_result;
    class story_entry;

    class property;
    class entity;

    class relation;
    struct linkage_element;
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

typedef int epoch;
typedef int nid; // entity id
typedef int vid; // event id
typedef int tid; // timeline id
typedef int cid; // chain id
typedef int rid; // relation id
#define id_null 0

struct nvt::parse_result {
    enum entry_type {
        unknown = 0,
        entity_entry,
        event_entry,
        timeline_entry,
        chain_entry,
        relation_entry
    } type();
    epoch when();
    std::map<std::string, std::string> properties();
    std::set<cid> chains();
    std::list<vid> events();
    nid chain_entity();

    bool error = false;
    int m_type = 0;
};

class nvt::story_entry {
public:
    virtual std::string name() {
        auto r = m_location.filename().replace_extension("").string();
        r.pop_back();
        return r;
    }

    const fs::path& location();
    int move_to(fs::path new_location);

    story_entry(fs::path location);

    virtual void read() {}

    virtual std::string gen_metadata() { return ""; }

    // take the file, take the metadata, merge the two.
    // if any conflicts arise in the existing metadata
    // and new metadata, replace the existing metadata
    // with new metadata
    // 
    // we will use the undefined properties as generics
    // 
    int write(std::string file_contents = "");

    //static entry_type PROJECT_API discern_type(fs::path location);

    static parse_result parse();

private:
    fs::path m_location;
};
