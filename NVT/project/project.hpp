#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include "library.hpp"

namespace fs = std::filesystem;

typedef int epoch;
#define epoch_min std::numeric_limits<epoch>().min()

class project::entity {
public:
	entity(int id = 0) : id{ id } { reset(); }

	epoch creation = epoch_min;
	epoch destruction = epoch_min;

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

class project::relation {
public:
	relation(std::string name) : name{ name } { reset(); }

	std::string name;
	std::vector<std::string> overrides{};

	bool breakable;

	epoch creation = epoch_min;
	epoch destruction = epoch_min;

	void write();
	void reset();
};

class project::property {
public:
	std::string field{};
	std::variant<int, double, epoch, std::string> record{};

	epoch creation = epoch_min;
	epoch destruction = epoch_min;

private:
	int id;
	int entity;
};

// just for clarification: linkage(husband, wife) -> wife
// so, linkage(n1, n2) returns what n1 perceives n2 to be in relation to them
class project::linkage : public std::set<std::tuple<relation, int, epoch, epoch>> {
public:
	linkage(int n1, int n2);

	int N1, N2;

	void write();
	void reset();
};

class project::event {
public:
	event(int id = 0) : id{ id } { reset(); }

	std::string name{};
	std::string desc{};

	int id;
	epoch when = epoch_min;

	std::set<event_chain> chains();

	std::multimap<std::string, std::string> properties{};

	void write();
	void reset();
private:
};

class project::event_chain : public std::list<event> {
public:
	event_chain(int id = 0) : id{ id } { reset(); }

	int id;
	int entity = 0;

	void write();
	void reset();
};

class project::timeline {
public:
	timeline(int id = 0) : id{ id } { reset(); }

	int id;

	std::set<int> events{};
	std::set<int> chains{};

	void write();
	void reset();
private:
};

class project::project {
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
