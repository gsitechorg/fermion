/* By Dylon Edwards
 */

#ifndef __BARYON__RAPIDCHECK_PARSER_H__
#define __BARYON__RAPIDCHECK_PARSER_H__

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace baryon {

class RapidCheckParser {
public:
  RapidCheckParser(const fs::path &config_path);
  std::string parse();

private:
  const fs::path config_path;
};

void init_rapidcheck(char *executable);
} // namespace baryon

#endif // __BARYON__RAPIDCHECK_PARSER_H__
