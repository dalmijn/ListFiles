#include <iostream>
#include <fstream>
#include <filesystem>

#include "Log.h"

void ListandWrite(std::string& path, std::string* e, Log* log)
{
	std::ostringstream fp;
	fp << path << "\\" << "filelist.txt";

	std::ofstream ToFile(fp.str());

	fp.str("");
	fp.clear();

	if (e->at(0) != '.')	{ e->insert(0, 1, '.'); }

	int count = 0;

	for (const auto& file : std::filesystem::recursive_directory_iterator(path))
	{		
		std::string ext = file.path().extension().string();
		if (ext == *e)
		{
			fp << "Found: " << file.path().string();
			log->Info(fp.str());
			fp.str("");
			fp.clear();
			ToFile << file.path().string() << "\n";
			count++;
		}
	}
	if (count == 0)
	{
		log->Warn("No items were found!");
	}
	else
	{
		log->Info("Writen all found items to text file.");
	}
	ToFile.close();
}

int main(int argc, const char *argv[])
{
	Log log;
	log.SetLevel(Log::LevelInfo);
	std::string CurDir = std::filesystem::current_path().string();
	std::ostringstream oss;

	std::string command;

	if (argc < 2) { command = "--help"; }
	else { command = argv[1]; }

	if (command == "--help" || command == "-h")
	{
		std::cout << "Usage: "
			<< "listfiles [-h | --help] [-l | --list <ext> <path>]\n\n"
			<< "Commands: \n"
			<< std::setw(4) << "" <<
			"-h or --help\n" << std::setw(8) << "" << 
			"View a bit of help regarding the executable, which is not much...\n\n" << 
			std::setw(4) << "" <<
			"-l or --list\n" << std::setw(8) << "" <<
			"List all files recursively for a certain extension\n" <<
			std::setw(8) << "" << "- Required: <ext>\n" <<
			std::setw(8) << "" << "- Optional: <path>" <<
			std::endl;
	}
	else if (command == "--list" || command == "-l")
	{
		if (argc < 3)
		{
			log.Error("Enter an extension with the '-l' command");
			return 1;
		}

		std::string ext;
		ext = argv[2];

		std::string path;
		if (argc < 4)
		{
			/*
			std::string exe = argv[0];
			std::string::size_type pos = exe.find_last_of("\\/");
			path = exe.substr(0, pos);
			*/
			path = std::filesystem::current_path().string();
		}
		else { path = argv[3]; }

		log.Info("Binary for recursive file listing");
		ListandWrite(path, &ext, &log);
	}
	else
	{
		log.SetLevel(Log::LevelError);
		log.Error("Invalid command, see --help");
		return 1;
	}
}