#include "resource.h"
#include <utility>
#include <string>

std::unordered_map<int, std::string> Resource::resource_names(NAMES_BY_ID);

Resource::Resource(ResourceId id) : id(id) {}

Resource::Resource(const Resource& other) { this->id = other.id; }

Resource::Resource(Resource&& other) { this->id = std::move(other.id); }

std::string Resource::get_name_by_id(ResourceId id) {
    return resource_names[id];
}

std::string Resource::get_name() { return get_name_by_id(this->id); }

ResourceId Resource::get_id() { return this->id; }

Resource Resource::operator=(const Resource& other) {
    this->id = other.id;
    return *this;
}

bool Resource::operator!=(const Resource& other) const {
    return this->id != other.id;
}

bool Resource::operator==(const Resource& other) const {
    return this->id == other.id;
}
