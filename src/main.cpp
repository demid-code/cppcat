#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <vector>
#include <string_view>

struct Options {
    bool help;
    bool show_ends;
    bool number;
    std::vector<std::string> files;
};

Options parse_args(int argc, char *argv[]) {
    Options opt;

    opt.help = false;
    opt.show_ends = false;
    opt.number = false;

    for (int i = 1; i < argc; i++) {
        std::string_view arg = argv[i];

        if      (arg == "-h" || arg == "--help") opt.help = true;
        else if (arg == "--show-ends")           opt.show_ends = true;
        else if (arg == "--number")              opt.number = true;
        else {
            opt.files.push_back(std::string(arg));
        }
    }

    return opt;
}

void usage(char *program) {
    std::cout << "Usage: " << program << " <filepaths> [flags]\n";
    std::cout << "Flags:\n";
    std::cout << "    -h --help      Prints usage\n";
    std::cout << "    --show-ends    Outputs $ at the end of the lines\n";
    std::cout << "    --number       Number all output lines\n";
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        std::cerr << "cppcat: Expected <filepath>\n"; return 1;
    }

    Options opt = parse_args(argc, argv);
    
    if (opt.help) {
        usage(argv[0]);
        return 0;
    }

    for (const std::string& s : opt.files) {
        std::ifstream file(s);
        if (!file) {
            std::cerr << "cppcat: " << s << ": " << std::strerror(errno) << "\n";
            return 1;
        }

        if (opt.show_ends) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line;
                if (!file.eof()) std::cout << "$\n";
            }
        } else if (opt.number) {
            std::string line;
            int line_num = 1;
            
            while (std::getline(file, line)) {
                std::cout.width(6);
                std::cout << std::right << line_num << "\t" << line;
                if (!file.eof()) std::cout << "\n";
                
                line_num += 1;
            }
        } else {
            std::cout << file.rdbuf();
        }
    }

    return 0;
}