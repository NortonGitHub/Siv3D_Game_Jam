
# include <Siv3D.hpp>
#include "MainLoop.h"

void Main() {
	MainLoop mainLoop;
	while (System::Update()) {
		mainLoop.Main();
	}
}
