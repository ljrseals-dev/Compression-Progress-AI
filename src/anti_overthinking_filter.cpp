// anti_overthinking_filter.cpp
// C++20 educational implementation of Prompt 4:
// Anti-Overthinking / Anti-Magic Filter – force minimal sufficient compressor, reject ungrounded length.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class AntiOverthinkingFilter {
public:
    std::string process(const std::string& query, const std::string& candidate_answer) {
        // Measure candidate length vs information content proxy
        size_t answer_len = candidate_answer.size();
        size_t unique = unique_token_count(candidate_answer);
        double density = unique > 0 ? static_cast<double>(unique) / answer_len : 0.0;

        std::ostringstream out;
        out << "=== Filter Report ===\n";
        out << "Candidate length     : " << answer_len << " chars\n";
        out << "Unique tokens        : " << unique << "\n";
        out << "Information density  : " << density << "\n";

        // Reject pure verbosity or magic claims
        if (contains_magic(candidate_answer)) {
            out << "REJECTED: contains ungrounded / magical language. Provide only verifiable, low-bit explanation.\n";
            return out.str();
        }
        if (answer_len > 400 && density < 0.15) {
            out << "REJECTED: overthinking detected – long monologue with low information density.\n";
            out << "Minimal sufficient answer would be far shorter.\n";
            return out.str();
        }

        // Accept and optionally compress further
        out << "ACCEPTED (sufficiently compressible).\n";
        out << "Suggested minimal form: " << compress_to_key_points(candidate_answer) << "\n";
        return out.str();
    }

private:
    static size_t unique_token_count(const std::string& s) {
        std::istringstream iss(s);
        std::vector<std::string> tokens;
        std::string t;
        while (iss >> t) {
            for (char& c : t) c = std::tolower(c);
            if (std::find(tokens.begin(), tokens.end(), t) == tokens.end())
                tokens.push_back(t);
        }
        return tokens.size();
    }

    static bool contains_magic(const std::string& s) {
        std::string lower = s;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        const char* bad[] = {"realm magic", "magic", "spell", "100x worse", "overthrown by", "eating the beings"};
        for (auto b : bad) if (lower.find(b) != std::string::npos) return true;
        return false;
    }

    static std::string compress_to_key_points(const std::string& s) {
        // Extremely crude: take first sentence or first 120 chars
        auto pos = s.find('.');
        if (pos != std::string::npos && pos < 150) return s.substr(0, pos + 1);
        return s.substr(0, std::min(s.size(), size_t(120))) + "...";
    }
};

int main() {
    std::cout << "Anti-Overthinking / Anti-Magic Filter (C++20 demo)\n";
    std::cout << "Enter a candidate answer (or 'demo' for built-in examples). Type 'quit' to exit.\n\n";

    AntiOverthinkingFilter filter;
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit") break;
        if (line == "demo") {
            std::cout << filter.process("how to purify water",
                "Boil water for one minute at sea level. This is the most reliable low-tech method.") << "\n";
            std::cout << filter.process("emergency",
                "In the realm of magic the beings that are 100x worse have overthrown many with realm magic including eating. You must learn the stratand...") << "\n";
            continue;
        }
        if (!line.empty()) {
            std::cout << filter.process("user query", line) << "\n";
        }
    }
    return 0;
}
