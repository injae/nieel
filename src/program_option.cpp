#include"program_option.h"
#include<iostream>

namespace nieel 
{
    po::options_description make_command_desc() {
        po::options_description desc("Command Options");
        desc.add_options()
            ("command"       , po::value<std::string>()             , ""    )
            ("subargs"       , po::value<std::vector<std::string>>(), ""    )
            ;
       return desc; 
    }
    
    po::positional_options_description make_command_option() {
        po::positional_options_description option;
        option.add("command" , 1);
        option.add("subargs" ,-1);
        return option; 
    }
    
    void Option::regist() {
        po::store(make_parser(), vm_);
        po::notify(vm_);
    }
    
    void Option::regist(std::vector<std::string>& options) {
        po::store(make_parser(options), vm_);
        po::notify(vm_);
    }
    
    parser_type Option::make_parser() {
        return  po::command_line_parser(argc_, argv_)
               .options(desc_)
               .positional(make_command_option())
               .allow_unregistered()
               .run();
    }
    
    parser_type Option::make_parser(std::vector<std::string>& options) {
        return  po::command_line_parser(options)
               .options(desc_)
               .positional(make_command_option())
               .allow_unregistered()
               .run();
    }
    
    std::vector<std::string> Option::get_subarg() {
       if(!vm_.count("subargs")) return std::vector<std::string>();
       return vm_["subargs"].as<std::vector<std::string>>();
    }
    
    SubOptions& SubOptions::operator()(option::type type, std::string name, std::function<void()> func) {
        if(type == option::type::option)  {
            options_.emplace_back(std::move(std::make_pair(name, func)));
        }
        if(type == option::type::command) {
            commands_.emplace_back(std::move(std::make_pair(name, func)));
        }  
        return *this;
    }
    
    SubOptions& SubOptions::operator()(option::type type, std::function<void()> func) {
        if(type == option::type::default_option) {
            default_option_ = std::move(func);
        }
        else if(type == option::type::default_command) {
            default_command_ = std::move(func);
        }
        return *this;
    }
    
    SubOptions& SubOptions::operator()(option::type type, std::string name, std::function<void(std::string&)> func) {
        if(type == option::type::command) {
            commands_.emplace_back(std::move(std::make_pair(name, [this, &func](){
              auto cmd = vm_["command"].as<std::string>();
              func(cmd);
            })));
        }  
        return *this;
    }
    SubOptions& SubOptions::operator()(option::type type, std::function<void(std::string&)> func) {
        if(type == option::type::default_command) {
            default_command_ = std::move([this, &func](){
              auto cmd = vm_["command"].as<std::string>();
              func(cmd);
            });
        }
        return *this;
    }
    
    
    void SubOptions::run() {
        if(vm_.count("command")) { auto cmd = vm_["command"].as<std::string>();
            for(auto& command : commands_) {
                if(cmd == command.first) {
                    command.second();
                    goto option;
                }
            }
            default_command_(); 
        }
        option:
        for(auto& option : options_) {
            if(vm_.count(option.first)) {
                option.second(); 
                return;
            }
        }
        default_option_(); 
    }
}