#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <map>

class Subject {
public:
    std::string replace_word(const std::map<std::string, std::string>& args);
    std::string find_phrase(const std::map<std::string, std::string>& args);
    std::string capitalize_words(const std::map<std::string, std::string>& args);
    std::string capitalize_sentences(const std::map<std::string, std::string>& args);
    std::string number_sentences(const std::map<std::string, std::string>& args);

    void set_text(const std::string& text);
    const std::string& get_text() const;

private:
    std::string text;
};

#endif
