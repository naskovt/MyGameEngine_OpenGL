#ifndef CAR_ENGINE_H
#define CAR_ENGINE_H


class CarEngine
{
public:

	CarEngine() = delete;
	CarEngine(float idleRPM, float maxRPM, float throttlingStep, float decreasingStep, float revLimiterStep) :
		_idleRPM( idleRPM), _maxRPM(maxRPM), _throttlingStep(throttlingStep), _decreasingStep(decreasingStep),
		_revLimiterStep(revLimiterStep), _RPM(0) {};

	void Throttle();

	void Idle();

	float GetNormalizedRPM();

private:

	float _idleRPM, _maxRPM, _throttlingStep, _decreasingStep, _RPM, _revLimiterStep;
};

#endif // !define CAR_ENGINE_H
