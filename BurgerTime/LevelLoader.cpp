#include "LevelLoader.h"
#include <rapidjson.h>
#include <fstream>
#include <document.h>

#include "PeterPepper.h"
#include "Plate.h"
#include "Platform.h"
#include "TopBun.h"
#include "Cheese.h"
#include "istreamwrapper.h"
#include "Scene.h"
#include "Lettuce.h"
#include "Patty.h"
#include "SceneManager.h"
#include "Tomato.h"
#include "Ladder.h"
#include "BottomBun.h"


//CREDITS TO https://www.geeksforgeeks.org/how-to-read-and-parse-json-file-with-rapidjson/  + CHATGPT


void LevelLoader::LoadLevel(std::string fileLoc)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("JSONTEST");
	if (std::ifstream is{ fileLoc })
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		std::vector<Vector2> bounds;
		using rapidjson::Value;
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const Value& pos = *itr;
			std::string type = pos["type"].GetString();
			const Value& locs = pos["positions"].GetArray();
			for (rapidjson::SizeType i = 0; i < locs.Size(); i++)
			{
				const Value& x = locs[i][0];
				const Value& y = locs[i][1];

				if (type == "platform")
				{
					dae::Platform{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "ladder")
				{
					dae::Ladder{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bun")
				{
					dae::TopBun{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "lettuce")
				{
					dae::Lettuce{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "patty")
				{
					dae::Patty{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "cheese")
				{
					dae::Cheese{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "tomato")
				{
					dae::Tomato{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bottombun")
				{
					dae::BottomBun{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "plate")
				{
					dae::Plate{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "peter")
				{
					dae::PeterPepper{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bounds")
				{
					bounds.push_back({ x.GetFloat(),y.GetFloat() });
				}
			}
		}
		Vector2 point1 = bounds[0];
		Vector2 point2 = bounds[1];

		float minX = std::min(point1.x, point2.x);
		float minY = std::min(point1.y, point2.y);
		float maxX = std::max(point1.x, point2.x);
		float maxY = std::max(point1.y, point2.y);

		Rect rect;
		rect.x = minX;
		rect.y = minY;
		rect.width = maxX - minX;
		rect.height = maxY - minY;
		scene.SetBounds(rect);
	}
}
