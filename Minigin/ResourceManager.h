#pragma once
#include <string>
#include <memory>
#include "Singleton.h"

//SDL_Mixer struct
//typedef struct Mix_Chunk {
//	int allocated;
//	Uint8* abuf;
//	Uint32 alen;
//	Uint8 volume;  
//} Mix_Chunk;

struct Mix_Chunk;

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
