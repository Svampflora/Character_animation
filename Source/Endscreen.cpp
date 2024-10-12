#include "Endscreen.h"
#include "Startscreen.h"
#include <fstream>
#include <iostream>


std::unique_ptr<State> End_screen::Update()
{

	if (IsKeyReleased(KEY_ENTER))
	{

	}
	return nullptr;
}

void End_screen::Render() const noexcept
{

}

