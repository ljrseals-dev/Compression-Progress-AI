// sensory_compression_tutor.cpp
// C++20 educational implementation of Prompt 1:
// Sensory Compression Tutor – store history, measure compression progress, propose next action.
// Demonstrates Schmidhuber-style compression-progress drive on text sensory logs.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

class HistoryCompressor {
public:
    void store(const std::string& observation) {
        history_.push_back(observation);
        // crude “compression”: count unique tokens + length of concatenated unique runs
        update_model();
    }

    double current_complexity() const {
        // proxy for description length: unique token count + residual entropy estimate
        return static_cast<double>(unique_tokens_.size()) * 8.0 + residual_;
    }

    double progress() const {
        if (prev_complexity_ <= 0.0) return 0.0;
        return prev_complexity_ - current_complexity();
    }

    std::string propose_next_action() const {
        // Simple heuristic: if residual high, ask for more detail on last modality;
        // if low, ask for a new modality or verification.
        if (residual_ > 50.0) {
            return "Request higher-resolution detail or repeated observation of the last sensory channel to reduce residual uncertainty.";
        }
        if (history_.size() < 3) {
            return "Provide a second sensory modality (e.g., sound or tactile) so joint compression can be attempted.";
        }
        return "Propose a low-cost action that is predicted to produce novel but learnable regularity (e.g., move slightly and re-observe the same scene).";
    }

    void print_status() const {
        std::cout << "\n=== Current Model Status ===\n";
        std::cout << "Observations stored : " << history_.size() << "\n";
        std::cout << "Unique tokens       : " << unique_tokens_.size() << "\n";
        std::cout << "Complexity proxy    : " << std::fixed << std::setprecision(1) << current_complexity() << " bits\n";
        std::cout << "Last progress       : " << progress() << " bits saved\n";
        std::cout << "Residual estimate   : " << residual_ << "\n";
        std::cout << "Suggested next      : " << propose_next_action() << "\n";
        std::cout << "============================\n";
    }

private:
    std::vector<std::string> history_;
    std::vector<std::string> unique_tokens_;
    double residual_ = 100.0;
    double prev_complexity_ = 0.0;

    void update_model() {
        prev_complexity_ = current_complexity();
        unique_tokens_.clear();
        std::string all;
        for (const auto& h : history_) all += " " + h;
        // naive tokenization
        std::string token;
        for (char c : all) {
            if (std::isalnum(c) || c == '_') {
                token += std::tolower(c);
            } else if (!token.empty()) {
                if (std::find(unique_tokens_.begin(), unique_tokens_.end(), token) == unique_tokens_.end())
                    unique_tokens_.push_back(token);
                token.clear();
            }
        }
        // residual shrinks with more data but never to zero (simple model)
        residual_ = 100.0 / (1.0 + std::log1p(static_cast<double>(history_.size())));
    }
};

int main() {
    std::cout << "Sensory Compression Tutor (C++20 demo)\n";
    std::cout << "Enter sensory observations (text). Type 'status' to see model, 'quit' to exit.\n";
    std::cout << "Example: \"I see a red rectangular object 2m ahead, ambient light 300 lux\"\n\n";

    HistoryCompressor compressor;
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit" || line == "exit") break;
        if (line == "status") {
            compressor.print_status();
            continue;
        }
        if (line.empty()) continue;
        compressor.store(line);
        std::cout << "Stored. Progress this step: " << compressor.progress() << " bits (proxy)\n";
        compressor.print_status();
    }
    return 0;
}
