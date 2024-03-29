#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#define TAB "    "

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Not enough arg" << std::endl;
        exit(1);
    }

    std::string class_name = argv[1];
    std::string header_file_name(class_name + ".gen.hpp");
    std::string cpp_file_name(class_name + ".gen.cpp");
    std::string runner_file_name("Run_" + class_name + ".cpp");

    std::ofstream header_file(header_file_name);
    std::ofstream cpp_file(cpp_file_name);
    std::ofstream runner_file(runner_file_name);

    header_file
        << "/********************************************\n"
        << " ** This file is generated by AppGenerator **\n"
        << " ********************************************/\n"
        << "\n"
        << "#pragma once\n"
        << "\n"
        << "#include \"AppInterface.hpp\"\n"
        << "\n"
        << "#include <cstdint>\n"
        << "#include <memory>\n"
        << "\n"
        << "class " << class_name << " : public tll::AppInterface\n"
        << "{\n"
        << "public:\n"
        << TAB << class_name << "();\n"
        << TAB << "~" << class_name << "();\n"
        << "\n"
        << TAB << "void init() override;\n"
        << TAB << "void run() override;\n"
        << TAB << "void terminate() override;\n"
        << "\n"
        << TAB << "void onTouched(tll::TouchInfo ti) override;\n"
        << TAB << "void onMoved(tll::TouchInfo ti) override;\n"
        << TAB << "void onReleased(tll::TouchInfo ti) override;\n"
        << "};\n"
        << "\n"
        << "/* Required to use in loading application file */\n"
        << "extern \"C\"\n"
        << "{\n"
        << TAB << "std::unique_ptr<tll::AppInterface> create()\n"
        << TAB << "{\n"
        << TAB << TAB << "return std::unique_ptr<tll::AppInterface>(new " << class_name << ");\n"
        << TAB << "}\n"
        << "}\n";

    cpp_file
        << "/********************************************\n"
        << " ** This file is generated by AppGenerator **\n"
        << " ********************************************/\n"
        << "\n"
        << "#include \"" << header_file_name << "\"\n"
        << "#include \"TLL.h\"\n"
        << "\n"
        << "#include <iostream>\n"
        << "\n"
        << class_name << "::" << class_name << "()\n"
        << "{\n"
        << TAB << "std::cout << \"Create " << class_name << " instance.\" << std::endl;\n"
        << "}\n"
        << "\n"
        << class_name << "::~" << class_name << "()\n"
        << "{\n"
        << TAB << "std::cout << \"Delete " << class_name << " instance.\" << std::endl;\n"
        << "}\n"
        << "\n"
        << "void " << class_name << "::init()\n"
        << "{\n"
        << "\n"
        << "}\n"
        << "\n"
        << "void " << class_name << "::run()\n"
        << "{\n"
        << "\n"
        << "}\n"
        << "\n"
        << "void " << class_name << "::terminate()\n"
        << "{\n"
        << "\n"
        << "}\n"
        << "\n"
        << "void " << class_name << "::onTouched(tll::TouchInfo ti)\n"
        << "{\n"
        << "\n"
        << "}\n"
        << "\n"
        << "void " << class_name << "::onMoved(tll::TouchInfo ti)\n"
        << "{\n"
        << "\n"
        << "}\n"
        << "\n"
        << "void " << class_name << "::onReleased(tll::TouchInfo ti)\n"
        << "{\n"
        << "\n"
        << "}\n";

    runner_file
        << "#include \"AppRunner.hpp\"\n"
        << "\n"
        << "int main()\n"
        << "{\n"
        << TAB << "AppRunner runner;\n"
        << TAB << "runner.runApp(\"" << class_name << "\");\n"
        << "}\n";

    header_file.close();
    cpp_file.close();
    runner_file.close();

    if (std::filesystem::exists(std::filesystem::status("../app/CMakeLists.txt")))
    {
        std::ofstream cmake_file("../app/CMakeLists.txt", std::ios::app);
        cmake_file << "add_library(" << class_name << " SHARED ${CMAKE_SOURCE_DIR}/app/" << cpp_file_name << ")\n";
        cmake_file.close();

        std::ofstream runner_cmake_file("../app/AppRunner/CMakeLists.txt", std::ios::app);
        runner_cmake_file << "add_executable(Run_" << class_name << " " << runner_file_name << ")\n";
        runner_cmake_file.close();

        std::cout << "Update \"../app/CMakeLists.txt\"" << std::endl;

        std::filesystem::rename(header_file_name, std::string("../app/") + header_file_name);
        std::filesystem::rename(cpp_file_name, std::string("../app/") + cpp_file_name);
        std::filesystem::rename(runner_file_name, std::string("../app/AppRunner/") + runner_file_name);
    }

    std::cout << "Create \"" << header_file_name << "\", \"" << cpp_file_name << "\"" << std::endl;
}
