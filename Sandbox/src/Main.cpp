#include <Wraith.h>

class Sandbox : public Wraith::Application
{
public:
	Sandbox(const std::string& name, int windowWidth, int windowHeight)
		: Application(name, windowWidth, windowHeight)
	{}
	
	~Sandbox() = default;
};

Wraith::Application Wraith::CreateApplication()
{
	return Sandbox("Sandbox Test", 1280, 720);
}
