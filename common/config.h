#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <memory>
#include <string>

#include <yaml-cpp/yaml.h>

class Config {
public:
    static YAML::Node commonNode;
    static YAML::Node yamlNode;

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

#endif
