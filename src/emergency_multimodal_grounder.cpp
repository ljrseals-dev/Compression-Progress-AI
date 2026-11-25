// emergency_multimodal_grounder.cpp
// C++20 educational implementation of Prompt 2:
// Emergency Multi-Modal Grounder – offline survival knowledge + sensory history + compression progress.
// Refuses ungrounded claims. Designed for Nomad-style offline emergency AI.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

class EmergencyGrounder {
public:
    bool load_knowledge(const std::string& path) {
        std::ifstream in(path);
        if (!in) return false;
        std::string line;
        while (std::getline(in, line)) {
            if (line.size() > 20) knowledge_.push_back(line);
        }
        std::cout << "Loaded " << knowledge_.size() << " knowledge fragments from " << path << "\n";
        return true;
    }

    void add_observation(const std::string& obs) {
        history_.push_back(obs);
        // update crude situation model
        situation_summary_ = "Current situation compressed from " + std::to_string(history_.size()) + " observations.";
    }

    std::string query(const std::string& q) const {
        // Extremely simple keyword match against knowledge + history.
        // Real system would use embeddings + local LLM; this demonstrates grounding.
        std::string lower_q = to_lower(q);
        std::vector<std::string> hits;
        for (const auto& k : knowledge_) {
            if (to_lower(k).find(lower_q) != std::string::npos || contains_any(lower_q, k)) {
                hits.push_back(k.substr(0, 200) + (k.size() > 200 ? "..." : ""));
                if (hits.size() >= 3) break;
            }
        }
        if (hits.empty()) {
            return "NO GROUNDED ANSWER. The query cannot be compressed against the available offline knowledge base or observation history. Missing data: relevant sensory confirmation or matching survival procedure.";
        }
        std::ostringstream out;
        out << "Grounded response (compression of knowledge + history):\n";
        for (size_t i = 0; i < hits.size(); ++i) {
            out << (i+1) << ". " << hits[i] << "\n";
        }
        out << "\nSituation model: " << situation_summary_ << "\n";
        out << "Recommendation: verify with one additional sensory observation before acting.";
        return out.str();
    }

    void print_status() const {
        std::cout << "History length: " << history_.size() << " | Knowledge fragments: " << knowledge_.size() << "\n";
    }

private:
    std::vector<std::string> knowledge_;
    std::vector<std::string> history_;
    std::string situation_summary_;

    static std::string to_lower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    static bool contains_any(const std::string& q, const std::string& text) {
        // very crude
        return to_lower(text).find(q.substr(0, std::min(q.size(), size_t(8)))) != std::string::npos;
    }
};

int main(int argc, char* argv[]) {
    std::cout << "Emergency Multi-Modal Grounder (C++20 demo)\n";
    EmergencyGrounder eg;
    std::string kb = "books/survival_1957.txt";
    if (argc > 1) kb = argv[1];
    if (!eg.load_knowledge(kb)) {
        std::cerr << "Could not load knowledge base. Place survival_1957.txt in books/ or pass path.\n";
        // continue with empty KB for demo
    }

    std::cout << "Commands: obs <text> | query <text> | status | quit\n";
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit") break;
        if (line == "status") { eg.print_status(); continue; }
        if (line.rfind("obs ", 0) == 0) {
            eg.add_observation(line.substr(4));
            std::cout << "Observation stored.\n";
        } else if (line.rfind("query ", 0) == 0) {
            std::cout << eg.query(line.substr(6)) << "\n";
        } else if (!line.empty()) {
            std::cout << "Unknown command.\n";
        }
    }
    return 0;
}
