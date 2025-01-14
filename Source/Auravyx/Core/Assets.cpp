#include "Auravyx/Core/Assets.h"
#include "Logger/Log.h"
#include <Auravyx/Graphics/GFX.h>

Assets::Assets(Assets* a)
{
	assets = a;
}

Assets* Assets::assets;

void Assets::addTexture(const std::string& name, const Texture& texture)
{
	textures.emplace(name, std::shared_ptr<Texture>(new Texture(texture)));
}

void Assets::addModel(const std::string& name, const Model& model)
{
	std::shared_ptr<Model> mod(new Model(model));
	mod->name = name;
	models.emplace(name, mod);
}

void Assets::addFont(const std::string& name, const Font& font)
{
	fonts.emplace(name, std::shared_ptr<Font>(new Font(font)));
}

void Assets::addAudio(const std::string& name, const WAVE& a)
{
	audio.emplace(name, std::shared_ptr<WAVE>(new WAVE(a)));
}

std::shared_ptr<Texture> Assets::getTexture(const std::string& name)
{
	try
	{
		return textures.at(name);
	}
	catch (std::out_of_range e)
	{
		Log::error("[Asset Fetch] Texture '" + name + "' was not found!");
	}
	return NULL;
}

std::shared_ptr<Font> Assets::getFont(const std::string& name)
{
	try
	{
		return fonts.at(name);
	}
	catch (std::out_of_range e)
	{
		Log::error("[Asset Fetch] Font '" + name + "' was not found!");
	}
	return NULL;
}

std::shared_ptr<WAVE> Assets::getAudio(const std::string& name)
{
	try
	{
		return audio.at(name);
	}
	catch (std::out_of_range e)
	{
		Log::error("[Asset Fetch] Audio '" + name + "' was not found!");
	}
	return NULL;
}
void Assets::deleteAudio()
{
	for (auto a : audio)
	{
		a.second->destroy();
	}
}

void Assets::deleteTextures()
{
	for (auto t : textures)
	{
		t.second->destroy();
	}
	GLuint del = GFX::getOverlay()->terrainMaterials;
	glDeleteTextures(1, &del);
}

void Assets::deleteFonts()
{
	for (auto f : fonts)
	{
		f.second->texture.destroy();
	}
}

void Assets::deleteModels()
{
	for (auto m : models)
	{
		m.second->destroy();
	}
}

Assets* Assets::getAssets()
{
	return assets;
}

std::shared_ptr<Model> Assets::getModel(const std::string& name)
{
	try
	{
		return models.at(name);
	}
	catch (std::out_of_range e)
	{
		Log::error("[Asset Fetch] Model '" + name + "' was not found!");
	}
	return NULL;
}
