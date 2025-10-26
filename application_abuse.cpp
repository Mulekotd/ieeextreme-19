#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <climits>
#include <algorithm>

// Stores aggregated data for one user on one day
struct UserDayStats {
    std::set<std::string> user_agents;
    std::set<std::string> ips;
    std::set<std::string> sessions;
    int pdf_count = 0;
    int last_pdf_id = -1;
    int current_crawl_count = 0;
    int max_crawl_count = 0;
};

// Custom log line parser to handle spaces in quotes/brackets
std::vector<std::string> parse_log_line(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool in_brackets = false;
    bool in_quotes = false;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        
        if (c == '[' && !in_quotes) {
            in_brackets = true;
            field.clear();
        } else if (c == ']' && !in_quotes && in_brackets) {
            in_brackets = false;
            fields.push_back(field);
            field.clear();
        } else if (c == '"' && !in_brackets) {
            if (!in_quotes) {
                in_quotes = true;
                field.clear();
            } else {
                in_quotes = false;
                fields.push_back(field);
                field.clear();
            }
        } else if (c == ' ' && !in_brackets && !in_quotes) {
            if (!field.empty()) {
                fields.push_back(field);
                field.clear();
            }
        } else {
            field += c;
        }
    }
    
    if (!field.empty()) {
        fields.push_back(field);
    }
    
    return fields;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string line;

    // 1. Parse Rules
    std::map<std::string, int> rules;
    rules["agent"] = INT_MAX;
    rules["ip"] = INT_MAX;
    rules["pdf"] = INT_MAX;
    rules["session"] = INT_MAX;
    rules["crawl"] = INT_MAX;

    std::getline(std::cin, line);
    std::stringstream ss_rules(line);
    std::string segment;
    while (std::getline(ss_rules, segment, ',')) {
        size_t eq_pos = segment.find('=');
        if (eq_pos != std::string::npos) {
            std::string key = segment.substr(0, eq_pos);
            // Trim leading/trailing spaces from key
            key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));
            key.erase(key.find_last_not_of(" \t\n\r\f\v") + 1);
            int val = std::stoi(segment.substr(eq_pos + 1));
            rules[key] = val;
        }
    }

    // 2. Parse Descriptor
    std::map<std::string, int> field_map;
    std::getline(std::cin, line);
    std::stringstream ss_desc(line);
    int col_index = 0;
    while (std::getline(ss_desc, segment, ',')) {
        segment.erase(0, segment.find_first_not_of(" \t\n\r\f\v"));
        segment.erase(segment.find_last_not_of(" \t\n\r\f\v") + 1);
        field_map[segment] = col_index++;
    }

    // 3. Process Log Entries
    std::map<std::pair<std::string, std::string>, UserDayStats> daily_stats;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        
        std::vector<std::string> parts = parse_log_line(line);
        if (parts.size() < field_map.size()) continue;

        std::string http_status = parts[field_map["HTTP Status"]];
        if (http_status != "200") {
            continue;
        }

        std::string id = parts[field_map["Id"]];
        if (id == "-") {
            continue;
        }

        std::string date_full = parts[field_map["Date"]]; // "07/Feb/2024:12:26:41"
        // Extract just the date part (before the colon)
        size_t colon_pos = date_full.find(':');
        std::string date_day = date_full.substr(0, colon_pos);  // "07/Feb/2024"

        UserDayStats& stats = daily_stats[std::make_pair(id, date_day)];

        stats.user_agents.insert(parts[field_map["User Agent"]]);
        stats.ips.insert(parts[field_map["Client IP"]]);
        std::string session = parts[field_map["Session Cookie"]];
        if (session != "-") {
            stats.sessions.insert(session);
        }

        // Check for PDF
        std::string request = parts[field_map["Request"]];
        if (request.find("GET /document/") == 0 && request.find(".pdf HTTP/1.1") != std::string::npos) {
            stats.pdf_count++;

            // Extract PDF number for crawl detection
            size_t start = 14; // length of "GET /document/"
            size_t end = request.find(".pdf HTTP/1.1");
            if (end != std::string::npos) {
                std::string pdf_id_str = request.substr(start, end - start);
                
                try {
                    int pdf_id = std::stoi(pdf_id_str);
                    if (pdf_id == stats.last_pdf_id + 1) {
                        stats.current_crawl_count++;
                    } else {
                        stats.current_crawl_count = 1;
                    }
                    stats.max_crawl_count = std::max(stats.max_crawl_count, stats.current_crawl_count);
                    stats.last_pdf_id = pdf_id;
                } catch (...) {
                    // Not a numeric PDF id, reset crawl
                    stats.current_crawl_count = 1;
                    stats.last_pdf_id = -1;
                }
            }
        } else {
            // Reset crawl count for non-PDF requests
            stats.current_crawl_count = 0;
            stats.last_pdf_id = -1;
        }
    }

    // 4. Report Violations
    std::map<std::string, std::map<std::string, int>> violations;
    for (auto const& entry : daily_stats) {
        std::string id = entry.first.first;
        const UserDayStats& stats = entry.second;
        
        if (stats.user_agents.size() >= rules["agent"]) {
            violations[id]["agent"] = stats.user_agents.size();
        }
        if (stats.ips.size() >= rules["ip"]) {
            violations[id]["ip"] = stats.ips.size();
        }
        if (stats.pdf_count >= rules["pdf"]) {
            violations[id]["pdf"] = stats.pdf_count;
        }
        if (stats.sessions.size() >= rules["session"]) {
            violations[id]["session"] = stats.sessions.size();
        }
        if (stats.max_crawl_count >= rules["crawl"]) {
            violations[id]["crawl"] = stats.max_crawl_count;
        }
    }

    if (violations.empty()) {
        std::cout << "N/A\n";
    } else {
        for (auto const& id_entry : violations) {
            std::string id = id_entry.first;
            for (auto const& abuse_entry : id_entry.second) {
                std::cout << id << " " << abuse_entry.first << "=" << abuse_entry.second << "\n";
            }
        }
    }

    return 0;
}
