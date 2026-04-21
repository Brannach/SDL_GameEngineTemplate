#pragma once

#include <string>

using namespace std;

class Layer
{
public:

	virtual void Render() = 0;
	virtual void Update() = 0;
	inline string GetName() { return mName; }
	virtual ~Layer() = default;
	
protected:
	string mName;

private:
	
};

