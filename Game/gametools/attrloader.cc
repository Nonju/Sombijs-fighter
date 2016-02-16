#include <iostream>

#include <fstream>
#include <string>
#include <cctype>

#include "attrloader.h"
#include "datacontainers.h"
#include "createtexture.h"

using namespace std;

AttrLoader::AttrLoader() { }

string AttrLoader::SplitLine(string const& line) const {
	long unsigned int pos{line.find(" ")};
	if (pos != string::npos) {
		return line.substr(0, pos);
	}
	else { return line; }
}

bool AttrLoader::ConvertLineToBool(string const& line) const {
	string newLine{};
	for (char c : line) {
		newLine += tolower(c);
	}
	return newLine == "true";
}

vector<CharData> AttrLoader::GetCharData(SDL_Renderer* renderer,
 string const& filename) {

	vector<CharData> container;
	ifstream ifs{filename};
	vector<string> data;

	if (!ifs) {
		cerr << "File (" << filename << ") could not be opened!" << endl;
	}
	else {
		string line{};
		while (getline(ifs, line)) {
			if (!line.empty() && line.find("//") != 0) {
				//only use first word of line (clean from trash)
				string tmpString{SplitLine(line)};
				//if reached end --> add to container + clean vector
				if (tmpString == "END") {
					CreateTexture ct{};
					SDL_Texture* tmpTexture = ct.GetTexture(renderer, data.at(1));				
					/*charName (string), texture (SDL_Texture*),
					 width (int), height (int), speedX (int), speedY (int)*/
					CharData tmp{data.at(0), tmpTexture,
					 stoi(data.at(2)), stoi(data.at(3)),
					 stoi(data.at(4)), stoi(data.at(5))};

					container.push_back(tmp);
					data.clear(); //resets tmp-vector-data
				}
				else {
					data.push_back(tmpString);
				}
			}
		}

	}
	ifs.close();
	return container;
}


vector<BlockData> AttrLoader::GetBlockData(SDL_Renderer* renderer,
 string const& filename) {
	
	vector<BlockData> container;
	ifstream ifs{filename};
	vector<string> data;

	if (!ifs) {
		cerr << "File (" << filename << ") could not be opened!" << endl;
	}
	else {
		string line{};
		while (getline(ifs, line)) {
			if (!line.empty() && line.find("//") != 0) {
				//only use first word of line (clean from trash)
				string tmpString{SplitLine(line)};
				//if reached end --> add to container + clean vector
				if (tmpString == "END") {
					CreateTexture ct{};
					//ct.GetTexture(SDL_Renderer*, const char*)
					SDL_Texture* tmpTexture = ct.GetTexture(renderer, data.at(2));
					bool isIntersectable{ConvertLineToBool(data.at(6))};
					
					/*blockName (string), blockType (char), texture (SDL_Texture*),
					 width (int), height (int), hitPoints (int),
					 intersectable (bool), charName (string)*/
					BlockData tmp{data.at(0), data.at(1).at(0), tmpTexture,
					 stoi(data.at(3)), stoi(data.at(4)),
					  stoi(data.at(5)), isIntersectable, data.at(7)};

					container.push_back(tmp);
					data.clear(); //resets tmp-vector data
				}
				else {
					data.push_back(tmpString);
				}
			}
		}

	}
	ifs.close();
	return container;
}

vector<ControlData> AttrLoader::GetControlData(string const& filename) {
	vector<ControlData> container;
	ifstream ifs{filename};
	vector<string> data;

	if (!ifs) {
		cerr << "File (" << filename << ") could not be opened!" << endl;
	}
	else {
		string line{};
		while (getline(ifs, line)) {
			if (!line.empty() && line.find("//") != 0) {
				//only use first word of line (clean from trash)
				string tmpString{SplitLine(line)};
				//if reached end --> add to container + clean vector
				if (tmpString == "END") {
					

					/*charName (string), Up (string), Down (string),
					 Left (string), Right (string), Shoot (string),
					 Special (string)*/

					ControlData tmp{data.at(0), data.at(1),
					 data.at(2), data.at(3), data.at(4), 
					 data.at(5), data.at(6)};

					container.push_back(tmp);
					data.clear(); //resets tmp-vector data
				}
				else {
					data.push_back(tmpString);
				}
			}

		}
	}
	ifs.close();
	return container;

}