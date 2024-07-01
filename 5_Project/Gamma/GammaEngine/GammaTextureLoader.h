#include <string>

namespace GammaEngine
{
	class TextureLoader : public spine::TextureLoader
	{
	public:
		TextureLoader() { }
		virtual ~TextureLoader() { }

		// Called when the atlas loads the texture of a page.
		virtual void load(spine::AtlasPage& page, const spine::String& path)
		{

			std::wstring* bitmap = new std::wstring(path.buffer(), path.buffer() + strlen(path.buffer()));
			GraphicSystem::LoadBitmapImage(*bitmap);
			page.setRendererObject(bitmap);
			vector2 size = GraphicSystem::GetBitmapSize(*bitmap);
			page.width = (int)size.x;
			page.height = (int)size.y;
		}

		// Called when the atlas is disposed and itself disposes its atlas pages.
		virtual void unload(void* texture)
		{
			// the texture parameter is the texture we stored in the page via page->setRendererObject()
			//engine_disposeTexture(texture);
		}
	};
}
