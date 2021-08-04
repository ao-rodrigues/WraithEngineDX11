#include <iostream>
#include <Wraith.h>

class Sandbox : public Wraith::Application
{
public:
	Sandbox()
	{
		
	}
	
	~Sandbox()
	{
		
	}
};


void main()
{
	auto sandbox = new Sandbox();

	sandbox->Run();

	delete sandbox;
}
