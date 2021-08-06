#pragma once
//#include "Audio/AudioSystem.h"
#include "Math/Vector2.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Framework/EventSystem.h"
#include "Resource/ResourceSystem.h"
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "Core/FileSystem.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <variant>

namespace nc
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw();

		template<typename T>
		T* Get();


	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}