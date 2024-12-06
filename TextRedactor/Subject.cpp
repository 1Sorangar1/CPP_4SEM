#include "Subject.h"
#include <sstream>
#include <cctype>

void Subject::set_text(const std::string& text) {
    this->text = text;
}

const std::string& Subject::get_text() const {
    return text;
}

std::string Subject::replace_word(const std::map<std::string, std::string>& args) {
    std::string word_to_replace = args.at("word_to_replace");
    std::string replacement = args.at("replacement");
    size_t pos = 0;

    while ((pos = text.find(word_to_replace, pos)) != std::string::npos) {
        text.replace(pos, word_to_replace.length(), replacement);
        pos += replacement.length();
    }
    return text;
}

std::string Subject::find_phrase(const std::map<std::string, std::string>& args) {
    std::string phrase = args.at("phrase");
    return text.find(phrase) != std::string::npos ? "Phrase found!" : "Phrase not found!";
}

std::string Subject::capitalize_words(const std::map<std::string, std::string>& args) {
    std::stringstream ss(text);
    std::string word, result;

    while (ss >> word) {
        word[0] = toupper(word[0]);
        result += word + " ";
    }
    text = result;
    return text;
}

std::string Subject::capitalize_sentences(const std::map<std::string, std::string>& args) {
    bool capitalize = true;
    for (auto& character : text) {
        if (capitalize && std::isalpha(character)) {
            character = toupper(character);
            capitalize = false;
        }
        if (character == '.' || character == '!' || character == '?') {
            capitalize = true;
        }
    }
    return text;
}

std::string Subject::number_sentences(const std::map<std::string, std::string>& args) {
    std::stringstream ss(text);
    std::string result, sentence;
    int counter = 1;

    auto is_end_of_sentence = [](char ch) {
        return ch == '.' || ch == '!' || ch == '?' || ch == '\n';
        };

    size_t i = 0;
    while (i < text.length()) {
        std::string current_sentence;

        while (i < text.length() && !is_end_of_sentence(text[i])) {
            current_sentence += text[i++];
        }

        while (i < text.length() && is_end_of_sentence(text[i])) {
            current_sentence += text[i++];
        }

        if (!current_sentence.empty()) {
            result += std::to_string(counter++) + ". " + current_sentence + "\n";
        }
    }

    text = result;
    return text;
}
