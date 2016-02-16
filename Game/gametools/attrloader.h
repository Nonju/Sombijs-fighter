#ifndef ATTRLOADER_H
#define ATTRLOADER_H

#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

#include "datacontainers.h"

class AttrLoader {

	public:
		AttrLoader();

		std::vector<CharData> GetCharData(SDL_Renderer* renderer,
		 std::string const& filename);

		std::vector<BlockData> GetBlockData(SDL_Renderer* renderer,
		 std::string const& filename);

		std::vector<ControlData> GetControlData(std::string const& filename);

	private:
		//SplitLine splits line and returns the first word it find on that line
		std::string SplitLine(std::string const& line) const;
		bool ConvertLineToBool(std::string const& line) const;

};


#endif