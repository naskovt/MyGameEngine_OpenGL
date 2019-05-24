#include "CarEngine.h"



void CarEngine::Throttle() {


	// rev limiter
	if (_RPM >= _maxRPM)
	{
		_RPM -= _revLimiterStep;
		return;
	}

	_RPM += _throttlingStep;

	if (_RPM > _maxRPM)
	{
		_RPM = _maxRPM;
	}
}

void CarEngine::Idle() {

	if (_RPM > _idleRPM) {

		_RPM -= _decreasingStep;

		if (_RPM < _idleRPM)
		{
			_RPM = _idleRPM;
		}
	}

}

float CarEngine::GetNormalizedRPM() {
	return _RPM / _maxRPM;
}
