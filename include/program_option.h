#ifndef __NIEEL_PROGRAM_OPTION_H__
#define __NIEEL_PROGRAM_OPTION_H__

#include<boost/program_options/options_description.hpp>
#include<boost/program_options/variables_map.hpp>
#include<boost/program_options/parsers.hpp>
#include<utility>
#include<vector>
#include<functional>
#include<string>

namespace po = boost::program_options;

namespace nieel 
{
    namespace option
    {
        enum class type
        {
              option
            , command
            , default_option
            , default_command
        };
    }
    #define opbind(func) [this](){ func(); }
    #define aopbind(func)[this](){ func; }
    #define uopbind(func) [this](auto& cmd) { func(cmd); }
    
    class SubOptions
    {
    using list_type = std::pair<std::string, std::function<void()>>;
    public:
        SubOptions(po::variables_map& vm) : vm_(vm), default_option_([](){}), default_command_([](){}) {}
        SubOptions& operator()(option::type type, std::function<void(std::string&)> func);
        SubOptions& operator()(option::type type, std::function<void()> func); 
        SubOptions& operator()(option::type type, std::string name, std::function<void()> func);
        SubOptions& operator()(option::type type, std::string name, std::function<void(std::string&)> func);
        void run();
    private:
        po::variables_map vm_;
        std::vector<list_type> options_;
        std::vector<list_type> commands_;
        std::function<void()> default_option_; 
        std::function<void()> default_command_; 
    };
    
    typedef po::basic_parsed_options<char> parser_type;
    
    class Option
    {
    public:
        virtual void                    run() = 0;
                void                    regist();
                void                    regist(std::vector<std::string>& options);
                parser_type             make_parser();
                parser_type             make_parser(std::vector<std::string>& options); 
                po::options_description description() { return desc_; } 
                std::vector<std::string> get_subarg();
                template<typename OPTION>
                OPTION make_sub_command() {
                    auto opts = po::collect_unrecognized(make_parser().options, po::include_positional);
                    opts.erase(opts.begin());
                    auto option = OPTION(argc_,argv_);
                    option.regist(opts); 
                    return option;
                }
            
        Option(const std::string descripte, int argc, char* argv[]) 
            : desc_(descripte), visible_option_(desc_), argc_(argc), argv_(argv) {}
        virtual ~Option() {}
        
    protected:
        po::variables_map vm_;
        po::options_description desc_;
        po::options_description visible_option_;
        int    argc_;
        char** argv_;
    };
    
    po::options_description            make_command_desc();
    po::positional_options_description make_command_option();
    
}

#endif