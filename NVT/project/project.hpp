#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>
#include "library.hpp"

namespace fs = std::filesystem;

typedef int epoch;

class nvt::entity {
public:
    entity(int id = 0) : id{ id } { reset(); }

    std::optional<epoch> creation;
    std::optional<epoch> destruction;

    std::string name{};
    std::string desc{};

    std::set<entity> related();
    std::set<linkage> linkages();

    void write();
    void reset();

private:
    int id;
    int m_chain;
};

class nvt::relation {
public:
    relation(std::string name) : name{ name } { reset(); }

    std::string name;
    std::vector<std::string> overrides{};

    bool breakable;

    std::optional<epoch> creation;
    std::optional<epoch> destruction;

    void write();
    void reset();
};

class nvt::property {
public:
    std::string field{};
    std::variant<int, double, epoch, std::string> record{};

    std::optional<epoch> creation;
    std::optional<epoch> destruction;

private:
    int id;
    int entity;
};

// just for clarification: linkage(husband, wife) -> wife
// so, linkage(n1, n2) returns what n1 perceives n2 to be in relation to them
class nvt::linkage : public std::set<std::tuple<relation, int, epoch, epoch>> {
public:
    linkage(int n1, int n2);

    int N1, N2;

    void write();
    void reset();
};

class nvt::event {
public:
    event(int id = 0) : id{ id } { reset(); }

    std::string name{};
    std::string desc{};

    std::optional<epoch> when;

    std::set<event_chain> chains();

    std::multimap<std::string, std::string> properties{};

    void write();
    void reset();

private:
    int id;
};

class nvt::event_chain : public std::list<event> {
public:
    event_chain(int id = 0) : id{ id } { reset(); }

    void write();
    void reset();

private:
    int id;
    int entity = 0;
};

class nvt::timeline {
public:
    timeline(int id = 0) : id{ id } { reset(); }

    std::set<int> events{};
    std::set<int> chains{};

    void write();
    void reset();

private:
    int id;
};

struct nvt::launch_details {
    std::string name{};
    fs::path location{};
    int last_updated;
};

class nvt::global {
public:
    static int open(fs::path location);
    static int close();
    static global* instance();

    std::list<launch_details> launches();
    void add_launch(launch_details ld);
    void rem_launch(std::string location);

private:
    global(fs::path location);
    ~global();

    static global* m_instance;
    fs::path m_location;
    std::list<launch_details> m_launches{};

    nlohmann::json config_json;
};

class nvt::project {
public:
    static int open(fs::path location);
    static int close();
    static project* instance();

    std::string name();
    void setName(std::string name);

    fs::path location();

    std::list<event>    events   (std::string search_text = "");
    std::list<entity>   entities (std::string search_text = "");
    std::list<timeline> timelines(std::string search_text = "");

private:
    project(fs::path location);
    ~project();

    int setLocation(fs::path location);

    static project* m_instance;

    std::string m_name;
    fs::path m_location;
    fs::path m_config_dir;

    std::unique_ptr<SQLite::Database> db = nullptr;
};
