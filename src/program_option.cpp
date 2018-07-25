#include<iostream>
#include<sstream>
#include"nieel/algorithm.hpp"
#include"nieel/program_option.h"

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
    
    po::parsed_options Option::make_parser() {
        return  po::command_line_parser(argc_, argv_)
               .options(desc_)
               .positional(make_command_option())
               .allow_unregistered()
               .run();
    }
    
    po::parsed_options Option::make_parser(std::vector<std::string>& options) {
        return  po::command_line_parser(options)
               .options(desc_)
               .positional(make_command_option())
               .allow_unregistered()
               .run();
    }
    
    std::vector<std::string> Option::get_argument_list(const std::vector<po::option>& raw) {
        std::vector<std::string> args;
    
        for(const boost::program_options::option& option : raw)
        {
            if(option.unregistered) continue; // Skipping unknown options
    
            if(option.value.empty())
                args.push_back("--" + option.string_key);
            else
            {
                // this loses order of positional options
                for(const std::string& value : option.value)
                {
                    if(option.string_key == value) continue;
                    if(option.string_key != "command") continue;
                    //args.push_back(option.string_key);
                    args.push_back(value);
                }
            }
        }
    
        return args;
    }
    
    std::vector<std::string> Option::get_subarg() {
       if(!vm_.count("subargs")) return std::vector<std::string>();
       return vm_["subargs"].as<std::vector<std::string>>();
    }
    
    SubOptions& SubOptions::operator()(option::type type, std::string name
                                      ,std::function<void()> func, std::string descripte) {
        if(type == option::type::option)  {
            options_.emplace_back(std::move(std::make_tuple(name, func, descripte)));
        }
        if(type == option::type::command) {
            commands_.emplace_back(std::move(std::make_tuple(name, func, descripte)));
        }  
        return *this;
    }
    
    SubOptions& SubOptions::operator()(option::type type, std::function<void()> func
                                      ,std::string descripte) {
        if(type == option::type::default_option) {
            default_option_ = std::move(func);
        }
        else if(type == option::type::default_command) {
            default_command_ = std::move(func);
        }
        return *this;
    }
    
    SubOptions& SubOptions::operator()(option::type type, std::string name
                                      ,std::function<void(std::string&)> func, std::string descripte) {
        if(type == option::type::command) {
            commands_.emplace_back(std::move(std::make_tuple(name, [this, &func](){
              auto cmd = vm_["command"].as<std::string>();
              func(cmd);
            }, descripte)));
        }  
        return *this;
    }
    SubOptions& SubOptions::operator()(option::type type, std::function<void(std::string&)> func
                                      ,std::string descripte) {
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
            for(auto& [name, command, _] : commands_) {
                if(cmd == name) {
                    command(); return ;
                }
            }
            default_command_(); 
        }
        for(auto& [name, option, _] : options_) {
            if(vm_.count(name)) {
                option();  return;
            }
        }
        default_option_(); 
    }
    
    std::string SubOptions::command_description(std::string description) {
        std::stringstream output("");
        if(commands_.empty()) return output.str();
        output << description << ": \n";
        for(auto& [name, _, des] : commands_) {
            output << "  " + name + "\t\t\t" + des << "\n";
        }
        return output.str();
    }
}