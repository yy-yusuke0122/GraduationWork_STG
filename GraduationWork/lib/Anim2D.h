#pragma once

class Anim2D {
public:
	Anim2D(unsigned int _start, unsigned int _end, std::string _name, float _speed, bool _isLoop) :
		start(_start), end(_end), name(_name), speed(_speed), isLoop(_isLoop), destroyFlag(false) {}
	~Anim2D() {}

	void Destroy() { destroyFlag = true; }

	bool IsDestroy() { return destroyFlag; }

	unsigned int start, end;
	std::string name;
	float speed;
	bool isLoop;
private:
	bool destroyFlag;
};