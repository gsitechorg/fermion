/* By Dylon Edwards
 *
 * Copyright 2019 - 2023 GSI Technology, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>

#include <cstdio>
#include <sstream>
#include <stdexcept>

#include <yaml-cpp/yaml.h>

#include "rapidcheck_parser.h"

namespace baryon {

  RapidCheckParser::RapidCheckParser(const std::filesystem::path& config_path)
    : config_path(config_path)
  {}

  std::string RapidCheckParser::parse() {
    std::stringstream ss;

    YAML::Node config = YAML::LoadFile(config_path.c_str());

    if (config["seed"]) {
      ss << "seed=" << config["seed"].as<std::string>() << " ";
    }

    if (config["max_success"]) {
      ss << "max_success=" << config["max_success"].as<std::string>() << " ";
    }

    if (config["max_size"]) {
      ss << "max_size=" << config["max_size"].as<std::string>() << " ";
    }

    if (config["max_discard_ratio"]) {
      ss << "max_discard_ratio=" << config["max_discard_ratio"].as<std::string>() << " ";
    }

    if (config["noshrink"]) {
      ss << "noshrink=" << config["noshrink"].as<std::string>() << " ";
    }

    if (config["verbose_progress"]) {
      ss << "verbose_progress=" << config["verbose_progress"].as<std::string>() << " ";
    }

    if (config["verbose_shrinking"]) {
      ss << "verbose_shrinking=" << config["verbose_shrinking"].as<std::string>() << " ";
    }

    if (config["reproduce"]) {
      ss << "reproduce=" << config["reproduce"].as<std::string>() << " ";
    }

    return ss.str();
  }

  void init_rapidcheck(char* executable) {
    fs::path config_path =
        fs::canonical(executable).parent_path() / "rapidcheck.yml";
    RapidCheckParser config_parser(config_path);
    setenv("RC_PARAMS", config_parser.parse().c_str(), 1);
  }
} // namespace baryon
