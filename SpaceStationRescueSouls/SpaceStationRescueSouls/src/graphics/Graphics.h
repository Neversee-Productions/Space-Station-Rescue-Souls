#ifndef _GRAPHICS_H
#define _GRAPHICS_H

namespace app::gra
{
	static std::shared_ptr<sf::Texture> loadTexture(std::string const & filePath)
	{
		auto texture = sf::Texture();
		if (texture.loadFromFile(filePath))
		{
			texture.setSmooth(true);
			return std::make_shared<decltype(texture)>(std::move(texture));
		}
		return nullptr;
	}
}

#endif // !_GRAPHICS_H
