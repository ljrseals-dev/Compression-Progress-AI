// cross_sense_pattern_hunter.cpp
// C++20 educational implementation of Prompt 3:
// Cross-Sense Pattern Hunter – fuse modalities and measure joint compression gain.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

class CrossSenseHunter {
public:
    void add_modality(const std::string& name, const std::string& data) {
        modalities_[name] = data;
        recompute();
    }

    void recompute() {
        // Unimodal complexity proxy
        unimodal_cost_ = 0.0;
        for (const auto& [name, data] : modalities_) {
            unimodal_cost_ += static_cast<double>(unique_tokens(data).size()) * 4.0;
        }

        // Joint: concatenate and count unique across all
        std::string joint;
        for (const auto& [name, data] : modalities_) joint += " " + data;
        joint_cost_ = static_cast<double>(unique_tokens(joint).size()) * 4.0;

        gain_ = unimodal_cost_ - joint_cost_;
    }

    void report() const {
        std::cout << "\n=== Cross-Sense Compression Report ===\n";
        std::cout << "Modalities loaded: " << modalities_.size() << "\n";
        for (const auto& [n, d] : modalities_) {
            std::cout << "  - " << n << " (" << d.size() << " chars)\n";
        }
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "Unimodal total cost  : " << unimodal_cost_ << "\n";
        std::cout << "Joint cost           : " << joint_cost_ << "\n";
        std::cout << "Compression gain     : " << gain_ << " (positive = useful fusion)\n";
        if (gain_ > 0) {
            std::cout << "Conclusion: joint model is more compressible – keep the fused representation.\n";
        } else {
            std::cout << "Conclusion: little or no gain yet. Request additional aligned observations.\n";
        }
        std::cout << "======================================\n";
    }

private:
    std::map<std::string, std::string> modalities_;
    double unimodal_cost_ = 0.0;
    double joint_cost_ = 0.0;
    double gain_ = 0.0;

    static std::set<std::string> unique_tokens(const std::string& s) {
        std::set<std::string> tokens;
        std::istringstream iss(s);
        std::string t;
        while (iss >> t) {
            for (char& c : t) c = std::tolower(c);
            tokens.insert(t);
        }
        return tokens;
    }
};

int main() {
    std::cout << "Cross-Sense Pattern Hunter (C++20 demo)\n";
    std::cout << "Commands: add <modality_name> <text...> | report | quit\n";
    std::cout << "Example: add vision red rectangular object 2 meters\n";
    std::cout << "         add sound low frequency hum 60Hz\n\n";

    CrossSenseHunter hunter;
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit") break;
        if (line == "report") { hunter.report(); continue; }
        if (line.rfind("add ", 0) == 0) {
            std::istringstream iss(line.substr(4));
            std::string name;
            iss >> name;
            std::string rest;
            std::getline(iss, rest);
            if (!name.empty() && !rest.empty()) {
                hunter.add_modality(name, rest);
                std::cout << "Added modality '" << name << "'.\n";
                hunter.report();
            }
        }
    }
    return 0;
}
