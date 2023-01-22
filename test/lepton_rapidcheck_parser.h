#ifndef __LEPTON__RAPIDCHECK_PARSER_H__
#define __LEPTON__RAPIDCHECK_PARSER_H__

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace lepton {

class RapidCheckParser {
public:
  RapidCheckParser(const fs::path &config_path);
  std::string parse();

private:
  const fs::path config_path;
};

void init_rapidcheck(char *executable);
} // namespace lepton

#endif // __LEPTON__RAPIDCHECK_PARSER_H__
