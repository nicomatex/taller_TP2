#include "resource.h"

#include <string>
#include <unordered_map>

#include "config.h"

std::string res_name(Resource res) {
  std::unordered_map<Resource, std::string> names(
      {{WHEAT, NM_WHEAT}, {IRON, NM_IRON}, {WOOD, NM_WOOD}, {COAL, NM_COAL}});
  return names[res];
}