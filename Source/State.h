#pragma once

#include <memory>
#include <string>
#include "Utilities.h"


class State
{

public:
	virtual ~State() = default;
	virtual std::unique_ptr<State> Update() = 0;
	virtual void Render()  const noexcept = 0;
};






