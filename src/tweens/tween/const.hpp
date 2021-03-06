#ifndef ZEN_TWEENS_CONST_HPP
#define ZEN_TWEENS_CONST_HPP

namespace Zen {

enum class TWEEN  {
	CREATED = 0,
	INIT,
	DELAY,
	OFFSET_DELAY,
	PENDING_RENDER,
	PLAYING_FORWARD,
	PLAYING_BACKWARD,
	HOLD_DELAY,
	REPEAT_DELAY,
	COMPLETE,

	//  Tween specific
	PENDING_ADD,
	PAUSED,
	LOOP_DELAY,
	ACTIVE,
	COMPLETE_DELAY,
	PENDING_REMOVE,

	// Easing functions
	// Powers
	POWER0,
	POWER1,
	POWER2,
	POWER3,
	POWER4,
	// Ease
	LINEAR,
	QUAD,
	CUBIC,
	QUART,
	QUINT,
	SINE,
	EXPO,
	CIRCULAR,
	ELASTIC,
	BACK,
	BOUNCE,
	STEPPED,
	// Ease In
	QUAD_IN,
	CUBIC_IN,
	QUART_IN,
	QUINT_IN,
	SINE_IN,
	EXPO_IN,
	CIRCULAR_IN,
	ELASTIC_IN,
	BACK_IN,
	BOUNCE_IN,
	// Ease Out
	QUAD_OUT,
	CUBIC_OUT,
	QUART_OUT,
	QUINT_OUT,
	SINE_OUT,
	EXPO_OUT,
	CIRCULAR_OUT,
	ELASTIC_OUT,
	BACK_OUT,
	BOUNCE_OUT,
	// Ease InOut
	QUAD_INOUT,
	CUBIC_INOUT,
	QUART_INOUT,
	QUINT_INOUT,
	SINE_INOUT,
	EXPO_INOUT,
	CIRCULAR_INOUT,
	ELASTIC_INOUT,
	BACK_INOUT,
	BOUNCE_INOUT
};

}	// namespace Zen

#endif
