#include <iostream>
#include <fstream>
#include "Engine.h"
#include "Wrapper.h"
#include "Subject.h"

void read_file(const std::string& filename, std::string& content) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

void write_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to write to file: " + filename);
    }
    file << content;
}

int main() {
    try {
        std::string filename = "Test.txt";
        std::string text;

        read_file(filename, text);

        Subject subj;
        subj.set_text(text);

        Engine engine;

        Wrapper replaceWrapper(&subj, &Subject::replace_word, { {"word_to_replace", ""}, {"replacement", ""} });
        Wrapper findWrapper(&subj, &Subject::find_phrase, { {"phrase", ""} });
        Wrapper capitalizeWordsWrapper(&subj, &Subject::capitalize_words, {});
        Wrapper capitalizeSentencesWrapper(&subj, &Subject::capitalize_sentences, {});
        Wrapper numberSentencesWrapper(&subj, &Subject::number_sentences, {});

        engine.register_command(&replaceWrapper, "replace");
        engine.register_command(&findWrapper, "find");
        engine.register_command(&capitalizeWordsWrapper, "capitalize_words");
        engine.register_command(&capitalizeSentencesWrapper, "capitalize_sentences");
        engine.register_command(&numberSentencesWrapper, "number_sentences");

        std::vector<std::string> commands = {"capitalize_sentences", "capitalize_words", "number_sentences", "find", "replace"};
        std::vector<std::map<std::string, std::string>> args_list = {
            {},
            {},
            {},
            { {"phrase", "A"} },
            { {"word_to_replace", "This"}, {"replacement", "that"} }
        };

        std::vector<std::string> results = engine.execute(commands, args_list);

        //Вывод промежуточных результатов
        for (const std::string& result : results) {
            std::cout << result +"\n" << std::endl;
        }

        write_file("filename", subj.get_text());
        std::cout << "Updated text saved to file.";

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
