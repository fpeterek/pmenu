#include "load_exec.hpp"

#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <vector>


namespace {

    namespace fs = std::filesystem;

    std::vector<std::string> tokenize(const std::string& path) {
        std::stringstream ss(path);
        std::vector<std::string> res;

        std::string token;

        while (std::getline(ss, token, ':')) {
            res.emplace_back(std::move(token));
        }

        return res;
    }

    std::vector<std::string> loadPath() {
        const char* path = std::getenv("PATH");

        if (path == nullptr) {
            return {};
        }

        return tokenize(path);
    }

    fs::path followSymlink(const fs::path& path) {

        if (fs::is_symlink(path)) {
            return followSymlink(fs::read_symlink(path));
        }

        return path;
    }

    bool isFile(const fs::path& path) {
        return fs::is_regular_file(path);
    }

    std::unordered_map<std::string, std::string> loadExecutables(const std::string& path) {
        std::unordered_map<std::string, std::string> contents;

        for (const auto & entry: fs::directory_iterator(path)) {

            auto file = followSymlink(entry.path());

            if (isFile(file)) {
                contents[entry.path().filename()] = file.string();
            }
        }
        return contents;
    }


    std::unordered_map<std::string, std::string> loadExecutables(const std::vector<std::string>& paths) {
        std::unordered_map<std::string, std::string> res;

        for (const auto& path : paths) {
            if (not fs::exists(path) or not fs::is_directory(path)) {
                continue;
            }
            const auto execs = loadExecutables(path);
            res.insert(execs.begin(), execs.end());
        }

        return res;
    }

}

std::unordered_map<std::string, std::string> loadFromPath() {
    return loadExecutables(loadPath());
}

