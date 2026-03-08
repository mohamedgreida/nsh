#include "executer.hpp"
#include "builtins.hpp"
#include "unistd.h"
#include "sys/wait.h"
#include <iostream>
#include <vector>
#include <fcntl.h>

void Executer::execute( std::vector<std::string> &tokens)
{
    bool backchar = false, flag= false;
    int index;
    if (tokens.back() == "&") {
        backchar = true;
        tokens.pop_back(); 
    }
    
    if (Builtins::handle(tokens))
        return;

    std::vector<const char *> argv;

    for(int i=0; i<tokens.size(); i++){
        if(tokens[i]== ">"){
            index = i;
            flag = true;
        }
    }

    for (const std::string &token : tokens){
            if(token == ">")
                break;
            argv.push_back(token.c_str());
    }
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0)
    {
        if(flag){
            int fd = open(tokens[index+1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("dup2");
            }
            close(fd);
        }
        int status = execvp(argv[0], const_cast<char *const *>(argv.data()));

        if (status != 0)
        {
            std::string msg = "failed to execute command";

            if (errno == ENOENT)
                msg = "command not found";

            std::cerr << tokens[0] << ": " << msg << std::endl;
        }
    }
    else if (pid == -1)
        std::cerr << tokens[0] << ": failed to execute command" << std::endl;
    else{
        if(backchar){
            std::cout << pid << '\n';
        }else{
            waitpid(pid, nullptr, 0);
        }
    }
}
