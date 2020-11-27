#pragma once
#include "../../lib/UrLib.h"

class PlayerMover : public Component {
public:
	PlayerMover();
	~PlayerMover();
	void Start();
	void Update();
	void Move(bool _isRight);
	void Jump();
	

private:
	float speed;		// ‰¡ˆÚ“®‘¬“x‚ğŠi”[‚·‚é” 
	float jumpPower;	// —‰º‘¬“x‚ğŠi”[‚·‚é” 
	bool randing;		// ’…’n‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ğŠi”[‚·‚é” 

private:
	void Fall();		// —‰ºˆ—
};