#include <execution>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace se = std::execution;

int main (int argc, char *argv[]) {
    std::vector<std::vector<std::string>> some_text =  {
        {"In", "the", "realm", "of", "digital", "engineering", "and", "design,", "the", "integration",
        "of", "advanced", "software", "solutions", "has", "revolutionized", "traditional", "workflows.",
        "Companies", "like", "AMC", "Bridge", "play", "a", "pivotal", "role", "in", "providing", "cutting-edge"},
        {"software", "development", "services", "that", "cater", "to", "the", "specific", "needs", "of", "CAD,",
        "CAM,", "CAE,", "BIM,", "PDM,", "and", "PLM", "sectors.", "These", "services", "not", "only", "enhance", "productivity",
        "but", "also", "drive", "innovation", "by", "enabling", "seamless", "collaboration", "and", "efficient"},
        {"data", "management.", "The", "expertise", "in", "developing", "customized", "tools", "and", "applications", 
        "allows", "businesses", "to", "streamline", "operations,", "reduce", "costs,", "and", "accelerate",
        "time-to-market", "for", "their", "products."},

        {"As", "industries", "continue", "to", "evolve,", "the", "demand", "for", "sophisticated", "and", "adaptive",
        "software", "solutions", "grows", "exponentially.", "AMC", "Bridge's", "commitment", 
        "to", "staying", "at", "the", "forefront", "of", "technology", "ensures", "that", "their", "clients", 
        "receive", "the", "most", "up-to-date", "and", "effective", "tools", "available.", "By", "leveraging"}, 
        {"the", "latest", "advancements", "in", "artificial", "intelligence,", "machine", "learning,",
        "and", "cloud", "computing,", "they", "empower", "organizations", "to", "tackle", "complex", "challenges", 
        "and", "achieve", "their", "goals.", "The", "collaboration", "between", "software", "developers", "and", 
        "industry", "experts", "results", "in", "robust", "and", "reliable", "solutions", "that", "meet", "the", "ever-changing"},
        {"demands", "of", "the", "modern", "digital", "landscape."}};
    
    std::unordered_map<std::string, int> initial_value{};

    // map-reduce
    auto result_map = std::transform_reduce(
        se::par,
        some_text.begin(),
        some_text.end(),
        initial_value,
        // reduce
        [](const std::unordered_map<std::string, int>& first_partial_result, const std::unordered_map<std::string, int>& second_partial_result) { 
            std::unordered_map<std::string, int> result;

            for (const auto& [word, cnt] : first_partial_result)
                result[word] += cnt;

            for (const auto& [word, cnt] : second_partial_result)
                result[word] += cnt;

            return result;
        },
        // map/transform
        [](std::vector<std::string>& words_vec) {
            std::unordered_map<std::string, int> curr_count;
            for (const auto& word : words_vec)
                curr_count[word] += 1;

            return curr_count;
        }
    );

    for (const auto& [word, count] : result_map)
        std::cout << word << " : " << count << '\n';

    std::cout << '\n';

    return 0;
}
