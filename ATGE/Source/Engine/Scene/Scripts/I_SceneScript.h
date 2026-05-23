#pragma once

namespace ATGE
{
	class I_SceneScript
	{
	public:
		I_SceneScript() = default;
		I_SceneScript(const I_SceneScript& other) = default;
		I_SceneScript& operator=(const I_SceneScript& other) = default;
		I_SceneScript(I_SceneScript&& other) = default;
		I_SceneScript& operator=(I_SceneScript&& other) = default;
		virtual ~I_SceneScript() = default;

		virtual void StartScene() = 0;
		virtual void EndScene() = 0;
	};
}

