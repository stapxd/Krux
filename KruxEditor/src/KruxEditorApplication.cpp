#include "Krux/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Krux {

	class KruxEditorApplication : public Application {
	public:
		KruxEditorApplication(ApplicationSpecification specification)
			: Application(specification)
		{
			PushLayer(new EditorLayer());
		}

		~KruxEditorApplication() {

		}
	};

	Application* CreateApplication() {
		return new KruxEditorApplication({ "Krux Editor", 1280, 780 });
	}

}